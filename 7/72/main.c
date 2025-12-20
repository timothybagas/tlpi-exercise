#include "mem.h"
#include <stdio.h>

int main() {
	char *str = (char *) mmalloc(100);
	int *nums = (int *) mmalloc(20);

	printf("str: %p\n", (void *) str);

  str[0] = 'H';
  str[1] = 'e';
  str[2] = 'l';
  str[3] = 'l';
  str[4] = 'o';
	printf("%s\n", str);

	printf("str: %p\n", (void *) str);
	debug();

	mfree(str);
	debug();

	str = (char *) mmalloc(5);
	debug();

	return 0;
}
