#define _GNU_SOURCE
#include <dirent.h>
#include <fcntl.h>
#include <stdlib.h>
#include <stdio.h>
#include <string.h>
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

	// There seems to be a bug in dlmalloc where the memory returned by calloc is not zeroed.
	// Unfortunately we need to manually zero the fields before the buffer to ensure things
	// work properly
	size_t zeroSize = 4* sizeof(int) + sizeof(off_t);
	memset(dir, 0, zeroSize);

	unsigned char* memPtr = (unsigned char*) dir;
	printf("OPENDIR MEMORY:\n");
	for(int i = 0; i < 200; i++){
        if(i > 0 && (i % 8 == 0)) {
            printf("\n");
        }
	    printf("%02x ", memPtr[i]);

	}
	printf("\n");

	printf("OPENDIR - dir->buf_pos %i  dir->buf_end %i (dir %i)\n", dir->buf_pos, dir->buf_end, dir);

	dir->fd = fd;
	return dir;
}
