#include<libtransistor/util.h>

int global;

int not_dynamic_function(int a) {
	dbg_printf("in not dynamic function");
	return a + 4;
}
