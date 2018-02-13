#include <libtransistor/nx.h>
#include <stdio.h>
#include <string.h>

#include "defs.h"

struct mem_block_t;
struct mem_block_t {
	void *base;
	size_t size;

	bool is_free;
	bool is_locked;
	bool is_valid;

	struct mem_block_t *prev;
	struct mem_block_t *next;
};
typedef struct mem_block_t mem_block_t;

static mem_block_t mem_blocks[512];
static mem_block_t *first_block;

static int mem_init_append_block(void *base, size_t size, bool is_free) {
	static int num_mem_blocks = 0;
	
	size&= ~0xfff; // round down
	base = (void*) ((((uint64_t) base) + 0xfff) & ~0xfff); // round up
	
	if(size <= 0) {
		return 0;
	}
	
	if(num_mem_blocks >= ARRAY_LENGTH(mem_blocks)) {
		return 2;
	}
	
	mem_block_t *mb = &mem_blocks[num_mem_blocks];
	mb->base = base;
	mb->size = size;
	mb->is_free = is_free;
	mb->is_locked = !is_free;
	mb->is_valid = true;
	if(num_mem_blocks == 0) {
		mb->prev = NULL;
		mb->next = NULL;
		first_block = mb;
	} else {
		mb->prev = &mem_blocks[num_mem_blocks-1];
		mb->prev->next = mb;
	}
	mb->next = NULL;
	
	num_mem_blocks++;

	return 0;
}

int mem_init() {
	void *addr = NULL;
	memory_info_t minfo;
	uint32_t pinfo;

	int num_mem_blocks = 0;
	memset(mem_blocks, 0, sizeof(mem_blocks));

	while(1) {
		if(svcQueryMemory(&minfo, &pinfo, addr)) {
			return 1;
		}

		int r;
		
		if(minfo.permission == 3 && minfo.memory_type == 5 && minfo.memory_attribute == 0) {
			printf("- detected usable heap block at %p, size 0x%lx\n", minfo.base_addr, minfo.size);
			
			if(loader_config.heap_overridden &&
			   minfo.base_addr <= loader_config.heap_base &&
			   minfo.base_addr + minfo.size >= loader_config.heap_base + loader_config.heap_size) {
				printf("- splitting this block around our overridden heap...\n");
				printf("- overridden heap @ %p, size 0x%lx\n", loader_config.heap_base, loader_config.heap_size);
				r = mem_init_append_block(minfo.base_addr, loader_config.heap_base - minfo.base_addr, true);
				if(r) { return r; }
				r = mem_init_append_block(loader_config.heap_base, loader_config.heap_size, false);
				if(r) { return r; }
				r = mem_init_append_block(loader_config.heap_base + loader_config.heap_size,
				                          (minfo.base_addr + minfo.size) - (loader_config.heap_base + loader_config.heap_size), true);
				if(r) { return r; }
				
			} else {
				r = mem_init_append_block(minfo.base_addr, minfo.size, true);
				if(r) { return r; }
			}
		} else {
			// to avoid incoherent coalescion
			r = mem_init_append_block(minfo.base_addr, minfo.size, false);
			if(r) { return r; }
		}

		addr = minfo.base_addr + minfo.size;
		if(!addr) {
			break;
		}
	}

	return 0;
}

// dump address space mapping
void mem_dump_info() {
	void *addr = NULL;
	memory_info_t minfo;
	uint32_t pinfo;

	printf("- memory map\n");
	while(1)
	{
		if(svcQueryMemory(&minfo, &pinfo, addr))
		{
			printf("  - query fail\n");
			return;
		}

		printf("  - mem 0x%016lX size 0x%016lX; %i %i [%i]\n", (uint64_t)minfo.base_addr, minfo.size, minfo.permission, minfo.memory_type, minfo.memory_attribute);

		addr = minfo.base_addr + minfo.size;
		if(!addr)
			break;
	}

	printf("- alloc_pages blocks\n");
	for(uint64_t i = 0; i < ARRAY_LENGTH(mem_blocks); i++) {
		if(mem_blocks[i].is_valid) {
			printf("  - [%16p] base %16p, size 0x%16lx, free %d, locked %d, prev %16p, next %16p\n", &mem_blocks[i], mem_blocks[i].base, mem_blocks[i].size, mem_blocks[i].is_free, mem_blocks[i].is_locked, mem_blocks[i].prev, mem_blocks[i].next);
		}
	}
}

