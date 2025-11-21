#include "mem.h"
#include <stdio.h>
#include <string.h>

int main() {
	char *str = (char *) mmalloc(30);
	int *nums = (int *) mmalloc(20);

	printf("str: %p\n", (void *) str);

	memcpy(str, "Hello World", 11);
	printf("%s\n", str);

	printf("str: %p\n", (void *) str);

	mfree(str);
	str = (char *) mmalloc(5);

	printlist();

	return 0;
}
