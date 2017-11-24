#include<libtransistor/nx.h>

#include<malloc.h>
#include<stdio.h>

int main() {
	svcSleepThread(100000000);

	void *buf = malloc(4);

	printf("malloc returned %p\n", buf);

	if(buf == NULL) {
		return 1;
	}

	result_t r;
	memory_info_t meminfo;
	uint32_t pageinfo;
	if((r = svcQueryMemory(&meminfo, &pageinfo, buf)) != RESULT_OK) {
		printf("failed to query memory: 0x%x\n", r);
		return 2;
	}

	if(meminfo.permission != 3) {
		printf("bad memory permission: %d\n", meminfo.permission);
		return 3;
	}
  
	return 0;
}
