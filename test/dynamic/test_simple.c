#include<stdio.h>

int dynamic_function(int a);

int main(int argc, char *argv[]) {
	printf("calling dynamic_function...\n");
	int ret = dynamic_function(9);
	printf("dynamic_function returns: %d (should return 13)\n", ret);
	return ret != 13;
}
