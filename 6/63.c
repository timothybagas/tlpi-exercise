#include <stdio.h>
#include <stdlib.h>
#include <string.h>

extern char **environ;

int env_index(const char *str) {
	int i;
	size_t pref_len, str_len;
	char *str_it, *environ_it;

	str_len = strlen(str);	

	for (i = 0; environ[i] != NULL; i++) {
		pref_len = 0;
		str_it = str;
		environ_it = environ[i];
		
		while (str_it != NULL && environ_it != NULL && *str_it == *environ_it) {
			str_it++; environ_it++; pref_len++;
		}
		if (pref_len == str_len && *environ_it == '=') break;
	}
	return i;
}

int msetenv(const char *name, const char *value, int overwrite) {	
	int i;
	char *new_environ;

	i = env_index(name);	

	if (environ[i] == NULL) {
		environ[i + 1] = NULL;
	}

	if (environ[i] == NULL || overwrite) {
		size_t name_len = strlen(name);
		size_t value_len = strlen(value);
		new_environ = (char *) malloc(name_len + value_len + 1);

		new_environ = strcpy(new_environ, name);
		new_environ = strcat(new_environ, "=");
		new_environ = strcat(new_environ, value);

		environ[i] = new_environ;
	}
	return 0;
}

int munsetenv(const char *name) {	
	int i;
	i = env_index(name);
	for (; environ[i] != NULL; i++) {
		environ[i] = environ[i + 1];
	}
	return 0;
}

int main(int argc, char **argv) {	
	msetenv("MYVAR", "A", 0);
	msetenv("MYVAR", "B", 1);
	msetenv("MYVAR", "C", 0);
	msetenv("MYVAR2", "D", 0);

	printf("%s=%s\n", "MYVAR", getenv("MYVAR"));
	printf("%s=%s\n", "MYVAR2", getenv("MYVAR2"));
	printf("%s=%s\n", "MYVAR3", getenv("MYVAR3"));
	printf("============================\n");

	munsetenv("MYVAR");

	printf("%s=%s\n", "MYVAR", getenv("MYVAR"));
	printf("%s=%s\n", "MYVAR2", getenv("MYVAR2"));
	printf("%s=%s\n", "MYVAR3", getenv("MYVAR3"));
	printf("============================\n");

	msetenv("MYVAR3", "E", 0);

	printf("%s=%s\n", "MYVAR", getenv("MYVAR"));
	printf("%s=%s\n", "MYVAR2", getenv("MYVAR2"));
	printf("%s=%s\n", "MYVAR3", getenv("MYVAR3"));
	printf("============================\n");

	munsetenv("MYVAR");
	munsetenv("MYVAR2");

	printf("%s=%s\n", "MYVAR", getenv("MYVAR"));
	printf("%s=%s\n", "MYVAR2", getenv("MYVAR2"));
	printf("%s=%s\n", "MYVAR3", getenv("MYVAR3"));
	printf("============================\n");

	return 0;
}
