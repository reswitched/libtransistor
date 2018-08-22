#include<libtransistor/ipc/fs/ifilesystem.h>

#include<libtransistor/types.h>
#include<libtransistor/svc.h>
#include<libtransistor/ipc.h>
#include<libtransistor/err.h>
#include<libtransistor/util.h>
#include<libtransistor/ipc/sm.h>
#include<string.h>

result_t ifilesystem_create_file(ifilesystem_t obj, uint32_t in_mode, uint64_t in_size, const char in_path[0x301]) {
	result_t res;
	ipc_request_t rq = ipc_default_request;
	rq.request_id = 0;

	uint8_t raw[16];
	rq.raw_data = raw;
	rq.raw_data_size = 16;

	*(uint32_t*)(raw + 0) = in_mode;
	*(uint64_t*)(raw + 8) = in_size;
	ipc_buffer_t in_path_buf = {
		.addr = (void*) in_path,
		.size = 769,
		.type = 25,
	};


	ipc_response_fmt_t rs = ipc_default_response_fmt;
	ipc_buffer_t *buffers[] = {
		&in_path_buf
	};
	rq.num_buffers = 1;
	rq.buffers = buffers;

	res = ipc_send(obj, &rq, &rs);
	return res;
}

result_t ifilesystem_delete_file(ifilesystem_t obj, const char in_path[0x301]) {
	result_t res;
	ipc_request_t rq = ipc_default_request;
	rq.request_id = 1;

	ipc_buffer_t in_path_buf = {
		.addr = (void*) in_path,
		.size = 769,
		.type = 25,
	};


	ipc_response_fmt_t rs = ipc_default_response_fmt;
	ipc_buffer_t *buffers[] = {
		&in_path_buf
	};
	rq.num_buffers = 1;
	rq.buffers = buffers;

	res = ipc_send(obj, &rq, &rs);
	return res;
}

result_t ifilesystem_create_directory(ifilesystem_t obj, const char in_path[0x301]) {
	result_t res;
	ipc_request_t rq = ipc_default_request;
	rq.request_id = 2;

	ipc_buffer_t in_path_buf = {
		.addr = (void*) in_path,
		.size = 769,
		.type = 25,
	};


	ipc_response_fmt_t rs = ipc_default_response_fmt;
	ipc_buffer_t *buffers[] = {
		&in_path_buf
	};
	rq.num_buffers = 1;
	rq.buffers = buffers;

	res = ipc_send(obj, &rq, &rs);
	return res;
}

result_t ifilesystem_delete_directory(ifilesystem_t obj, const char in_path[0x301]) {
	result_t res;
	ipc_request_t rq = ipc_default_request;
	rq.request_id = 3;

	ipc_buffer_t in_path_buf = {
		.addr = (void*) in_path,
		.size = 769,
		.type = 25,
	};


	ipc_response_fmt_t rs = ipc_default_response_fmt;
	ipc_buffer_t *buffers[] = {
		&in_path_buf
	};
	rq.num_buffers = 1;
	rq.buffers = buffers;

	res = ipc_send(obj, &rq, &rs);
	return res;
}

result_t ifilesystem_delete_directory_recursively(ifilesystem_t obj, const char in_path[0x301]) {
	result_t res;
	ipc_request_t rq = ipc_default_request;
	rq.request_id = 4;

	ipc_buffer_t in_path_buf = {
		.addr = (void*) in_path,
		.size = 769,
		.type = 25,
	};


	ipc_response_fmt_t rs = ipc_default_response_fmt;
	ipc_buffer_t *buffers[] = {
		&in_path_buf
	};
	rq.num_buffers = 1;
	rq.buffers = buffers;

	res = ipc_send(obj, &rq, &rs);
	return res;
}

result_t ifilesystem_rename_file(ifilesystem_t obj, const char in_oldPath[0x301], const char in_newPath[0x301]) {
	result_t res;
	ipc_request_t rq = ipc_default_request;
	rq.request_id = 5;

	ipc_buffer_t in_oldPath_buf = {
		.addr = (void*) in_oldPath,
		.size = 769,
		.type = 25,
	};
	ipc_buffer_t in_newPath_buf = {
		.addr = (void*) in_newPath,
		.size = 769,
		.type = 25,
	};


	ipc_response_fmt_t rs = ipc_default_response_fmt;
	ipc_buffer_t *buffers[] = {
		&in_oldPath_buf,
		&in_newPath_buf
	};
	rq.num_buffers = 2;
	rq.buffers = buffers;

	res = ipc_send(obj, &rq, &rs);
	return res;
}

result_t ifilesystem_rename_directory(ifilesystem_t obj, const char in_oldPath[0x301], const char in_newPath[0x301]) {
	result_t res;
	ipc_request_t rq = ipc_default_request;
	rq.request_id = 6;

	ipc_buffer_t in_oldPath_buf = {
		.addr = (void*) in_oldPath,
		.size = 769,
		.type = 25,
	};
	ipc_buffer_t in_newPath_buf = {
		.addr = (void*) in_newPath,
		.size = 769,
		.type = 25,
	};


	ipc_response_fmt_t rs = ipc_default_response_fmt;
	ipc_buffer_t *buffers[] = {
		&in_oldPath_buf,
		&in_newPath_buf
	};
	rq.num_buffers = 2;
	rq.buffers = buffers;

	res = ipc_send(obj, &rq, &rs);
	return res;
}

