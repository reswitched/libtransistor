#include<libtransistor/types.h>
#include<libtransistor/err.h>
#include<libtransistor/svc.h>
#include<libtransistor/ipc/vi.h>
#include<libtransistor/display/graphic_buffer_queue.h>
#include<libtransistor/display/surface.h>

#include<malloc.h>
#include<stdio.h>

static uint8_t __attribute__((aligned(0x1000))) gpu_buffer_memory[0x780000];

result_t surface_create(surface_t *surface, uint64_t layer_id, igbp_t igbp) {
	surface->layer_id = layer_id;
	surface->igbp = igbp;
	surface->state = SURFACE_STATE_INVALID;
	for(int i = 0; i < 2; i++) {
		surface->has_requested[i] = false;
	}
	surface->current_slot = 0;

	result_t r;

	int status;
	queue_buffer_output_t qbo;
	if((r = igbp_connect(&surface->igbp, 2, false, &status, &qbo)) != RESULT_OK) {
		goto fail;
	}
	if(status != 0) {
		r = LIBTRANSISTOR_ERR_SURFACE_CONNECT_FAILED;
		goto fail_connect;
	}

	// TODO: malloc_aligned?
	//surface->gpu_buffer_memory_alloc = malloc(0x780000 + 0xfff);
	//if(surface->gpu_buffer_memory_alloc == NULL) {
	//	return LIBTRANSISTOR_ERR_OUT_OF_MEMORY;
	//}
	//printf("gpu_buffer_memory_alloc: %p\n", surface->gpu_buffer_memory_alloc);
	//surface->gpu_buffer_memory = (uint32_t*) (((uint64_t) surface->gpu_buffer_memory_alloc + 0xfff) & 0xFFFFFFFFFFFFF000);
	//printf("gpu_buffer_memory: %p\n", surface->gpu_buffer_memory);

	surface->gpu_buffer_memory = gpu_buffer_memory;
	
	if((r = svcSetMemoryAttribute(surface->gpu_buffer_memory, 0x780000, 0x8, 0x8)) != RESULT_OK) {
		printf("failed svcsma\n");
		goto fail_memory;
	}

	printf("passed svcsma\n");

	if((r = gpu_buffer_initialize(
		    &surface->gpu_buffer,
		    surface->gpu_buffer_memory,
		    0x780000, 0, 0, 0x1000, 0)) != RESULT_OK) {
		goto fail_memory_attribute;
	}

	graphic_buffer_t gb_common;
	gb_common.width = qbo.width;
	gb_common.height = qbo.height;
	gb_common.stride = qbo.width;
	gb_common.format = RGBA_8888;
	gb_common.usage = 0xb00;
	gb_common.gpu_buffer = &surface->gpu_buffer;

	for(int i = 0; i < 2; i++) {
		surface->graphic_buffers[i] = gb_common;
		surface->graphic_buffers[i].unknown = 0x3c0000 * i; // TODO: this isn't unknown; this is the offset within the gpu_buffer where the pixel data lives
	}

	for(int i = 0; i < 2; i++) {
		if((r = igbp_set_preallocated_buffer(&surface->igbp, i, &surface->graphic_buffers[i])) != RESULT_OK) {
			goto fail_memory_attribute;
		}
	}
	
	surface->state = SURFACE_STATE_QUEUED;

	return RESULT_OK;
	
fail_memory_attribute:
	svcSetMemoryAttribute(surface->gpu_buffer_memory, 0x3c0000, 0x0, 0x0);
fail_memory:
	//free(surface->gpu_buffer_memory_alloc);
fail_connect:
	igbp_disconnect(&surface->igbp, 2, ALL_LOCAL, &status);
fail:
	surface->state = SURFACE_STATE_INVALID;
	return r;
}

void surface_destroy(surface_t *surface) {
	int status;
	igbp_disconnect(&surface->igbp, 2, ALL_LOCAL, &status);
	vi_adjust_refcount(surface->igbp.igbp_binder.handle, -1, 1);
	vi_destroy_managed_layer(surface->layer_id);
	surface->state = SURFACE_STATE_INVALID;
	
	gpu_buffer_destroy(&surface->gpu_buffer, NULL, NULL);
	
	svcSetMemoryAttribute(surface->gpu_buffer_memory, 0x780000, 0x0, 0x0);
	// TODO: free memory
}

result_t surface_dequeue_buffer(surface_t *surface, uint32_t **image) {
	result_t r;

	if(surface->state != SURFACE_STATE_QUEUED) {
		return  LIBTRANSISTOR_ERR_SURFACE_INVALID_STATE;
	}

	int status;
	fence_t fence;
	if((r = igbp_dequeue_buffer(
		    &surface->igbp,
		    1280, 720, 1, 0xb00,
		    false, &status, &surface->current_slot,
		    &fence, NULL)) != RESULT_OK) {
		return r;
	}

	if(status != 0) {
		return LIBTRANSISTOR_ERR_SURFACE_DEQUEUE_BUFFER_FAILED;
	}

	if(!surface->has_requested[surface->current_slot]) {
		graphic_buffer_t graphic_buffer;
		if((r = igbp_request_buffer(
			    &surface->igbp, surface->current_slot, &status,
			    &graphic_buffer)) != RESULT_OK) {
			return r;
		}

		// TODO: find a way to map this buffer and use it instead of
		//   using the memory we originally made the buffer with

		surface->has_requested[surface->current_slot] = true;
	}

	*image = surface->gpu_buffer_memory + ((surface->current_slot * 0x3c0000) / sizeof(uint32_t));

	surface->state = SURFACE_STATE_DEQUEUED;
	
	return RESULT_OK;
}

result_t surface_queue_buffer(surface_t *surface) {
	result_t r;

	if(surface->state != SURFACE_STATE_DEQUEUED) {
		return LIBTRANSISTOR_ERR_SURFACE_INVALID_STATE;
	}
	
	queue_buffer_output_t qbo;
	int status;
	if((r = igbp_queue_buffer(&surface->igbp, surface->current_slot,
	                          NULL, &qbo, &status)) != RESULT_OK) {
		return r;
	}

	if(status != 0) {
		return LIBTRANSISTOR_ERR_SURFACE_QUEUE_BUFFER_FAILED;
	}

	surface->state = SURFACE_STATE_QUEUED;
	
	return RESULT_OK;
}
