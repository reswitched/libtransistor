#pragma once

#include<libtransistor/types.h>

typedef struct {
	uint32_t nvmap_handle;
	size_t size;
	uint32_t alignment;
	uint8_t kind;
} gpu_buffer_t;

result_t gpu_initialize();
result_t gpu_buffer_initialize(gpu_buffer_t *gpu_b, void *addr, size_t size, uint32_t heapmask, uint32_t flags, uint32_t alignment, uint8_t kind);
result_t gpu_buffer_get_id(gpu_buffer_t *gpu_b, uint32_t *id);
result_t gpu_buffer_initialize_from_id(gpu_buffer_t *gpu_b, uint32_t id);
void gpu_finalize();
