#include <fcntl.h>
#include "syscall.h"
#include "libc.h"

int posix_fadvise(int fd, off_t base, off_t len, int advice)
{
    // We don't really care
    return 0;
}

LFS64(posix_fadvise);
