#include<libtransistor/types.h>
#include<libtransistor/svc.h>
#include<libtransistor/util.h>
#include<libtransistor/loader_config.h>
#include<libtransistor/alloc_pages.h>
#include<libtransistor/err.h>

#include<stdio.h>
#include<string.h>
#include<stdlib.h>

#define AP_DEBUG_ENABLED 0
#define AP_DEBUG(...) if(AP_DEBUG_ENABLED) dbg_printf(__VA_ARGS__)

typedef enum {
	STATE_UNUSED = 0,
	STATE_INVALID,
	STATE_UNALLOCATED ,
	STATE_ALLOCATED,
	STATE_LOCKED_BY_MEMORY_STATE,
	STATE_LOCKED_BY_OVERRIDE,
} block_state_t;

struct mem_block_t;
struct mem_block_t {
	void *base;
	size_t size;

	block_state_t state;

	struct mem_block_t *prev;
	struct mem_block_t *next;
};
typedef struct mem_block_t mem_block_t;

static mem_block_t mem_blocks[512] = {{NULL, 0, STATE_UNUSED, NULL, NULL}};
static mem_block_t *first_block = NULL;

static mem_block_t *ap_get_new_block();
static mem_block_t *ap_attempt_coalesce(mem_block_t *block);
static result_t ap_insert_new_block(void *base, size_t size, block_state_t state);
static result_t ap_insert_and_split_block(void *base, ssize_t size, block_state_t state);
static void ap_assert_coherency();
static void *ap_alloc_pages(size_t min, size_t max, size_t *actual);
static bool ap_free_pages(void *pages);

static mem_block_t *ap_get_new_block() {
	for(uint64_t i = 0; i < ARRAY_LENGTH(mem_blocks); i++) {
		if(mem_blocks[i].state == STATE_UNUSED) {
			mem_blocks[i].state = STATE_INVALID;
			return &mem_blocks[i];
		}
	}
	
	return NULL;
}

static mem_block_t *ap_attempt_coalesce(mem_block_t *block) {
	if(block->prev &&
	   block->prev->state != STATE_ALLOCATED && // never coalesce allocated blocks
	   block->prev->state == block->state) { // coalesce with block before
		block->prev->size+= block->size;
		block->prev->next = block->next;
		if(block->next) {
			block->next->prev = block->prev;
		}
		block->state = STATE_UNUSED;
		return ap_attempt_coalesce(block->prev);
	} else if(block->next &&
	          block->next->state != STATE_ALLOCATED && // never coalesce allocated blocks
	          block->next->state == block->state) { // coalesce with block after
		block->size+= block->next->size;
		if(block->next->next) {
			block->next->next->prev = block;
		}
		block->next->state = STATE_UNUSED;
		block->next = block->next->next;
		return ap_attempt_coalesce(block);
	} else {
		return block;
	}
}

