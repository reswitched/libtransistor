#include<libtransistor/types.h>
#include<libtransistor/svc.h>
#include<libtransistor/ipc.h>
#include<libtransistor/err.h>
#include<libtransistor/util.h>
#include<libtransistor/ipc/sm.h>
#include<libtransistor/ipc/fs/ifile.h>
#include<string.h>


result_t ifile_read(ifile_t obj, uint64_t *out_out_size, int8_t * out_out_buf, size_t out_out_buf_size, uint64_t in_unk0, uint64_t in_offset, uint64_t in_size) {
	result_t res;
	ipc_request_t rq = ipc_default_request;
	rq.request_id = 0;

	uint8_t raw[24];
	rq.raw_data = raw;
	rq.raw_data_size = 24;

	*(uint64_t*)(raw + 0) = in_unk0;
	*(uint64_t*)(raw + 8) = in_offset;
	*(uint64_t*)(raw + 16) = in_size;


	ipc_response_fmt_t rs = ipc_default_response_fmt;
	uint8_t output_raw[8];
	rs.raw_data = output_raw;
	rs.raw_data_size = 8;

	ipc_buffer_t out_out_buf_buf = {
		.addr = out_out_buf,
		.size = out_out_buf_size,
		.type = 70,
	};


	ipc_buffer_t *buffers[] = {
		&out_out_buf_buf
	};
	rq.num_buffers = 1;
	rq.buffers = buffers;

	res = ipc_send(obj, &rq, &rs);
	*out_out_size = *(uint64_t*)(output_raw + 0);

	return res;
}

result_t ifile_write(ifile_t obj, uint32_t in_unk0, uint64_t in_offset, uint64_t in_size, const int8_t * in_buf, size_t in_buf_size) {
	result_t res;
	ipc_request_t rq = ipc_default_request;
	rq.request_id = 1;

	uint8_t raw[24];
	rq.raw_data = raw;
	rq.raw_data_size = 20;

	*(uint32_t*)(raw + 0) = in_unk0;
	*(uint64_t*)(raw + 8) = in_offset;
	*(uint32_t*)(raw + 16) = in_size;
	ipc_buffer_t in_buf_buf = {
		.addr = in_buf,
		.size = in_buf_size,
		.type = 69,
	};


	ipc_response_fmt_t rs = ipc_default_response_fmt;
	ipc_buffer_t *buffers[] = {
		&in_buf_buf
	};
	rq.num_buffers = 1;
	rq.buffers = buffers;

	res = ipc_send(obj, &rq, &rs);
	return res;
}

result_t ifile_flush(ifile_t obj) {
	result_t res;
	ipc_request_t rq = ipc_default_request;
	rq.request_id = 2;

	ipc_response_fmt_t rs = ipc_default_response_fmt;
	res = ipc_send(obj, &rq, &rs);
	return res;
}

result_t ifile_set_size(ifile_t obj, uint64_t in_size) {
	result_t res;
	ipc_request_t rq = ipc_default_request;
	rq.request_id = 3;

	uint8_t raw[8];
	rq.raw_data = raw;
	rq.raw_data_size = 8;

	*(uint64_t*)(raw + 0) = in_size;


	ipc_response_fmt_t rs = ipc_default_response_fmt;
	res = ipc_send(obj, &rq, &rs);
	return res;
}

result_t ifile_get_size(ifile_t obj, uint64_t *out_fileSize) {
	result_t res;
	ipc_request_t rq = ipc_default_request;
	rq.request_id = 4;

	ipc_response_fmt_t rs = ipc_default_response_fmt;
	uint8_t output_raw[8];
	rs.raw_data = output_raw;
	rs.raw_data_size = 8;

	res = ipc_send(obj, &rq, &rs);
	*out_fileSize = *(uint64_t*)(output_raw + 0);

	return res;
}
