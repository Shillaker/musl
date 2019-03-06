#include <stdlib.h>
#include <string.h>
#include <errno.h>

char *__strchrnul(const char *, int);
int __putenv(char *, size_t, char *);

void __env_rm_add(char *old, char *new)
{
	static char **env_alloced;
	static size_t env_alloced_n;
	for (size_t i=0; i < env_alloced_n; i++)
		if (env_alloced[i] == old) {
			env_alloced[i] = new;
			free(old);
			return;
		} else if (!env_alloced[i] && new) {
			env_alloced[i] = new;
			new = 0;
		}
	if (!new) return;
	char **t = realloc(env_alloced, sizeof *t * (env_alloced_n+1));
	if (!t) return;
	(env_alloced = t)[env_alloced_n++] = new;
}

int setenv(const char *var, const char *value, int overwrite)
{
	// Hack to hook into environment
	return _setenv(var, value, overwrite);
}
