/**
 * @file libtransistor/ipc_helpers.h
 * @brief Functions and macros to make using IPC a little easier
 */

#pragma once

#ifdef __cplusplus
extern "C" {
#endif

#include<libtransistor/ipc.h>
#include<libtransistor/util.h>

#include<string.h>

inline ipc_buffer_t ipc_make_buffer(void *addr, size_t size, uint32_t type) {
	ipc_buffer_t buf;
	buf.addr = addr;
	buf.size = size;
	buf.type = type;
	return buf;
}

inline ipc_buffer_t ipc_buffer_from_string(const char *string, uint32_t type) {
	ipc_buffer_t buf;
	buf.addr = string;
	buf.size = strlen(string) + 1;
	buf.type = type;
	return buf;
}

inline ipc_request_t ipc_make_request(uint32_t id) {
	ipc_request_t rq = ipc_default_request;
	rq.request_id = id;
	return rq;
}

#define ipc_buffer_from_reference(ptr, type) ipc_make_buffer((ptr), sizeof(*(ptr)), type)
#define ipc_msg_raw_data_from_reference(msg, ptr) \
	msg.raw_data_size = sizeof(*(ptr)); \
	msg.raw_data = (uint32_t*) (ptr);

#define ipc_buffer_from_value(val, type) ipc_make_buffer(&(val), sizeof(val), type)
#define ipc_msg_raw_data_from_value(msg, val) \
	msg.raw_data_size = sizeof(val); \
	msg.raw_data = (uint32_t*) (&(val));

#define ipc_msg_set_buffers(msg, obj_arr, ptr_arr)	  \
	ipc_buffer_t *(ptr_arr)[ARRAY_LENGTH(obj_arr)]; \
	for(size_t i = 0; i < ARRAY_LENGTH(obj_arr); i++) { \
		(ptr_arr)[i] = &(obj_arr)[i]; \
	} \
	(msg).num_buffers = ARRAY_LENGTH(obj_arr); \
	(msg).buffers = (ptr_arr);

#define ipc_msg_copy_handle_from_value(msg, handle)	\
	(msg).num_copy_handles = 1; \
	(msg).copy_handles = &(handle);

#define ipc_msg_copy_handle_from_reference(msg, handle)	\
	(msg).num_copy_handles = 1; \
	(msg).copy_handles = handle;

#ifdef __cplusplus
}
#endif
