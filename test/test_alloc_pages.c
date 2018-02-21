#include<libtransistor/alloc_pages.h>
#include<libtransistor/util.h>

#include<stdio.h>

#define ASSERT_OK(label, expr) if((r = expr) != RESULT_OK) {            \
		printf("assertion failed at %s:%d: result 0x%x is not OK\n", __FILE__, __LINE__, r); \
		goto label; \
	}

int main(int argc, char *argv[]) {
	result_t r;
	
	size_t size;
	void *pages[5];
	pages[0] = alloc_pages(0x1000, 0x2000, &size);
	pages[1] = alloc_pages(0x1000, 0x1000, NULL);
	pages[2] = alloc_pages(0x1000, 0x1000, NULL);
	free_pages(pages[1]);
	ASSERT_OK(fail, ap_probe_full_address_space());
	ap_dump_info();
	
	return 0;
fail:
	return 1;
}
