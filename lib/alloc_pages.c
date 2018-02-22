#include<libtransistor/types.h>
#include<libtransistor/svc.h>
#include<libtransistor/util.h>
#include<libtransistor/loader_config.h>
#include<libtransistor/alloc_pages.h>

#include<stdio.h>
#include<string.h>
#include<stdlib.h>

#define AP_DEBUG_ENABLED 0
#define AP_DEBUG(...) if(AP_DEBUG_ENABLED) dbg_printf(__VA_ARGS__)

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

static mem_block_t *ap_get_new_block();
static mem_block_t *ap_attempt_coalesce(mem_block_t *block);
static int ap_insert_new_block(void *base, size_t size, bool is_free);
static result_t ap_insert_and_split_block(void *base, size_t size, bool locked);
static void ap_assert_coherency();
static void *ap_alloc_pages(size_t min, size_t max, size_t *actual);
static bool ap_free_pages(void *pages);

static mem_block_t *ap_get_new_block() {
	for(uint64_t i = 0; i < ARRAY_LENGTH(mem_blocks); i++) {
		if(!mem_blocks[i].is_valid) {
			mem_blocks[i].is_valid = true;
			return &mem_blocks[i];
		}
	}
	
	return NULL;
}

static mem_block_t *ap_attempt_coalesce(mem_block_t *block) {
	if(block->prev &&
	   block->prev->is_free == block->is_free &&
	   block->prev->is_locked == block->is_locked) { // coalesce with block before
		block->prev->size+= block->size;
		block->prev->next = block->next;
		if(block->next) {
			block->next->prev = block->prev;
		}
		block->is_valid = false;
		return ap_attempt_coalesce(block->prev);
	} else if(block->next &&
	          block->next->is_free == block->is_free &&
	          block->next->is_locked == block->is_locked) { // coalesce with block after
		block->size+= block->next->size;
		if(block->next->next) {
			block->next->next->prev = block;
		}
		block->next->is_valid = false;
		block->next = block->next->next;
		return ap_attempt_coalesce(block);
	} else {
		return block;
	}
}

static int ap_insert_new_block(void *base, size_t size, bool is_free) {
	AP_DEBUG("inserting [%p, +0x%x)", base, size);
	size&= ~0xfff; // round down
	base = (void*) ((((uint64_t) base) + 0xfff) & ~0xfff); // round up
	
	if(size <= 0) {
		return 0;
	}

	mem_block_t *mb = ap_get_new_block();
	if(mb == NULL) {
		return 1;
	}
	
	mb->base = base;
	mb->size = size;
	mb->is_free = is_free;
	mb->is_locked = !is_free;
	mb->is_valid = true;

	mem_block_t *last = NULL;
	for(mem_block_t *head = first_block; true; head = head->next) {
		if(head == NULL || head->base >= base) {
			if(head) {
				if(head->base == base) {
					return 2;
				}
				if(head->base < base + size) {
					return 3;
				}
				head->prev = mb;
			}
			
			mb->next = head;
			mb->prev = last;
			
			if(last) {
				last->next = mb;
			} else {
				first_block = mb;
			}

			ap_attempt_coalesce(mb);
			
			return 0;
		}
		last = head;
	}
}

static size_t heap_size = 0;

result_t ap_init() {
	if(loader_config.heap_overridden) {
		memset(mem_blocks, 0, sizeof(mem_blocks));
		ap_insert_new_block(0, loader_config.heap_base, false);
		ap_insert_new_block(loader_config.heap_base, loader_config.heap_size, true);
	}

	return RESULT_OK;
}

// split this block around any existing blocks
static result_t ap_insert_and_split_block(void *base, size_t size, bool locked) {
	AP_DEBUG("probing block: [%p, +0x%x)...", base, size);
	if(size < 0x1000) {
		return RESULT_OK;
	}
	
	mem_block_t *head = first_block;
	while(head != NULL) {
		if((head->base >= base && head->base < base + size) ||
		   (head->base + head->size > base && head->base + head->size <= base + size)) {
			AP_DEBUG("overlapped with existing block [%p, +0x%x]", head->base, head->size);
			// we're overlapping with an existing block, need to split...
			result_t r;
			if(head->base >= base) { // if the start of the overlapping block is in the one we're trying to add
				AP_DEBUG("split begin");
				// add the space before it
				r = ap_insert_and_split_block(base, head->base - base, locked);
				if(r) { return r; }
				AP_DEBUG("done split begin");
			}
			if(head->base + size > base) { // if the end of the overlapping block is in the one we're trying to add
				AP_DEBUG("split end");
				// add the space after it
				r = ap_insert_and_split_block(head->base + head->size, (base + size) - (head->base + head->size), locked);
				if(r) { return r; }
				AP_DEBUG("done split end");
			}
			return RESULT_OK;
		}
		head = head->next;
	}

	AP_DEBUG("no overlap detected");
	return ap_insert_new_block(base, size, !locked);
}

// dump address space mapping
// may not be safe to call if printf has not been set up yet
void ap_dump_info() {
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

	printf("- alloc_pages blockchain\n");
	for(mem_block_t *head = first_block; head != NULL; head = head->next) {
		printf("  - [%16p] base %16p, size 0x%16lx, free %d, locked %d, prev %16p, next %16p\n", head, head->base, head->size, head->is_free, head->is_locked, head->prev, head->next);
	}
}

static void ap_assert_coherency() {
	mem_block_t *head = first_block;
	if(head == NULL) {
		AP_DEBUG("first block is NULL?\n");
		return;
	}
	void *addr = head->base;
	while(head != NULL) {
		if(head->base != addr) {
			AP_DEBUG("coherency broken\n");
			if(AP_DEBUG_ENABLED) {
				ap_dump_info();
			}
			exit(1);
		}
		addr+= head->size;
		head = head->next;
	}
}

