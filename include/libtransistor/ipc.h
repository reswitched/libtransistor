#pragma once

#include<libtransistor/types.h>

typedef struct {
	session_h session;
} ipc_domain_t;

typedef struct {
	int32_t object_id; // -1 if this represents a session, >= 0 if this represents a domain object
	union {
		session_h session; // object_id = -1
		ipc_domain_t *domain; // object_id >= 0
	};
} ipc_object_t;

typedef struct {
	void *addr;
	uint64_t size;
	uint32_t type;
} ipc_buffer_t;

typedef struct {
	uint32_t type;
	uint32_t num_buffers;
	ipc_buffer_t **buffers;
	uint32_t request_id;
	uint32_t *raw_data;
	size_t raw_data_size; // in BYTES
	bool send_pid;
	uint8_t num_copy_handles;
	uint8_t num_move_handles;
	uint8_t num_objects;
	handle_t *copy_handles;
	handle_t *move_handles;
	ipc_object_t *objects;
	bool close_object;
} ipc_request_t;

// fill this struct out with what you expect before passing it to ipc_unmarshal
typedef struct {
	uint32_t num_copy_handles;
	uint32_t num_move_handles;
	uint32_t num_objects;
	handle_t *copy_handles;
	handle_t *move_handles;
	ipc_object_t *objects;
  
	size_t raw_data_size; // in BYTES
	uint32_t *raw_data;

	bool has_pid;
	uint32_t *pid;
} ipc_response_fmt_t;

// see ipc.c for actual default values
extern ipc_request_t      ipc_default_request;
extern ipc_response_fmt_t ipc_default_response_fmt;
extern ipc_object_t       ipc_null_object;

/*
  Packs the IPC message described by `rq` and `object` into `buffer`.
*/
result_t ipc_marshal(uint32_t *buffer, ipc_request_t *rq, ipc_object_t object);

/*
  Unpacks the IPC message described by `rs` from `buffer`. `object` should
  be the object the request was sent to.
*/
result_t ipc_unmarshal(uint32_t *buffer, ipc_response_fmt_t *rs, ipc_object_t object);

/*
  Send a request described by `rq` to `object` and then unpack the response
*/
result_t ipc_send(ipc_object_t object, ipc_request_t *rq, ipc_response_fmt_t *rs);

/*
  Converts `session` to a domain object and initializes `domain`.
  Guarenteed to initialize `domain`, making it valid to call `ipc_close_domain`
  on the newly initialized domain if this returns != RESULT_OK
*/
result_t ipc_convert_to_domain(ipc_object_t *session, ipc_domain_t *domain);

/*
  Closes the `object`
*/
result_t ipc_close(ipc_object_t object);

/*
  Closes the whole `domain`
*/
result_t ipc_close_domain(ipc_domain_t domain);


extern int ipc_debug_flag;
