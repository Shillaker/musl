#include <stdlib.h>
#include <string.h>
#include <errno.h>
#include "libc.h"

char *__strchrnul(const char *, int);

static void dummy(char *old, char *new) {}
weak_alias(dummy, __env_rm_add);

int unsetenv(const char *name)
{
    // Hack to hook into environment
	return _unsetenv(name);
}
