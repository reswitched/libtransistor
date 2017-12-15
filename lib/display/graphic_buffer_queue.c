#include<libtransistor/err.h>
#include<libtransistor/types.h>
#include<libtransistor/util.h>
#include<libtransistor/display/binder.h>
#include<libtransistor/display/graphic_buffer.h>
#include<libtransistor/display/fence.h>
#include<libtransistor/display/graphic_buffer_queue.h>

#include<string.h>

#define INTERFACE_TOKEN "android.gui.IGraphicBufferProducer"

enum {
	REQUEST_BUFFER = 0x1,
	SET_BUFFER_COUNT = 0x2,
	DEQUEUE_BUFFER = 0x3,
	DETACH_BUFFER = 0x4,
	DETACH_NEXT_BUFFER = 0x5,
	ATTACH_BUFFER = 0x6,
	QUEUE_BUFFER = 0x7,
	CANCEL_BUFFER = 0x8,
	QUERY = 0x9,
	CONNECT = 0xA,
	DISCONNECT = 0xB,
	// 0xC might be SET_SIDEBAND_STREAM but I'm not sure
	ALLOCATE_BUFFERS = 0xD,
	SET_PREALLOCATED_BUFFER = 0xE
};

static result_t queue_buffer_output_unflatten(parcel_t *parcel, queue_buffer_output_t *qbo) {
	if(parcel_read_remaining(parcel) < 4*sizeof(uint32_t)) {
		return LIBTRANSISTOR_ERR_PARCEL_DATA_UNDERRUN;
	}

	qbo->width = parcel_read_u32(parcel);
	qbo->height = parcel_read_u32(parcel);
	qbo->transform_hint = parcel_read_u32(parcel);
	qbo->num_pending_buffers = parcel_read_u32(parcel);

	return RESULT_OK;
}

static result_t queue_buffer_input_flatten(parcel_t *parcel, queue_buffer_input_t *qbi) {
	static uint32_t ts32 = 0x588bbba9;
	uint32_t template[] = {
		0x54, 0, // unknown, but always these values
		ts32, 0x0, //u64 timestamp
		1, 0, 0, // unknown, but always these values
		0, 0, // sometimes zero
		0,
		0, // also seen 2

		0, 0,

		// fence?
		1, 1, 0xa3, 0x0,
		-1, 0, -1, 0, -1, 0
	};

	ts32++;
	//ts32+= 0x2e45f00;

	memcpy(parcel_write_inplace(parcel, sizeof(template)), &template, sizeof(template));
  
	return RESULT_OK;
}

static result_t graphic_buffer_flatten(parcel_t *parcel, graphic_buffer_t *gb) {
	result_t r;
  
	uint8_t *out = parcel_write_inplace(parcel, 0x16c);

	uint32_t gpu_buffer_id;
	if((r = gpu_buffer_get_id(gb->gpu_buffer, &gpu_buffer_id)) != RESULT_OK) {
		return r;
	}

	// not really sure why I need this?
	gpu_buffer_t gpu_buffer_copy;
	if((r = gpu_buffer_initialize_from_id(&gpu_buffer_copy, gpu_buffer_id)) != RESULT_OK) {
		return r;
	}
  
	/*
	  RFBG, width, height, stride,
	  format, usage, 0x2a [mId >> 32?], [some kind of native handle thing?] [v38 points here] [mId & 0xFFFFFFFF] index
	  0x0 [numFds?], 0x51 [numInts?], -1 {592}, gpu_buffer_id {593},
	  0x0, 0xdaffcaff {582}, -1 [0x2a?] {583}, v39 [0x0] {584},
	  v5 [0xb00] {585}, v4 [0x1] {586}, v4 [0x1] {587}, 0 [0x500] {588}
	  v31 [0x3c0000] {589}, v22 [0x1] {590}, uninit?,

	  memcpied from &v53, length 88 * v22

	  zeroes? {581 clears from v38+12 to the end of this block}

	  0x0 {594}, 0x0 {594}
	*/
  
	uint32_t template[] = {
		0x47424652, gb->width,  gb->height, gb->stride,
		gb->format, gb->usage,  0x0000002a, gb->index,
		0x00000000, 0x00000051,  0xffffffff, gpu_buffer_id,
		0x00000000, 0xdaffcaff,  0x0000002a, 0x00000000,
		0x00000b00, 0x00000001,  0x00000001, 0x00000500,
		0x003c0000, 0x00000001,  0x00000000, 0x00000500,
		0x000002d0, 0x00532120,  0x00000001, 0x00000003,
		0x00001400, gpu_buffer_copy.nvmap_handle,  gb->unknown, 0x000000fe,
		0x00000004, 0x00000000,  0x00000000, 0x00000000,
		0x00000000, 0x003c0000,  0x00000000, 0x00000000,
		0x00000000, 0x00000000,  0x00000000, 0x00000000,
		0x00000000, 0x00000000,  0x00000000, 0x00000000,
		0x00000000, 0x00000000,  0x00000000, 0x00000000,
		0x00000000, 0x00000000,  0x00000000, 0x00000000,
		0x00000000, 0x00000000,  0x00000000, 0x00000000,
		0x00000000, 0x00000000,  0x00000000, 0x00000000,
		0x00000000, 0x00000000,  0x00000000, 0x00000000,
		0x00000000, 0x00000000,  0x00000000, 0x00000000,
		0x00000000, 0x00000000,  0x00000000, 0x00000000,
		0x00000000, 0x00000000,  0x00000000, 0x00000000,
		0x00000000, 0x00000000,  0x00000000, 0x00000000,
		0x00000000, 0x00000000,  0x00000000, 0x00000000,
		0x00000000, 0x0, 0x0 // these last two words are some kind of address but I don't think it really matters
	};

	memcpy(out, template, 0x16c);
	return RESULT_OK;
}

