#include<malloc.h>
#include<stdio.h>

int main(int argc) {
	void *p = NULL;
	do {
		printf(" -> %p\n", p = malloc(0x2000000));
	} while(p != NULL);
}
