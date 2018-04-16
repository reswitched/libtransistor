#include<libtransistor/address_space.h>
#include<libtransistor/util.h>
#include<libtransistor/types.h>
#include<libtransistor/svc.h>
#include<libtransistor/err.h>
#include<libtransistor/mutex.h>

#include<stdlib.h>
#include<string.h>

typedef enum {
	INVALID,
	RESERVED_BY_KERNEL,
	RESERVED_BY_USER,
} memory_region_state_t;

typedef struct {
	memory_region_state_t state;
	uint64_t base;
	size_t size;
} memory_region_t;

static trn_mutex_t as_lock;

static result_t as_set_region_from_info(memory_region_t *region, int base_id, int size_id, memory_region_state_t state) REQUIRES(as_lock) {
	result_t r;

	if(region == NULL) {
		return LIBTRANSISTOR_ERR_OUT_OF_MEMORY;
	}
	
	region->state = state;
	if((r = svcGetInfo(&region->base, base_id, 0xFFFF8001, 0)) != RESULT_OK) { return r; }
	if((r = svcGetInfo(&region->size, size_id, 0xFFFF8001, 0)) != RESULT_OK) { return r; }

	return RESULT_OK;
}

static memory_region_t regions[256] GUARDED_BY(as_lock);
static uint64_t num_regions GUARDED_BY(as_lock) = 0;
static memory_region_t address_space GUARDED_BY(as_lock);

static memory_region_t *as_grab_region() REQUIRES(as_lock) {
	if(num_regions < ARRAY_LENGTH(regions)) {
		return &regions[num_regions++];
	}
	return NULL;
}

static void as_delete_region(uint64_t index) REQUIRES(as_lock){
	memmove(&regions[index], &regions[index+1], (--num_regions)-index);
}

result_t as_init() {
	trn_mutex_lock(&as_lock);
	
	for(uint64_t i = 0; i < ARRAY_LENGTH(regions); i++) {
		regions[i].state = INVALID;
	}
	
	result_t r;
	
	if((r = as_set_region_from_info(as_grab_region(), 2, 3, RESERVED_BY_KERNEL)) != RESULT_OK) { // MapRegion
		trn_mutex_unlock(&as_lock);
		return r;
	}
	
	if((r = as_set_region_from_info(as_grab_region(), 4, 5, RESERVED_BY_KERNEL)) != RESULT_OK) { // HeapRegion
		trn_mutex_unlock(&as_lock);
		return r;
	}

	if((r = as_set_region_from_info(as_grab_region(), 14, 15, RESERVED_BY_KERNEL)) != RESULT_OK) { // NewMapRegion
		trn_mutex_unlock(&as_lock);
		return r;
	}

	// TODO: if we want to support 1.0.0, this will need a workaround
	if((r = as_set_region_from_info(&address_space, 12, 13, INVALID)) != RESULT_OK) { // AddressSpace
		trn_mutex_unlock(&as_lock);
		return r;
	}

	trn_mutex_unlock(&as_lock);
	return RESULT_OK;
}

void as_finalize() {
}

void *as_reserve(size_t len) {
	trn_mutex_lock(&as_lock);
	
	uint64_t addr;
	memory_info_t memory_info;
	result_t r;
	uint32_t page_info;
	
	do {
		uint64_t random = (uint64_t) rand() << 12;
		addr = (random % address_space.size) + address_space.base;

		bool is_overlapping = false;
		for(uint64_t i = 0; i < num_regions; i++) {
			memory_region_t *r = &regions[i];
			if(r->state != RESERVED_BY_USER && r->state != RESERVED_BY_KERNEL) {
				continue;
			}
			
			if((addr >= r->base && addr < (r->base + r->size)) ||
			   ((addr + len) >= r->base && (addr + len) < (r->base + r->size)) ||
			   (r->base >= addr && r->base < (addr + len)) ||
			   ((r->base + r->size) >= addr && (r->base + r->size) < (addr + len))) {
				is_overlapping = true;
				break;
			}
		}

		if(is_overlapping) {
			continue;
		}
		
		if((r = svcQueryMemory(&memory_info, &page_info, (void*) addr)) != RESULT_OK) {
			goto fail_mutex;
		}
	} while(memory_info.memory_type != 0 || memory_info.memory_attribute != 0 || memory_info.permission != 0 || (uint64_t) memory_info.base_addr + memory_info.size < addr + len);

	memory_region_t *region = as_grab_region();
	if(region == NULL) {
		goto fail_mutex;
	}

	region->state = RESERVED_BY_USER;
	region->base = addr;
	region->size = len;

	trn_mutex_unlock(&as_lock);
	return (void*) addr;

fail_mutex:
	trn_mutex_unlock(&as_lock);
	return NULL;
}

void as_release(void *addr, size_t len) {
	trn_mutex_lock(&as_lock);
	for(uint64_t i = 0; i < num_regions; i++) {
		if(regions[i].base == (uint64_t) addr) {
			if(regions[i].size != len || regions[i].state != RESERVED_BY_USER) {
				trn_mutex_unlock(&as_lock);
				return;
			}
			as_delete_region(i);
			trn_mutex_unlock(&as_lock);
			return;
		}
	}
	trn_mutex_unlock(&as_lock);
}
