/**
 * @file libtransistor/display/surface.h
 * @brief Display surface data structures and functions
 */

#pragma once

#include<libtransistor/types.h>
#include<libtransistor/display/graphic_buffer_queue.h>

/**
* @enum surface_state_t
* @brief Keeps track of the internal state of a \ref surface_t
*/
typedef enum {
	SURFACE_STATE_INVALID,
	SURFACE_STATE_DEQUEUED,
	SURFACE_STATE_QUEUED,
} surface_state_t;


/**
* @struct surface_t
* @brief A surface that can be drawn to
*/
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

/**
* @brief Create a new Surface
*
* @param surface Structure to initialize
* @param layer_id ID of the existing layer
* @param igbp IGraphicBufferProducer to use for submitting buffers
*/
result_t surface_create(surface_t *surface, uint64_t layer_id, igbp_t igbp);

/**
* @brief Acquire a buffer for rendering
*
* @param surface Surface to dequeue buffer from
* @param image Returns a pointer to the swizzled pixel data buffer to render to.
*
* Using \ref gfx_slow_swizzling_blit is recommended. Call \ref surface_queue_buffer
* when you're done rendering to submit it to be displayed.
*/
// for now, we ignore fences
result_t surface_dequeue_buffer(surface_t *surface, uint32_t **image);

/**
* @brief Submit the current buffer to be displayed
*
* @param surface Surface to submit buffer for
*/
result_t surface_queue_buffer(surface_t *surface);
// no surface_destroy() yet
