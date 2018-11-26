#include <features.h>
#include "libc.h"

#define START "_start"

#include "crt_arch.h"

int main(int argc, char *argv[]);

void _start_c(long *p)
{
	int argc = p[0];
	char **argv = (void *)(p+1);

	// Cut out the whole libc init process, passing control directly to the application
    exit(main(argc, argv));
}
