#include<libtransistor/util.h>

int global;

int dynamic_function(int a) {
	dbg_printf("in dynamic function");
	return a + 4;
}
