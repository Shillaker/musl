#include <stdint.h>
#include <errno.h>
#include "syscall.h"

/*
 * As with brk, sbrk has been removed in current msul, however, it's useful in a wasm context.
 * The original musl implementation made two calls to brk, whereas we can just all directly to the
 * relevant intrinsic
 */
void *sbrk(intptr_t inc)
{
    void *res = (void*) syscall(SYS_sbrk, inc);
    return res;
}
