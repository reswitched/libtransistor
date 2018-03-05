#include<libtransistor/types.h>
#include<libtransistor/svc.h>
#include<libtransistor/ipc.h>
#include<libtransistor/err.h>
#include<libtransistor/util.h>
#include<libtransistor/internal_util.h>
#include<libtransistor/ipc/sm.h>
#include<libtransistor/ipc/audio.h>

#include<assert.h>

static int audio_ipc_initializations = 0;

static ipc_object_t iaom_object; // IAudioOutManager

result_t audio_ipc_init() {
	if(audio_ipc_initializations++ > 0) {
		return RESULT_OK;
	}

	result_t r;
	r = sm_init();
	if(r) {
		goto fail;
	}
	
	r = sm_get_service(&iaom_object, "audout:u");
	if(r) {
		goto fail_sm;
	}

	sm_finalize();
	return 0;

fail_sm:
	sm_finalize();
fail:
	audio_ipc_initializations--;
	return r;
}

result_t audio_ipc_list_outputs(char (*names)[0x20], int max_names, uint32_t *num_names) {
	INITIALIZATION_GUARD(audio_ipc);
	
	ipc_buffer_t names_buffer;
	names_buffer.addr = names;
	names_buffer.size = sizeof(names[0]) * max_names;
	names_buffer.type = 6;

	ipc_buffer_t *buffers[] = {&names_buffer};

	ipc_request_t rq = ipc_default_request;
	rq.request_id = 0; // I'm pretty sure that IAudioOutManager#2 is the same, except takes a type 0x22 buffer instead of 0x6
	rq.num_buffers = 1;
	rq.buffers = buffers;

	ipc_response_fmt_t rs = ipc_default_response_fmt;
	rs.raw_data_size = sizeof(*num_names);
	rs.raw_data = num_names;

	return ipc_send(iaom_object, &rq, &rs);
}

result_t audio_ipc_open_output(const char name[0x20], audio_output_t *out) {
	INITIALIZATION_GUARD(audio_ipc);

	ipc_buffer_t name_in_buffer;
	name_in_buffer.addr = (char*) name;
	name_in_buffer.size = 0x20;
	name_in_buffer.type = 5;

	uint8_t name_out_buffer_storage[0x100];
	ipc_buffer_t name_out_buffer; // not sure what's up with this?
	name_out_buffer.addr = name_out_buffer_storage;
	name_out_buffer.size = sizeof(name_out_buffer_storage);
	name_out_buffer.type = 6;

	ipc_buffer_t *buffers[] = {&name_in_buffer, &name_out_buffer};

	struct {
		uint64_t unknown0;
		uint64_t unknown1; // probably a pid-copy thing
	} rq_data;
	rq_data.unknown0 = 0xcafe000000000000;
	rq_data.unknown1 = 0;

	handle_t copy_handles[] = {0xffff8001}; // current process
	
	ipc_request_t rq = ipc_default_request;
	rq.request_id = 1;
	rq.send_pid = true;
	rq.num_copy_handles = 1;
	rq.copy_handles = copy_handles;
	rq.raw_data_size = sizeof(rq_data);
	rq.raw_data = (uint32_t*) &rq_data;
	rq.num_buffers = 2;
	rq.buffers = buffers;

	struct {
		uint32_t sample_rate;
		uint32_t channel_count;
		uint32_t pcm_format;
		uint32_t unknown;
	} rs_data;
	
	ipc_response_fmt_t rs = ipc_default_response_fmt;
	rs.raw_data_size = sizeof(rs_data);
	rs.raw_data = (uint32_t*) &rs_data;
	rs.num_objects = 1;
	rs.objects = &out->object;
	
	result_t r;
	if((r = ipc_send(iaom_object, &rq, &rs)) != RESULT_OK) {
		return r;
	}

	out->num_channels = rs_data.channel_count;
	out->sample_format = rs_data.pcm_format;
	out->sample_rate = rs_data.sample_rate;

	return RESULT_OK;
}

result_t audio_ipc_output_get_state(audio_output_t *out, audio_output_state_t *state) {
	INITIALIZATION_GUARD(audio_ipc);

	ipc_request_t rq = ipc_default_request;
	rq.request_id = 0;

	ipc_response_fmt_t rs = ipc_default_response_fmt;
	rs.raw_data_size = sizeof(*state);
	rs.raw_data = (uint32_t*) state;

	return ipc_send(out->object, &rq, &rs);
}

