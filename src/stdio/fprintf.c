#include <stdio.h>
#include <stdarg.h>

int fprintf(FILE *restrict f, const char *restrict fmt, ...)
{
	int ret;
	va_list ap;
	va_start(ap, fmt);
	ret = vfprintf(f, fmt, ap);
	va_end(ap);
	return ret;
}

// This is an Emscripten-specific function to optimise fprintf.
// We can just pass through to normal fprintf backend.
int fiprintf(FILE *restrict f, const char *restrict fmt, ...)
{
    int ret;
    va_list ap;
    va_start(ap, fmt);
    ret = vfprintf(f, fmt, ap);
    va_end(ap);
    return ret;
}