static void mem_assert_coherency() {
	mem_block_t *head = first_block;
	if(head == NULL) {
		printf("first block is NULL?\n");
		return;
	}
	void *addr = head->base;
	while(head != NULL) {
		if(head->base != addr) {
			printf("coherency broken\n");
			mem_dump_info();
			exit_loader();
		}
		addr+= head->size;
		head = head->next;
	}
}

static mem_block_t *mem_get_new_block() {
	for(uint64_t i = 0; i < ARRAY_LENGTH(mem_blocks); i++) {
		if(!mem_blocks[i].is_valid) {
			mem_blocks[i].is_valid = true;
			return &mem_blocks[i];
		}
	}
	
	return NULL;
}

void *mem_alloc_pages(size_t min, size_t max, size_t *actual) {
	printf("- alloc pages [0x%lx, 0x%lx]\n", min, max);
	
	mem_block_t *alloc_head = first_block;
	mem_block_t *smallest = NULL;

	// round up to page size
	min = (min + 0xfff) & ~0xfff;
	max = (max + 0xfff) & ~0xfff;
	
	if(min > max) {
		return NULL;
	}

	// find smallest block that matches our lower bound on size
	while(alloc_head != NULL) {
		if(alloc_head->is_free && alloc_head->size >= min && (smallest == NULL || alloc_head->size < smallest->size)) {
			smallest = alloc_head;
		}
		alloc_head = alloc_head->next;
	}
	
	if(smallest == NULL) {
		return NULL;
	}

	printf("  - using block [%p]\n", smallest);
	
	// use as much of the block as we can
	size_t size = max;
	
	if(size >= smallest->size) {
		// use the entire block
		size = smallest->size;
		printf("  - using entire block\n");
	} else {
		// split the block
		mem_block_t *new_block = mem_get_new_block();
		if(!new_block) {
			return NULL;
		}
		
		new_block->base = smallest->base + size;
		new_block->size = smallest->size - size;
		
		new_block->is_free = true;
		new_block->is_valid = true;
		
		new_block->next = smallest->next;
		new_block->prev = smallest;
		smallest->next->prev = new_block;
		smallest->next = new_block;
		
		smallest->size = size;

		printf("  - split block, asserting coherency...\n");
		mem_assert_coherency();
	}
	
	smallest->is_free = false;
	
	if(actual != NULL) {
		*actual = size;
	}
	return smallest->base;
}

bool mem_free_pages(void *pages) {
	mem_block_t *free_head = first_block;
	
	while(free_head != NULL) {
		if(free_head->base == pages) {
			break;
		}
		free_head = free_head->next;
	}

	if(free_head->base != pages) {
		return true;
	}

	if(free_head->is_locked) {
		return true;
	}
	
	if(free_head->is_free) {
		return true;
	}

	// TODO: check memory permission/type/state
	
	free_head->is_free = true;
	if(free_head->prev && free_head->prev->is_free) { // coalesce with block before
		free_head->prev->size+= free_head->size;
		free_head->prev->next = free_head->next;
		free_head->next->prev = free_head->prev;
		free_head->is_valid = false;
		free_head = free_head->prev;
		mem_assert_coherency();
	}
	if(free_head->next && free_head->next->is_free) { // coalesce with block after
		free_head->size+= free_head->next->size;
		free_head->next->next->prev = free_head;
		free_head->next->is_valid = false;
		free_head->next = free_head->next->next;
		mem_assert_coherency();
	}

	return false;
}

// allocate the largest block available
void *mem_alloc_largest(size_t *size) {
	mem_block_t *alloc_head = first_block;
	mem_block_t *largest = NULL;

	// find smallest block that matches our lower bound on size
	while(alloc_head != NULL) {
		if(alloc_head->is_free && (largest == NULL || alloc_head->size > largest->size)) {
			largest = alloc_head;
		}
		alloc_head = alloc_head->next;
	}
	
	if(largest == NULL) {
		return NULL;
	}

	*size = largest->size;
	largest->is_free = false;
	return largest->base;
}
