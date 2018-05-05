#include<malloc.h>
#include<string.h>
#include<libtransistor/util.h>

void __real_free(void *ptr);

void __wrap_free(void *ptr) {
	dbg_printf("poisoning %p before free...", ptr);
	memset(ptr, 0xee, malloc_usable_size(ptr));
	__real_free(ptr);
}