static result_t ap_insert_new_block(void *base, size_t size, block_state_t state) {
	AP_DEBUG("inserting [%p, +0x%x)", base, size);
	size&= ~0xfff; // round down
	base = (void*) ((((uint64_t) base) + 0xfff) & ~0xfff); // round up
	
	if(size <= 0) {
		return RESULT_OK;
	}

	mem_block_t *mb = ap_get_new_block();
	if(mb == NULL) {
		return LIBTRANSISTOR_ERR_AP_OUT_OF_PAGES;
	}
	
	mb->base = base;
	mb->size = size;
	mb->state = state;

	mem_block_t *last = NULL;
	for(mem_block_t *head = first_block; true; head = head->next) {
		if(head == NULL || head->base >= base) {
			if(head) {
				if(head->base == base) {
					return LIBTRANSISTOR_ERR_AP_DUPLICATE_BLOCK;
				}
				if(head->base < base + size) {
					return LIBTRANSISTOR_ERR_AP_INSERT_FAILED;
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
			
			return RESULT_OK;
		}
		last = head;
	}
}

result_t ap_init() {
	if(loader_config.heap_overridden) {
		ap_insert_and_split_block(0, loader_config.heap_base, STATE_LOCKED_BY_MEMORY_STATE);
		ap_insert_and_split_block(loader_config.heap_base, loader_config.heap_size, STATE_UNALLOCATED);
	} else {
		ap_probe_full_address_space();
	}

	return RESULT_OK;
}

result_t ap_lock_region(void *base, size_t size) {
	return ap_insert_new_block(base, size, STATE_LOCKED_BY_OVERRIDE);
}

// split this block around any existing blocks
static result_t ap_insert_and_split_block(void *base, ssize_t size, block_state_t state) {
	AP_DEBUG("probing block: [%p, +0x%lx)...", base, size);
	if(size < 0x1000) {
		return RESULT_OK;
	}
	
	mem_block_t *head = first_block;
	while(head != NULL) {
		if((head->base >= base && head->base < base + size) || // if the beginning of HEAD is in this block
		   (head->base + head->size > base && head->base + head->size <= base + size) || // if the end of HEAD is in this block
		   (base >= head->base && base < head->base + head->size) || // if the beginning of this block is in HEAD
		   (base + size > head->base && base + size <= head->base + head->size) // if the end of this block is in HEAD
			) {
			AP_DEBUG("overlapped with existing block [%p, +0x%lx]", head->base, head->size);
			// we're overlapping with an existing block, need to split...
			result_t r;
			if(head->base >= base) { // if the start of the overlapping block is in the one we're trying to add
				AP_DEBUG("split begin");
				// add the space before it
				r = ap_insert_and_split_block(base, head->base - base, state);
				if(r) { return r; }
				AP_DEBUG("done split begin");
			}
			if(head->base + size > base) { // if the end of the overlapping block is in the one we're trying to add
				AP_DEBUG("split end");
				// add the space after it
				r = ap_insert_and_split_block(head->base + head->size, (base + size) - (head->base + head->size), state);
				if(r) { return r; }
				AP_DEBUG("done split end");
			}
			return RESULT_OK;
		}
		head = head->next;
	}

	AP_DEBUG("no overlap detected");
	return ap_insert_new_block(base, size, state);
}

// dump address space mapping
// may not be safe to call if printf has not been set up yet
static void ap_do_dump_info(bool dbg) {
#define DI_PRINTF(...) if(dbg) { dbg_printf(__VA_ARGS__); } else printf(__VA_ARGS__)
	
	void *addr = NULL;
	memory_info_t minfo;
	uint32_t pinfo;

	DI_PRINTF("- memory map\n");
	while(1)
	{
		if(svcQueryMemory(&minfo, &pinfo, addr))
		{
			DI_PRINTF("  - query fail\n");
			return;
		}

		DI_PRINTF("  - mem 0x%016lX size 0x%016lX; %i %i [%i]\n", (uint64_t)minfo.base_addr, minfo.size, minfo.permission, minfo.memory_type, minfo.memory_attribute);

		addr = minfo.base_addr + minfo.size;
		if(!addr)
			break;
	}

	const char *state_labels[] = {"UNUSED", "INVALID", "UNALLOCD", "ALLOCD", "LOCKED_MEMSTATE", "LOCKED_MANUAL"};
	
	DI_PRINTF("- alloc_pages blocks\n");
	for(uint64_t i = 0; i < ARRAY_LENGTH(mem_blocks); i++) {
		if(mem_blocks[i].state != STATE_UNUSED) {
			DI_PRINTF("  - [%16p] base %16p, size 0x%16lx, state %15s, prev %16p, next %16p\n", &mem_blocks[i], mem_blocks[i].base, mem_blocks[i].size, state_labels[mem_blocks[i].state], mem_blocks[i].prev, mem_blocks[i].next);
		}
	}

	DI_PRINTF("- alloc_pages blockchain\n");
	for(mem_block_t *head = first_block; head != NULL; head = head->next) {
		DI_PRINTF("  - [%16p] base %16p, size 0x%16lx, state %15s, prev %16p, next %16p\n", head, head->base, head->size, state_labels[head->state], head->prev, head->next);
	}
#undef DI_PRINTF
}

void ap_dump_info() {
	ap_do_dump_info(false);
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
				ap_do_dump_info(true);
			}
			exit(1);
		}
		addr+= head->size;
		head = head->next;
	}
}

static void *heap_end = NULL;

