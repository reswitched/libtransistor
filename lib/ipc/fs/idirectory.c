#include<libtransistor/types.h>
#include<libtransistor/svc.h>
#include<libtransistor/ipc.h>
#include<libtransistor/err.h>
#include<libtransistor/util.h>
#include<libtransistor/ipc/sm.h>
#include<libtransistor/ipc/fs/idirectory.h>

result_t idirectory_read(idirectory_t obj, uint64_t *out_unk0, idirectoryentry_t * out_unk1, size_t out_unk1_size) {
	result_t res;
	ipc_request_t rq = ipc_default_request;
	rq.request_id = 0;

	ipc_response_fmt_t rs = ipc_default_response_fmt;
	uint8_t output_raw[8];
	rs.raw_data = output_raw;
	rs.raw_data_size = 8;

	ipc_buffer_t out_unk1_buf = {
		.addr = out_unk1,
		.size = out_unk1_size,
		.type = 6,
	};


	ipc_buffer_t *buffers[] = {
		&out_unk1_buf
	};
	rq.num_buffers = 1;
	rq.buffers = buffers;

	res = ipc_send(obj, &rq, &rs);
	*out_unk0 = (uint64_t)(rs.raw_data + 0);

	return res;
}

result_t idirectory_get_entry_count(idirectory_t obj, uint64_t *out_unk0) {
	result_t res;
	ipc_request_t rq = ipc_default_request;
	rq.request_id = 1;

	ipc_response_fmt_t rs = ipc_default_response_fmt;
	uint8_t output_raw[8];
	rs.raw_data = output_raw;
	rs.raw_data_size = 8;

	res = ipc_send(obj, &rq, &rs);
	*out_unk0 = (uint64_t)(rs.raw_data + 0);

	return res;
}
