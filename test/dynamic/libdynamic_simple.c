#include<libtransistor/util.h>

#include<stdio.h>
#include<stdlib.h>

int global;

int dynamic_function(int a) {
	dbg_printf("in dynamic function");
	printf("malloc: %p\n", malloc(4));
	return a + 4;
}
