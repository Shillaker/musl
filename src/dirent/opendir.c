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

	printf("OPENDIR - dir->buf_pos %i  dir->buf_end %i (dir %i)\n", dir->buf_pos, dir->buf_end, dir);

	dir->fd = fd;
	return dir;
}
