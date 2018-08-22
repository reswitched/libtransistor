#include<libtransistor/alloc_pages.h>

#include<libtransistor/types.h>
#include<libtransistor/loader_config.h>

#include<stdlib.h>

void *alloc_pages(size_t min, size_t max, size_t *actual) {
	if(loader_config.has_alloc_pages) {
		return loader_config.alloc_pages(min, max, actual);
	} else {
		void *memptr;
		if(posix_memalign(&memptr, 0x1000, max) == 0) {
			if(actual != NULL) {
				*actual = max;
			}
			return memptr;
		} else {
			return NULL;
		}
	}
}

bool free_pages(void *pages) {
	if(loader_config.has_alloc_pages) {
		return loader_config.free_pages(pages);
	} else {
		free(pages);
		return true;
	}
}
