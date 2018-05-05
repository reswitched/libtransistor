#include<stdio.h>
#include<stdlib.h>
#include<string.h>

#include<libtransistor/util.h>

static void spray() {
	void *ptrs[100];
	for(int i = 0; i < ARRAY_LENGTH(ptrs); i++) {
		ptrs[i] = malloc(64);
		memset(ptrs[i], 0xee, 64);
	}
}

int main(int argc, char *argv[]) {
	spray();
	for(int i = 0; i < 10; i++) {
		printf("attempt %d\n", i);
		FILE *f = fopen("/sd/foobar.doesnotexist", "rb");
		if(f != NULL) {
			printf("opened file???\n");
			return 1;
		}
		spray();
	}
}