result_t ifilesystem_get_entry_type(ifilesystem_t obj, uint32_t *out_unk1, const char in_path[0x301]) {
	result_t res;
	ipc_request_t rq = ipc_default_request;
	rq.request_id = 7;

	ipc_buffer_t in_path_buf = {
		.addr = (void*) in_path,
		.size = 769,
		.type = 25,
	};


	ipc_response_fmt_t rs = ipc_default_response_fmt;
	char output_raw[4];
	rs.raw_data = output_raw;
	rs.raw_data_size = 4;

	ipc_buffer_t *buffers[] = {
		&in_path_buf
	};
	rq.num_buffers = 1;
	rq.buffers = buffers;

	res = ipc_send(obj, &rq, &rs);
	*out_unk1 = *(uint32_t*)(output_raw + 0);

	return res;
}

result_t ifilesystem_open_file(ifilesystem_t obj, ifile_t *out_file, uint32_t in_mode, const char in_path[0x301]) {
	result_t res;
	ipc_request_t rq = ipc_default_request;
	rq.request_id = 8;

	uint8_t raw[4];
	rq.raw_data = raw;
	rq.raw_data_size = 4;

	*(uint32_t*)(raw + 0) = in_mode;
	ipc_buffer_t in_path_buf = {
		.addr = (void*) in_path,
		.size = 769,
		.type = 25,
	};


	ipc_response_fmt_t rs = ipc_default_response_fmt;
	rs.objects = out_file;
	rs.num_objects = 1;


	ipc_buffer_t *buffers[] = {
		&in_path_buf
	};
	rq.num_buffers = 1;
	rq.buffers = buffers;

	res = ipc_send(obj, &rq, &rs);
	return res;
}

result_t ifilesystem_open_directory(ifilesystem_t obj, idirectory_t *out_directory, uint32_t in_unk0, const char in_path[0x301]) {
	result_t res;
	ipc_request_t rq = ipc_default_request;
	rq.request_id = 9;

	uint8_t raw[4];
	rq.raw_data = raw;
	rq.raw_data_size = 4;

	*(uint32_t*)(raw + 0) = in_unk0;
	ipc_buffer_t in_path_buf = {
		.addr = (void*) in_path,
		.size = 769,
		.type = 25,
	};


	ipc_response_fmt_t rs = ipc_default_response_fmt;
	rs.objects = out_directory;
	rs.num_objects = 1;


	ipc_buffer_t *buffers[] = {
		&in_path_buf
	};
	rq.num_buffers = 1;
	rq.buffers = buffers;

	res = ipc_send(obj, &rq, &rs);
	return res;
}

result_t ifilesystem_commit(ifilesystem_t obj) {
	result_t res;
	ipc_request_t rq = ipc_default_request;
	rq.request_id = 10;

	ipc_response_fmt_t rs = ipc_default_response_fmt;
	res = ipc_send(obj, &rq, &rs);
	return res;
}

result_t ifilesystem_get_free_space_size(ifilesystem_t obj, uint64_t *out_totalFreeSpace, const char in_path[0x301]) {
	result_t res;
	ipc_request_t rq = ipc_default_request;
	rq.request_id = 11;

	ipc_buffer_t in_path_buf = {
		.addr = (void*) in_path,
		.size = 769,
		.type = 25,
	};


	ipc_response_fmt_t rs = ipc_default_response_fmt;
	uint8_t output_raw[8];
	rs.raw_data = output_raw;
	rs.raw_data_size = 8;

	ipc_buffer_t *buffers[] = {
		&in_path_buf
	};
	rq.num_buffers = 1;
	rq.buffers = buffers;

	res = ipc_send(obj, &rq, &rs);
	*out_totalFreeSpace = *(uint64_t*)(output_raw + 0);

	return res;
}

result_t ifilesystem_get_total_space_size(ifilesystem_t obj, uint64_t *out_totalSize, const char in_path[0x301]) {
	result_t res;
	ipc_request_t rq = ipc_default_request;
	rq.request_id = 12;

	ipc_buffer_t in_path_buf = {
		.addr = (void*) in_path,
		.size = 769,
		.type = 25,
	};


	ipc_response_fmt_t rs = ipc_default_response_fmt;
	uint8_t output_raw[8];
	rs.raw_data = output_raw;
	rs.raw_data_size = 8;

	ipc_buffer_t *buffers[] = {
		&in_path_buf
	};
	rq.num_buffers = 1;
	rq.buffers = buffers;

	res = ipc_send(obj, &rq, &rs);
	*out_totalSize = *(uint64_t*)(output_raw + 0);

	return res;
}

result_t ifilesystem_clean_directory_recursively(ifilesystem_t obj, const char in_path[0x301]) {
	result_t res;
	ipc_request_t rq = ipc_default_request;
	rq.request_id = 13;

	ipc_buffer_t in_path_buf = {
		.addr = (void*) in_path,
		.size = 769,
		.type = 25,
	};


	ipc_response_fmt_t rs = ipc_default_response_fmt;
	ipc_buffer_t *buffers[] = {
		&in_path_buf
	};
	rq.num_buffers = 1;
	rq.buffers = buffers;

	res = ipc_send(obj, &rq, &rs);
	return res;
}

result_t ifilesystem_get_file_time_stamp_raw(ifilesystem_t obj, uint8_t out_timestamp[0x20], const char in_path[0x301]) {
	result_t res;
	ipc_request_t rq = ipc_default_request;
	rq.request_id = 14;

	ipc_buffer_t in_path_buf = {
		.addr = (void*) in_path,
		.size = 769,
		.type = 25,
	};


	ipc_response_fmt_t rs = ipc_default_response_fmt;
	uint8_t output_raw[32];
	rs.raw_data = output_raw;
	rs.raw_data_size = 32;

	ipc_buffer_t *buffers[] = {
		&in_path_buf
	};
	rq.num_buffers = 1;
	rq.buffers = buffers;

	res = ipc_send(obj, &rq, &rs);
	memcpy(out_timestamp, output_raw + 0, 32);

	return res;
}
