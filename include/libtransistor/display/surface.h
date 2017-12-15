#pragma once

#include<libtransistor/types.h>
#include<libtransistor/display/graphic_buffer_queue.h>

typedef enum {
	SURFACE_STATE_INVALID,
	SURFACE_STATE_DEQUEUED,
	SURFACE_STATE_QUEUED,
} surface_state_t;

typedef struct {
	uint64_t layer_id;
	igbp_t igbp;
	surface_state_t state;
	bool has_requested[2];
	uint32_t current_slot;

	gpu_buffer_t gpu_buffer;
	uint32_t *gpu_buffer_memory;
	uint32_t *gpu_buffer_memory_alloc;

	graphic_buffer_t graphic_buffers[2];
} surface_t;

result_t surface_create(surface_t *surface, uint64_t layer_id, igbp_t igbp);
// for now, we ignore fences
result_t surface_dequeue_buffer(surface_t *surface, uint32_t **image);
result_t surface_queue_buffer(surface_t *surface);
// no surface_destroy() yet
