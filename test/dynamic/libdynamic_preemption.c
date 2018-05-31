#include<stdio.h>
#include<stdlib.h>

int global_variable = 5; // this should get preempted by test_preemption.o's global_variable, which has a value of 4

int dynamic_function(int a) {
	printf("D: global variable: %d\n", global_variable);
	if(global_variable != 4) {
		printf("D:   unexpected value for global_variable. did it not get preempted?\n");
		exit(44);
	}
	global_variable = 6;
	printf("D: global variable: %d\n", global_variable);
	return a + 4;
}
