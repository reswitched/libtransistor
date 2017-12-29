#include<stdio.h>
#include<stdbool.h>

static bool initializer_was_run = false;

static void __attribute__((constructor)) initializer(void) {
	printf("in init...\n");
	initializer_was_run = true;
}

static void __attribute__((destructor)) finalizer(void) {
	printf("in fini...\n");
}

int main(int argc, char *argv[]) {
	printf("in main\n");
	printf("initializer was run? %s\n", initializer_was_run ? "true" : "false");
	return initializer_was_run ? 0 : 1;
}
