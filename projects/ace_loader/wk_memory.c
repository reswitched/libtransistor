#include <libtransistor/nx.h>
#include <libtransistor/ipc.h>
#include <string.h>
#include <stdlib.h>
#include <stdio.h>

#include "defs.h"
#include "memory.h"
#include "wk_memory.h"

void *wkBase;

// install exit hook in webkit
int wk_mem_install_hook(void *hook_func)
{
	void *addr = NULL;
	memory_info_t minfo;
	uint32_t pinfo;
	uint64_t *ptr = NULL;

	while(1)
	{
		if(svcQueryMemory(&minfo, &pinfo, addr))
			return 1;

		if(minfo.size == WK_SIZE && minfo.permission == 5 && minfo.memory_type == 3)
			wkBase = minfo.base_addr;
		if(minfo.size == WK_MEM_SIZE && minfo.permission == 3 && minfo.memory_type == 4)
		{
			ptr = minfo.base_addr + 0x62E0;
			*ptr = (uint64_t)hook_func; // original call 0x16e6b4 from 0x12b524
		}
		addr = minfo.base_addr + minfo.size;
		if(!addr)
			break;
	}

	if(!ptr || !wkBase)
		return 1;
	return 0;
}

// remove 'uncached' flag from all HEAP pages
int wk_mem_heap_cleanup()
{
	void *addr = NULL;
	memory_info_t minfo;
	uint32_t pinfo;

	while(1)
	{
		if(svcQueryMemory(&minfo, &pinfo, addr))
			return 1;

		if(minfo.permission == 3 && minfo.memory_type == 5 && minfo.memory_attribute & 8)
			printf("- svcSetMemoryAttribute 0x%06X\n", svcSetMemoryAttribute(minfo.base_addr, minfo.size, 0, 0));

		addr = minfo.base_addr + minfo.size;
		if(!addr)
			break;
	}

	return 0;
}
