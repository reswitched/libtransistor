#include<stdio.h>

int main(int argc, char *argv[]) {
	int r = getc(stdin);
	printf("getchar returned %d\n", r);
	return 0;
}
