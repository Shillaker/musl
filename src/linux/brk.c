#include <errno.h>
#include "syscall.h"

/*
 * brk has been removed in the latest musl, however, it works well in a wasm scenario
 * so we'll keep it.
 */
int brk(void *end)
{
    void *res = (void*) syscall(SYS_brk, end);

    if(res == (void*) -1) {
        return -1;
    }

    return 0;
}
