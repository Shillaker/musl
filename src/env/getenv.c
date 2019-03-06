#include <stdlib.h>
#include <string.h>
#include "libc.h"

char *__strchrnul(const char *, int);

char *getenv(const char *name)
{
	// Hack to hook into environment
	return _getenv(name);
}
