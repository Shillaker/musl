#define _GNU_SOURCE
#include <dirent.h>
#include <fcntl.h>
#include <stdlib.h>
#include <stdio.h>
#include "__dirent.h"
#include "syscall.h"

DIR *opendir(const char *name)
{
	int fd;
	DIR *dir;

	if ((fd = open(name, O_RDONLY|O_DIRECTORY|O_CLOEXEC)) < 0)
		return 0;

	if (!(dir = calloc(1, sizeof *dir))) {
		__syscall(SYS_close, fd);
		return 0;
	}

	// 27/05/2019
	// For readdir and other functions to work, the buf_pos and buf_end of the returned DIR
	// must be zero. This should get done by calloc (which ought to return zeroed memory), but
	// a bug in calloc (which still exists) means that occasionally the memory from calloc
	// *isn't* zeroed, hence we set the variables manually here.
	dir->buf_pos = 0;
	dir->buf_end = 0;

	dir->fd = fd;

	printf("OPENDIR %s - buf_pos %i  buf_end %i  fd %i\n", name, dir->buf_pos, dir->buf_end, dir->fd);
	return dir;
}