result_t ap_probe_full_address_space() {
	result_t r;
	void *addr = NULL;
	memory_info_t minfo;
	uint32_t pinfo;

	// clear everything that's safe to clear so we can rebuild it
	for(mem_block_t *head = first_block; head != NULL; head = head->next) {
		if(head->state == STATE_LOCKED_BY_MEMORY_STATE ||
		   head->state == STATE_UNALLOCATED) {
			if(head->prev == NULL) {
				first_block = head->next;
			} else {
				head->prev->next = head->next;
				if(head->next) {
					head->next->prev = head->prev;
				}
			}
			head->state = STATE_UNUSED;
		}
	}

	// add new blocks
	while(1) {
		if((r = svcQueryMemory(&minfo, &pinfo, addr)) != RESULT_OK) {
			return r;
		}

		int r;

		if(minfo.memory_type == 5) { // if this is a heap block
			AP_DEBUG("- detected heap block at %p\n");
			if(minfo.base_addr + minfo.size > heap_end) {
				heap_end = minfo.base_addr + minfo.size; // we need to know how big the heap is before we try to expand it
			}
		}
		
		if(minfo.permission == 3 && minfo.memory_type == 5 && minfo.memory_attribute == 0) {
			AP_DEBUG("- detected usable heap block at %p, size 0x%lx\n", minfo.base_addr, minfo.size);
			
			r = ap_insert_and_split_block(minfo.base_addr, minfo.size, STATE_UNALLOCATED);
			if(r) { return r; }
		} else {
			AP_DEBUG("- detected unusable block at %p, size 0x%lx\n", minfo.base_addr, minfo.size);
			
			r = ap_insert_and_split_block(minfo.base_addr, minfo.size, STATE_LOCKED_BY_MEMORY_STATE);
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
	result_t r;
	
rescan:

	alloc_head = first_block;
	
	// find smallest block that matches our lower bound on size
	while(alloc_head != NULL) {
		if(alloc_head->state == STATE_UNALLOCATED && alloc_head->size >= min && (smallest == NULL || alloc_head->size < smallest->size)) {
			smallest = alloc_head;
		}
		alloc_head = alloc_head->next;
	}
	
	if(smallest == NULL) {
		if(!loader_config.heap_overridden) {
			AP_DEBUG("  - out of memory, growing heap...\n");

			void *heap_base;
			if((r = svcGetInfo(&heap_base, 4, 0xFFFF8001, 0)) != RESULT_OK) {
				AP_DEBUG("    - failed to determined heap base: 0x%lx\n", r);
				return NULL;
			}

			AP_DEBUG("    - heap_end %p\n", heap_end);
			
			if(heap_end == NULL) {
				if((r = ap_probe_full_address_space()) != RESULT_OK) {
					AP_DEBUG("    - failed to probe address space: 0x%lx\n");
					return NULL;
				}

				AP_DEBUG("    - finished probing, heap_end is %p\n", heap_end);
				
				if(heap_end == NULL) { // there are no pre-existing heap blocks
					heap_end = heap_base;
				}
			}
			size_t heap_size = heap_end - heap_base;
			AP_DEBUG("    - determined current heap size to be 0x%lx\n", heap_size);
			
			size_t original_heap_size = heap_size;
			heap_size*= 2;

			if(heap_size == 0) {
				heap_size = 0x200000;
			}

			if(heap_size < original_heap_size + min) {
				heap_size = original_heap_size + min;
			}

			AP_DEBUG("    - growing to 0x%lx\n", heap_size);
			
			void *heap;
			result_t r;
			while(heap_size > original_heap_size &&
			      heap_size > 0x20000 &&
			      (r = svcSetHeapSize(&heap, heap_size)) != RESULT_OK) {
				heap_size-= 0x20000;
				AP_DEBUG("    - growing to 0x%lx (previously failed with 0x%x)\n", heap_size, r);
			}
			if(heap_size <= original_heap_size) {
				AP_DEBUG("  - failed to grow heap\n");
				heap_size = original_heap_size;
				return NULL;
			}
			AP_DEBUG("  - grew heap to 0x%lx bytes\n", heap_size);
			AP_DEBUG("  - rescanning address space...\n");
			ap_probe_full_address_space();
			
			if(heap_end != heap_base + heap_size) {
				AP_DEBUG("  - heap end is not where we expect it to be (expected %p, got %p)\n", heap_base + heap_size, heap_end);
				// TODO: is this a fatal error?
			}
			
			if(AP_DEBUG_ENABLED) {
				ap_do_dump_info(true);
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

		new_block->state = STATE_UNALLOCATED;
		
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

	smallest->state = STATE_ALLOCATED;
	
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

	if(free_head->state != STATE_ALLOCATED) {
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

	free_head->state = STATE_UNALLOCATED;
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
		if(alloc_head->state == STATE_UNALLOCATED && (largest == NULL || alloc_head->size > largest->size)) {
			largest = alloc_head;
		}
		alloc_head = alloc_head->next;
	}
	
	if(largest == NULL) {
		return NULL;
	}

	*size = largest->size;
	largest->state = STATE_ALLOCATED;
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