result_t ap_probe_full_address_space() {
	result_t r;
	void *addr = NULL;
	memory_info_t minfo;
	uint32_t pinfo;

	// clear chain, except for blocks that have been allocated
	for(mem_block_t *head = first_block; head != NULL; head = head->next) {
		if(head->is_locked || head->is_free) {
			if(head->prev == NULL) {
				first_block = head->next;
			} else {
				head->prev->next = head->next;
				if(head->next) {
					head->next->prev = head->prev;
				}
			}
		}
	}

	// add new blocks
	while(1) {
		if((r = svcQueryMemory(&minfo, &pinfo, addr)) != RESULT_OK) {
			return r;
		}

		int r;
		
		if(minfo.permission == 3 && minfo.memory_type == 5 && minfo.memory_attribute == 0) {
			AP_DEBUG("- detected usable heap block at %p, size 0x%lx\n", minfo.base_addr, minfo.size);
			
			r = ap_insert_and_split_block(minfo.base_addr, minfo.size, false);
			if(r) { return r; }
		} else {
			AP_DEBUG("- detected unusable block at %p, size 0x%lx\n", minfo.base_addr, minfo.size);
			r = ap_insert_and_split_block(minfo.base_addr, minfo.size, true);
			if(r) { return r; }
		}

		addr = minfo.base_addr + minfo.size;
		if(!addr) {
			break;
		}
	}

	ap_assert_coherency();

	return RESULT_OK;
}

static void *ap_alloc_pages(size_t min, size_t max, size_t *actual) {
	AP_DEBUG("- alloc pages [0x%lx, 0x%lx]\n", min, max);
	
	// round up to page size
	min = (min + 0xfff) & ~0xfff;
	max = (max + 0xfff) & ~0xfff;
	
	if(min > max) {
		return NULL;
	}

	mem_block_t *alloc_head;
	mem_block_t *smallest = NULL;
	
rescan:

	alloc_head = first_block;
	
	// find smallest block that matches our lower bound on size
	while(alloc_head != NULL) {
		if(alloc_head->is_free && alloc_head->size >= min && (smallest == NULL || alloc_head->size < smallest->size)) {
			smallest = alloc_head;
		}
		alloc_head = alloc_head->next;
	}
	
	if(smallest == NULL) {
		if(!loader_config.heap_overridden) {
			AP_DEBUG("  - out of memory, growing heap...\n");
			size_t original_heap_size = heap_size;
			heap_size*= 2;

			if(heap_size == 0) {
				heap_size = 0x200000;
			}
			
			void *heap;
			while(heap_size > original_heap_size && svcSetHeapSize(&heap, heap_size) != RESULT_OK) {
				heap_size-= 0x20000;
			}
			if(heap_size == original_heap_size) {
				AP_DEBUG("  - failed to grow heap\n");
				return NULL;
			}
			AP_DEBUG("  - grew heap to 0x%lx bytes\n", heap_size);
			AP_DEBUG("  - rescanning address space...\n");
			ap_probe_full_address_space();
			if(AP_DEBUG_ENABLED) {
				ap_dump_info();
			}
			goto rescan;
		}
		return NULL;
	}

	AP_DEBUG("  - using block [%p]\n", smallest);
	
	// use as much of the block as we can
	size_t size = max;
	
	if(size >= smallest->size) {
		// use the entire block
		size = smallest->size;
		AP_DEBUG("  - using entire block\n");
	} else {
		// split the block
		mem_block_t *new_block = ap_get_new_block();
		if(!new_block) {
			return NULL;
		}
		
		new_block->base = smallest->base + size;
		new_block->size = smallest->size - size;
		
		new_block->is_free = true;
		new_block->is_valid = true;
		
		new_block->next = smallest->next;
		new_block->prev = smallest;
		if(smallest->next) {
			smallest->next->prev = new_block;
		}
		smallest->next = new_block;
		
		smallest->size = size;

		AP_DEBUG("  - split block, asserting coherency...\n");
		ap_assert_coherency();
		AP_DEBUG("  - coherent!\n");
	}
	
	smallest->is_free = false;
	
	if(actual != NULL) {
		*actual = size;
	}
	return smallest->base;
}

static bool ap_free_pages(void *pages) {
	mem_block_t *free_head;
	for(free_head = first_block; free_head != NULL; free_head = free_head->next) {
		if(free_head->base == pages) {
			break;
		}
	}

	if(free_head == NULL) {
		return true;
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

	result_t r;
	memory_info_t minfo;
	uint32_t pinfo;
	if((r = svcQueryMemory(&minfo, &pinfo, pages)) != RESULT_OK) {
		return true;
	}

	if(minfo.permission != 3 || minfo.memory_type != 5 || minfo.memory_attribute != 0) {
		return true;
	}
	
	// TODO: check memory permission/type/state

	free_head->is_free = true;
	free_head = ap_attempt_coalesce(free_head);
	ap_assert_coherency();
	
	return false;
}

// allocate the largest block available
void *ap_alloc_largest(size_t *size) {
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

void *alloc_pages(size_t min, size_t max, size_t *actual) {
	if(loader_config.has_alloc_pages) {
		return loader_config.alloc_pages(min, max, actual);
	}

	return ap_alloc_pages(min, max, actual);
}

bool free_pages(void *pages) {
	if(loader_config.has_alloc_pages) {
		return loader_config.free_pages(pages);
	}

	return ap_free_pages(pages);
}
