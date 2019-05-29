#define _GNU_SOURCE

#include <dirent.h>
#include <fcntl.h>
#include <stdlib.h>
#include <string.h>
#include "__dirent.h"
#include "syscall.h"

DIR *opendir(const char *name) {
    int fd;
    DIR *dir;

    if ((fd = open(name, O_RDONLY | O_DIRECTORY | O_CLOEXEC)) < 0)
        return 0;
    if (!(dir = calloc(1, sizeof *dir))) {
        __syscall(SYS_close, fd);
        return 0;
    }

    // There seems to be a bug in dlmalloc where the memory returned by calloc is not zeroed.
    // readdir relies on this being the case, therefore we must manually zero the relevant fields
    // (we can ignore the buffer itself)
    size_t zeroSize = 4 * sizeof(int) + sizeof(off_t);
    memset(dir, 0, zeroSize);

    dir->fd = fd;
    return dir;
}
