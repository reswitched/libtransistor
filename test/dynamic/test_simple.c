#include<stdio.h>

int dynamic_function(int a);

int main(int argc, char *argv[]) {
	printf("calling dynamic_function...\n");
	printf("dynamic_function returns: %d (should return 13)\n", dynamic_function(9));
}
