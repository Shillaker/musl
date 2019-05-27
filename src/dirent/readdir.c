#include <dirent.h>
#include <errno.h>
#include "__dirent.h"
#include "syscall.h"
#include "libc.h"

int __getdents(int, struct dirent *, size_t);

struct dirent *readdir(DIR *dir)
{
	struct dirent *de;


	/*
	 * This function is a little hard to understand and can be fragile.
	 * Each call to readdir will return a single dirent, but a call to getdents
	 * will fill up the whole buffer with multiple dirents.
	 *
	 * It then uses the DIR passed into the function to track how far it has moved
	 * through the buffer (and whether it needs to call getdents again). The fields
	 * are as follows:
	 *
	 * - dir->buf = pointer to the buffer (zero terminated, 2048 bytes long (hard-coded in __dirent.h))
	 * - dir->buf_end = how many bytes we've read into this buffer (zero to begin with)
	 * - dir->buf_pos = how much of the buffer we've read
	 *
	 * Clearly this depends heavily on the DIR not being modified between calls, and
	 * the DIR being passed in properly zeroed on the first call.
	 *
	 * 27/05/2019 - there is a bug in calloc where the new memory isn't always zeroed properly
	 * this meant opendir created a non-zero DIR, which caused this function to perform an
	 * infinite loop.
	 */
	if (dir->buf_pos >= dir->buf_end) {
	    // We enter this block on the first call, or if we've read through the whole buffer

	    // Call getdents to populate the buffer with dirents
		int len = __syscall(SYS_getdents, dir->fd, dir->buf, sizeof dir->buf);

		// Drop out if there are none
		if (len <= 0) {
			if (len < 0 && len != -ENOENT) errno = -len;
			return 0;
		}

		// Set up the buffer markers
		dir->buf_end = len;
		dir->buf_pos = 0;
	}

	// Get a pointer to the next dirent
	de = (void *)(dir->buf + dir->buf_pos);

	// Move the buffer position along to the beginning of the one after
	dir->buf_pos += de->d_reclen;

	// Not sure what this bit does.
	dir->tell = de->d_off;

	return de;
}

LFS64(readdir);
