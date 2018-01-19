#include <libtransistor/nx.h>
#include <libtransistor/ipc.h>
#include <string.h>
#include <stdlib.h>
#include <stdio.h>
#include "defs.h"
#include "memory.h"

void *wkBase;

// map area
void *map_base;
uint64_t map_size;
static heap_map_t heap_map[HEAP_MAP_SIZE];
static int heap_map_cur;

// heap area
void *heap_base;
uint64_t heap_size;

// dump address space mapping
void mem_info()
{
	void *addr = NULL;
	memory_info_t minfo;
	uint32_t pinfo;

	while(1)
	{
		if(svcQueryMemory(&minfo, &pinfo, addr))
		{
			printf("- querry fail\n");
			return;
		}

		printf("mem 0x%016lX size 0x%016lX; %i %i [%i]\n", (uint64_t)minfo.base_addr, minfo.size, minfo.permission, minfo.memory_type, minfo.memory_attribute);

		addr = minfo.base_addr + minfo.size;
		if(!addr)
			break;
	}
}

// create one huge contiguous block from HEAP
// fill 'heap_map' for unmapping
int mem_make_block()
{
	void *addr = NULL;
	memory_info_t minfo;
	uint32_t pinfo;
	void *map = map_base;
	int i;

	heap_map_cur = 0;
	map_size = 0;

	// scan for areas
	while(1)
	{
		if(svcQueryMemory(&minfo, &pinfo, addr))
			return 1;

		if(minfo.permission == 3 && minfo.memory_type == 5 && minfo.memory_attribute == 0)
		{
			if(loader_config.heap_overridden &&
			   minfo.base_addr <= loader_config.heap_base &&
			   minfo.base_addr + minfo.size >= loader_config.heap_base + loader_config.heap_size) {
				printf("- splitting this block around our overridden heap...\n");
				printf("- overridden heap @ %p, size 0x%x\n", loader_config.heap_base, loader_config.heap_size);
				heap_map[heap_map_cur].src = minfo.base_addr;
				heap_map[heap_map_cur].size = loader_config.heap_base - minfo.base_addr;
				printf("- block before: %p, 0x%x\n", heap_map[heap_map_cur].src, heap_map[heap_map_cur].size);
				heap_map_cur++;
				if(heap_map_cur == HEAP_MAP_SIZE) {
					printf("- out of map storage space\n");
					break;
				}
				
				heap_map[heap_map_cur].src = loader_config.heap_base + loader_config.heap_size;
				heap_map[heap_map_cur].size = (minfo.base_addr + minfo.size) - (loader_config.heap_base + loader_config.heap_size);
				printf("- block after: %p, 0x%x\n", heap_map[heap_map_cur].src, heap_map[heap_map_cur].size);
				heap_map_cur++;
			} else {
				printf("- found suitable block at %p, size 0x%x\n", minfo.base_addr, minfo.size);
				heap_map[heap_map_cur].src = minfo.base_addr;
				heap_map[heap_map_cur].size = minfo.size;
				heap_map_cur++;
			}
			if(heap_map_cur == HEAP_MAP_SIZE)
			{
				printf("- out of map storage space\n");
				break;
			}
		}

		addr = minfo.base_addr + minfo.size;
		if(!addr)
			break;
	}

	// map those areas
	for(i = 0; i < heap_map_cur; i++)
	{
		result_t r;

		heap_map[i].dst = map;
		r = svcMapMemory(heap_map[i].dst, heap_map[i].src, heap_map[i].size);
		if(r)
		{
			// failed
			printf("- svcMapMemory error 0x%06X\n", r);
			heap_map[i].size = 0; // mark as useless
		} else
		{
			// OK; advance destination
			map += heap_map[i].size;
		}
	}

	map_size = map - map_base;
	printf("- mapped %luB contiguous memory block\n", map_size);

	return 0;
}

// free created contiguous block
// uses 'heap_map' for unmapping
int mem_destroy_block()
{
	int i;

	map_size = 0;

	for(i = 0; i < heap_map_cur; i++)
	{
		if(heap_map[i].size)
		{
			result_t r;
			r = svcUnmapMemory(heap_map[i].dst, heap_map[i].src, heap_map[i].size);
			if(r)
				return r;
		}
	}

	heap_map_cur = 0;
	return 0;
}

// remove 'uncached' flag from all HEAP pages
int mem_heap_cleanup()
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

// get biggest HEAP block
int mem_get_heap()
{
	void *addr = NULL;
	memory_info_t minfo;
	uint32_t pinfo;
	void *ptr;
	uint64_t size = 0;

	while(1)
	{
		if(svcQueryMemory(&minfo, &pinfo, addr))
			return 1;

		if(minfo.permission == 3 && minfo.memory_type == 5 && minfo.size > size)
		{
			size = minfo.size;
			ptr = minfo.base_addr;
		}

		addr = minfo.base_addr + minfo.size;
		if(!addr)
			break;
	}

	if(!size)
		return 1;

	heap_base = ptr;
	heap_size = size;

	return 0;
}

// install exit hook in webkit
int mem_install_hook(void *hook_func)
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

