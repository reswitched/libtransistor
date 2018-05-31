#include<libtransistor/types.h>
#include<libtransistor/err.h>
#include<libtransistor/svc.h>
#include<libtransistor/ipc/vi.h>
#include<libtransistor/display/graphic_buffer_queue.h>
#include<libtransistor/display/surface.h>
#include<libtransistor/alloc_pages.h>
#include<libtransistor/util.h>

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

	const uint64_t num_buffers = ARRAY_LENGTH(surface->graphic_buffers);
	size_t buffer_size = num_buffers * 0x3c0000;
	
	surface->gpu_buffer_memory = alloc_pages(buffer_size, buffer_size, NULL);
	if(surface->gpu_buffer_memory == NULL) {
		return LIBTRANSISTOR_ERR_OUT_OF_MEMORY;
	}

	if((r = svcSetMemoryAttribute(surface->gpu_buffer_memory, buffer_size, 0x8, 0x8)) != RESULT_OK) {
		goto fail_memory;
	}

	if((r = gpu_buffer_initialize(
		    &surface->gpu_buffer,
		    surface->gpu_buffer_memory,
		    buffer_size, 0, 0, 0x1000, 0)) != RESULT_OK) {
		goto fail_memory_attribute;
	}

	graphic_buffer_t gb_common;
	gb_common.width = qbo.width;
	gb_common.height = qbo.height;
	gb_common.stride = qbo.width;
	gb_common.format = RGBA_8888;
	gb_common.usage = 0xb00;
	gb_common.gpu_buffer = &surface->gpu_buffer;

	for(int i = 0; i < ARRAY_LENGTH(surface->graphic_buffers); i++) {
		surface->graphic_buffers[i] = gb_common;
		surface->graphic_buffers[i].unknown = 0x3c0000 * i; // TODO: this isn't unknown; this is the offset within the gpu_buffer where the pixel data lives
	}

	for(int i = 0; i < ARRAY_LENGTH(surface->graphic_buffers); i++) {
		if((r = igbp_set_preallocated_buffer(&surface->igbp, i, &surface->graphic_buffers[i])) != RESULT_OK) {
			goto fail_memory_attribute;
		}
	}
	
	surface->state = SURFACE_STATE_QUEUED;

	return RESULT_OK;
	
fail_memory_attribute:
	svcSetMemoryAttribute(surface->gpu_buffer_memory, 0x3c0000, 0x0, 0x0);
fail_memory:
	free_pages(surface->gpu_buffer_memory);
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
	vi_close_layer(surface->layer_id);
	vi_destroy_managed_layer(surface->layer_id);
	surface->state = SURFACE_STATE_INVALID;
	
	gpu_buffer_destroy(&surface->gpu_buffer, NULL, NULL);
	
	svcSetMemoryAttribute(surface->gpu_buffer_memory, 0x3c0000 * ARRAY_LENGTH(surface->graphic_buffers), 0x0, 0x0);
	
	free_pages(surface->gpu_buffer_memory);
}

result_t surface_dequeue_buffer(surface_t *surface, uint32_t **image) {
	result_t r;

	if(surface->state != SURFACE_STATE_QUEUED) {
		return  LIBTRANSISTOR_ERR_SURFACE_INVALID_STATE;
	}

	int status;
	if((r = igbp_dequeue_buffer(
		    &surface->igbp,
		    1280, 720, 1, 0xb00,
		    false, &status, &surface->current_slot,
		    &surface->current_fence, NULL)) != RESULT_OK) {
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

	queue_buffer_input_t qbi;
	qbi.size = sizeof(qbi) - 0x8;
	qbi.num_fds = 0;
	qbi.timestamp = 0;
	qbi.is_auto_timestamp = 0;
	qbi.crop.left = 0;
	qbi.crop.top = 0;
	qbi.crop.right = 0;
	qbi.crop.bottom = 0;
	qbi.scaling_mode = 0;
	qbi.transform = 0;
	qbi.sticky_transform = 0;
	qbi.unknown[0] = 0;
	qbi.unknown[1] = 1;
	qbi.fence.is_valid = 1;
	for(size_t i = 0; i < ARRAY_LENGTH(qbi.fence.sync); i++) {
		qbi.fence.sync[i].syncpt_id = 0xffffffff;
		qbi.fence.sync[i].syncpt_value = 0;
	}
	
	queue_buffer_output_t qbo;
	int status;
	if((r = igbp_queue_buffer(&surface->igbp, surface->current_slot,
	                          &qbi, &qbo, &status)) != RESULT_OK) {
		return r;
	}

	if(status != 0) {
		return LIBTRANSISTOR_ERR_SURFACE_QUEUE_BUFFER_FAILED;
	}

	surface->state = SURFACE_STATE_QUEUED;
	
	return RESULT_OK;
}

result_t surface_wait_buffer(surface_t *surface) {
	if(surface->state != SURFACE_STATE_DEQUEUED) {
		return LIBTRANSISTOR_ERR_SURFACE_INVALID_STATE;
	}

	if(!surface->current_fence.is_valid) {
		return RESULT_OK;
	}

	for(size_t i = 0; i < ARRAY_LENGTH(surface->current_fence.sync); i++) {
		result_t r;
		gpu_fence_t *f = &surface->current_fence.sync[i];
		if(f->syncpt_id == 0xffffffff) {
			continue;
		}
		if((r = gpu_wait_fence(f, -1)) != RESULT_OK) {
			return r;
		}
	}

	return RESULT_OK;
}
