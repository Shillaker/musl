#ifndef SHARED

#include <alloca.h>

void _start_c(long *p);

void _start(void) {
  long p = 0;
  _start_c(&p);
}
#endif