result_t audio_ipc_output_start(audio_output_t *out) {
	INITIALIZATION_GUARD(audio_ipc);

	ipc_request_t rq = ipc_default_request;
	rq.request_id = 1;

	return ipc_send(out->object, &rq, &ipc_default_response_fmt);
}

result_t audio_ipc_output_stop(audio_output_t *out) {
	INITIALIZATION_GUARD(audio_ipc);

	ipc_request_t rq = ipc_default_request;
	rq.request_id = 2;

	return ipc_send(out->object, &rq, &ipc_default_response_fmt);
}

result_t audio_ipc_output_register_buffer_event(audio_output_t *out, handle_t *event) {
	INITIALIZATION_GUARD(audio_ipc);

	ipc_request_t rq = ipc_default_request;
	rq.request_id = 4;

	ipc_response_fmt_t rs = ipc_default_response_fmt;
	rs.num_copy_handles = 1;
	rs.copy_handles = event;
	
	return ipc_send(out->object, &rq, &rs);
}

result_t audio_ipc_output_append_buffer(audio_output_t *out, audio_output_buffer_t *buffer) {
	INITIALIZATION_GUARD(audio_ipc);

	uint64_t key = (uint64_t) buffer; // this meaning is guessed

	static_assert(sizeof(*buffer) == 0x28, "audio_output_buffer_t is 0x28 bytes long");

	ipc_buffer_t ipc_buffer;
	ipc_buffer.addr = buffer;
	ipc_buffer.size = sizeof(*buffer);
	ipc_buffer.type = 5;

	ipc_buffer_t *buffers[] = {&ipc_buffer};
	
	ipc_request_t rq = ipc_default_request;
	rq.request_id = 3;
	rq.raw_data_size = sizeof(key);
	rq.raw_data = (uint32_t*) &key;
	rq.num_buffers = 1;
	rq.buffers = buffers;

	return ipc_send(out->object, &rq, &ipc_default_response_fmt);
}

result_t audio_ipc_output_get_released_buffer(audio_output_t *out, uint32_t *num_released, audio_output_buffer_t **buffer) {
	INITIALIZATION_GUARD(audio_ipc);

	ipc_buffer_t ipc_buffer;
	ipc_buffer.addr = buffer;
	ipc_buffer.size = sizeof(*buffer);
	ipc_buffer.type = 6;

	ipc_buffer_t *buffers[] = {&ipc_buffer};
	
	ipc_request_t rq = ipc_default_request;
	rq.request_id = 5;
	rq.num_buffers = 1;
	rq.buffers = buffers;

	ipc_response_fmt_t rs = ipc_default_response_fmt;
	rs.raw_data_size = sizeof(uint32_t);
	rs.raw_data = (uint32_t*) num_released;
	
	return ipc_send(out->object, &rq, &rs);
}

result_t audio_ipc_output_contains_buffer(audio_output_t *out, audio_output_buffer_t *buffer, bool *contains) {
	INITIALIZATION_GUARD(audio_ipc);

	uint64_t key = (uint64_t) buffer; // this meaning is guessed
	
	ipc_request_t rq = ipc_default_request;
	rq.request_id = 6;
	rq.raw_data_size = sizeof(key);
	rq.raw_data = (uint32_t*) &key;
	
	uint32_t padded_bool;
	
	ipc_response_fmt_t rs = ipc_default_response_fmt;
	rs.raw_data_size = sizeof(padded_bool);
	rs.raw_data = &padded_bool;
	
	result_t r;
	if((r = ipc_send(out->object, &rq, &rs)) != RESULT_OK) {
		return r;
	}

	*contains = (bool) padded_bool;

	return RESULT_OK;
}

void audio_ipc_output_close(audio_output_t *out) {
	ipc_close(out->object);
}

static void audio_ipc_force_finalize() {
	ipc_close(iaom_object);
	audio_ipc_initializations = 0;
}

void audio_ipc_finalize() {
	if(--audio_ipc_initializations == 0) {
		audio_ipc_force_finalize();
	}
}

static __attribute__((destructor)) void audio_ipc_destruct() {
	if(audio_ipc_initializations > 0) {
		audio_ipc_force_finalize();
	}
}
