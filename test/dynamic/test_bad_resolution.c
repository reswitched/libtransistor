#include<stdio.h>

int dynamic_function(int a);

int main(int argc, char *argv[]) {
	printf("should not reach main!!!\n");
	dynamic_function(4);
	return 1;
}
