#include<libtransistor/util.h>
#include<libtransistor/svc.h>

#include<stdio.h>

int main(int argc, char *argv[]) {
	result_t r;
	handle_t handle;
	if((r = obtain_self_process_handle(&handle)) != RESULT_OK) {
		printf("failed to obtain handle: 0x%x\n", r);
		return 1;
	}

	printf("obtained mirror handle: 0x%x\n", handle);

	void *my_heap_base;
	if((r = svcGetInfo(&my_heap_base, 4, 0xffff8001, 0)) != RESULT_OK) {
		printf("failed to obtain heap base: 0x%x\n", r);
		svcCloseHandle(handle);
		return 1;
	}
	printf("self heap base: %p\n", my_heap_base);
	
	void *other_heap_base;
	if((r = svcGetInfo(&other_heap_base, 4, handle, 0)) != RESULT_OK) {
		printf("failed to obtain mirror heap base: 0x%x\n", r);
		svcCloseHandle(handle);
		return 1;
	}
	printf("mirror heap_base: %p\n", other_heap_base);
	svcCloseHandle(handle);

	return my_heap_base != other_heap_base;
}