static result_t fence_unflatten(parcel_t *parcel, fence_t *fence) {
	memcpy(fence, parcel_read_inplace(parcel, sizeof(*fence)), sizeof(*fence));
	return RESULT_OK;
}

result_t igbp_request_buffer(igbp_t *igbp, int slot, int *status, graphic_buffer_t *gb) {
	result_t r;

	parcel_t parcel;
	parcel_initialize(&parcel);

	parcel_write_interface_token(&parcel, INTERFACE_TOKEN);
	parcel_write_u32(&parcel, slot);

	parcel_t response;
	if((r = binder_transact_parcel(&(igbp->igbp_binder), REQUEST_BUFFER, 0, &parcel, &response)) != RESULT_OK) {
		return r;
	}

	bool non_null = parcel_read_u32(&response) != 0;
	if(non_null) {
		int length = parcel_read_u32(&response);
		if(length != 0x16c) {
			return LIBTRANSISTOR_ERR_DISPLAY_GRAPHIC_BUFFER_LENGTH_MISMATCH;
		}
		int unknown = parcel_read_u32(&response);
		void *gb_flat = parcel_read_inplace(&response, 0x16c);
	}
	*status = parcel_read_u32(&response);
  
	return RESULT_OK;
}

result_t igbp_dequeue_buffer(igbp_t *igbp, uint32_t width, uint32_t height, pixel_format_t pixel_format, uint32_t usage, bool get_frame_timestamps, int *status, int *slot, fence_t *fence, frame_event_history_delta_t *out_timestamps) {
	if(get_frame_timestamps) {
		return LIBTRANSISTOR_ERR_UNIMPLEMENTED;    
	}

	result_t r;

	parcel_t parcel;
	parcel_initialize(&parcel);

	parcel_write_interface_token(&parcel, INTERFACE_TOKEN);
	parcel_write_u32(&parcel, pixel_format);
	parcel_write_u32(&parcel, width);
	parcel_write_u32(&parcel, height);
	parcel_write_u32(&parcel, get_frame_timestamps ? 1 : 0);
	parcel_write_u32(&parcel, usage);

	parcel_t response;
	if((r = binder_transact_parcel(&(igbp->igbp_binder), DEQUEUE_BUFFER, 0, &parcel, &response)) != RESULT_OK) {
		return r;
	}

	*slot = parcel_read_u32(&response);
	if((r = fence_unflatten(&response, fence)) != RESULT_OK) {
		return r;
	}
	*status = parcel_read_u32(&response);

	return RESULT_OK;
}

result_t igbp_queue_buffer(igbp_t *igbp, int slot, queue_buffer_input_t *qbi, queue_buffer_output_t *qbo, int *status) {
	result_t r;
  
	parcel_t parcel;
	parcel_initialize(&parcel);

	parcel_write_interface_token(&parcel, INTERFACE_TOKEN);
	parcel_write_u32(&parcel, slot);
	if((r = queue_buffer_input_flatten(&parcel, qbi)) != RESULT_OK) {
		return r;
	}

	parcel_t response;
	if((r = binder_transact_parcel(&(igbp->igbp_binder), QUEUE_BUFFER, 0, &parcel, &response)) != RESULT_OK) {
		return r;
	}

	if((r = queue_buffer_output_unflatten(&response, qbo)) != RESULT_OK) {
		return r;
	}

	*status = parcel_read_u32(&response);

	return RESULT_OK;
}

result_t igbp_cancel_buffer(igbp_t *igbp, int slot, fence_t *fence) {
	return LIBTRANSISTOR_ERR_UNIMPLEMENTED;
}

result_t igbp_query(igbp_t *igbp, int what, int *status, int *value) {
	return LIBTRANSISTOR_ERR_UNIMPLEMENTED;
}

result_t igbp_connect(igbp_t *igbp, int api, bool producer_controlled_by_app, int *status, queue_buffer_output_t *qbo) {
	result_t r;
  
	parcel_t parcel;
	parcel_initialize(&parcel);

	parcel_write_interface_token(&parcel, INTERFACE_TOKEN);
	parcel_write_u32(&parcel, 0); // IProducerListener is null because we don't support it in libtransistor (yet)
	parcel_write_u32(&parcel, api);
	parcel_write_u32(&parcel, producer_controlled_by_app ? 1 : 0);

	parcel_t response;
	r = binder_transact_parcel(&(igbp->igbp_binder), CONNECT, 0, &parcel, &response);
	if(r) {
		return r;
	}

	r = queue_buffer_output_unflatten(&response, qbo);
	if(r) {
		return r;
	}

	if(parcel_read_remaining(&response) < sizeof(uint32_t)) {
		return LIBTRANSISTOR_ERR_PARCEL_DATA_UNDERRUN;
	}

	*status = parcel_read_u32(&response);

	return RESULT_OK;
}

result_t igbp_set_preallocated_buffer(igbp_t *igbp, int slot, graphic_buffer_t *gb) {
	result_t r;

	parcel_t parcel;
	parcel_initialize(&parcel);
	parcel_write_interface_token(&parcel, INTERFACE_TOKEN);
	parcel_write_u32(&parcel, slot);
	parcel_write_u32(&parcel, 1); // unknown

	parcel_write_u32(&parcel, 0x16c); // flattened GraphicBuffer length
	parcel_write_u32(&parcel, 0); // ???

	r = graphic_buffer_flatten(&parcel, gb);
	if(r) {
		return r;
	}

	parcel_t response;
	r = binder_transact_parcel(&(igbp->igbp_binder), SET_PREALLOCATED_BUFFER, 0, &parcel, &response);
	if(r) {
		return r;
	}
  
	return RESULT_OK;
}
