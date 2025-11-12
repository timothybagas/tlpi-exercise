#include <setjmp.h>
#include <stdio.h>

static jmp_buf env;

void call_longjmp(int val) {
	printf("longjmp %d\n", val);
	longjmp(env, val);
}

void call_setjump() {
	if (!setjmp(env)) {
		printf("setjmp 0\n");
	} else {
		printf("setjmp 1\n");
	}
}

int main(int argc, char **argv) {
	call_setjump();
	call_longjmp(1);
	return 0;
}
