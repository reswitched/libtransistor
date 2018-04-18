#include<libtransistor/types.h>
#include<libtransistor/svc.h>
#include<libtransistor/err.h>
#include<libtransistor/alloc_pages.h>
#include<libtransistor/loader_config.h>
#include<libtransistor/address_space.h>

#include<stdio.h>
#include<string.h>

#define ASSERT_OK(label, expr) if((r = expr) != RESULT_OK) {            \
		printf("assertion failed at %s:%d: result 0x%x is not OK\n", __FILE__, __LINE__, r); \
		goto label; \
	}

void print_mapping(void *addr) {
	memory_info_t mem_info;
	uint32_t page_info;
	result_t r;
	
	ASSERT_OK(fail, svcQueryMemory(&mem_info, &page_info, addr));
	
	printf("%p +0x%lx: type %d, attribute %d, permission %d\n", mem_info.base_addr, mem_info.size, mem_info.memory_type, mem_info.memory_attribute, mem_info.permission);
	
fail:
	return;
}

int main(int argc, char *argv[]) {
	uint8_t code[] = {0x00, 0x00, 0x80, 0xd2, 0xc0, 0x03, 0x5f, 0xd6}; // mov w0, #85; ret

	if(!loader_config.has_process_handle) {
		printf("needs process handle\n");
		return 1;
	}

	if(!lconfig_has_syscall(SVC_ID_MAP_PROCESS_CODE_MEMORY)) {
		printf("needs svcMapProcessCodeMemory\n");
		return 1;
	}
	
	result_t r = LIBTRANSISTOR_ERR_OUT_OF_MEMORY;
	void *rw = alloc_pages(0x1000, 0x1000, NULL);
	if(rw == NULL) { goto fail; }
	void *rx = as_reserve(0x1000);
	if(rx == NULL) { goto fail_rx_pages; }
	
	ASSERT_OK(fail_rw_reservation, svcMapProcessCodeMemory(loader_config.process_handle, rx, rw, 0x1000));
	printf("made mapping\n");
	print_mapping(rx);
	print_mapping(rw);

	/*printf("copying code\n");
	memcpy(rw, code, sizeof(code));
	printf("copied code, running...\n");
	
	int (*func)(void) = rx;
	int ret = func();
	
	printf("jit code returned\n");
	printf("  => %d\n", ret);*/
	printf("unmapping...\n");
	svcUnmapProcessCodeMemory(loader_config.process_handle, rx, rw, 0x1000);
	printf("unmapped\n");
	
fail_rw_reservation:
	as_release(rw, 0x1000);
fail_rx_pages:
	free_pages(rx);
fail:
	return r != RESULT_OK;
}
