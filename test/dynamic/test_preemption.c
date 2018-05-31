#include<stdio.h>
#include<stdlib.h>

int dynamic_function(int a);

int global_variable = 4;

int main(int argc, char *argv[]) {
	printf("M: global variable: %d\n", global_variable);
	if(global_variable != 4) {
		printf("M:   unexpected value for global_variable. did it get overridden by libdynamic_preemption?\n");
		exit(45);
	}
	printf("M: calling dynamic_function...\n");
	int ret = dynamic_function(9);
	printf("M: dynamic_function returns: %d (should return 13)\n", ret);
	printf("M: global variable: %d\n", global_variable);
	if(global_variable != 6) {
		printf("M:  unexpected value for global_variable. did dynamic_function not update it?\n");
		exit(46);
	}
	return ret != 13;
}
