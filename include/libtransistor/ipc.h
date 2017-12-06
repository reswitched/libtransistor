#pragma once

#include<libtransistor/types.h>

struct ipc_server_object_t;

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
	u64 size;
	u32 type;
} ipc_buffer_t;

/*
  describes an outgoing request
 */
typedef struct {
	u32 type;
	u32 num_buffers;
	ipc_buffer_t **buffers;
	u32 request_id;
	u32 *raw_data;
	size_t raw_data_size; // in BYTES
	bool send_pid;
	u8 num_copy_handles;
	u8 num_move_handles;
	u8 num_objects;
	handle_t *copy_handles;
	handle_t *move_handles;
	ipc_object_t *objects;
	bool close_object;
} ipc_request_t;

/*
  describes the format expectations of an incoming request
 */
typedef struct {
	u32 num_buffers;
	ipc_buffer_t **buffers;
	u32 *raw_data;
	size_t raw_data_size; // in BYTES
	bool send_pid;
	u64 *pid;
	u8 num_copy_handles;
	u8 num_move_handles;
	u8 num_objects;
	handle_t *copy_handles;
	handle_t *move_handles;
	struct ipc_server_object_t **objects;
} ipc_request_fmt_t;

/*
  describes an outgoing response
 */
typedef struct {
	u32 type;
	u32 num_buffers;
	ipc_buffer_t **buffers;
	result_t result_code;
	u32 *raw_data;
	size_t raw_data_size; // in BYTES
	bool send_pid;
	u8 num_copy_handles;
	u8 num_move_handles;
	u8 num_objects;
	handle_t *copy_handles;
	handle_t *move_handles;
	struct ipc_server_object_t **objects;
} ipc_response_t;

/*
  describes the format expectations of an incoming response.
  fill this struct out with what you expect before passing it to ipc_unmarshal
 */
typedef struct {
	uint32_t num_copy_handles;
	uint32_t num_move_handles;
	uint32_t num_objects;
	handle_t *copy_handles;
	handle_t *move_handles;
	ipc_object_t *objects;
  
	size_t raw_data_size; // in BYTES
	u32 *raw_data;

	bool has_pid;
	u32 *pid;
} ipc_response_fmt_t;

// see ipc.c for actual default values
extern ipc_request_t      ipc_default_request;
extern ipc_response_t     ipc_default_response;
extern ipc_request_fmt_t  ipc_default_request_fmt;
extern ipc_response_fmt_t ipc_default_response_fmt;
extern ipc_object_t       ipc_null_object;

/*
  describes an incoming IPC message. used as an intermediate during unpacking
 */
typedef struct {
	u16 message_type;
	u32 raw_data_section_size; // in words
	u32 num_x_descriptors;
	u32 num_a_descriptors;
	u32 num_b_descriptors;
	u32 num_w_descriptors;
	u32 c_descriptor_flags;
	u32 *x_descriptors;
	u32 *a_descriptors;
	u32 *b_descriptors;
	u32 *w_descriptors;
	u32 *c_descriptors;
	u32 num_copy_handles;
	u32 num_move_handles;
	handle_t *copy_handles;
	handle_t *move_handles;
	bool has_pid;
	u64 pid;
	int pre_padding; // in words
	int post_padding; // in words
	u32 *data_section; // may point to domain header, may point to SFCI/SFCO
} ipc_message_t;

/*
  Packs the IPC message described by `rq` and `object` into `buffer`.
*/
result_t ipc_pack_request(u32 *buffer, ipc_request_t *rq, ipc_object_t object);

/*
  Packs the IPC message described by `rs` and `object` into `buffer`.
*/
result_t ipc_pack_response(u32 *buffer, ipc_response_t *rs, struct ipc_server_object_t *object);

/*
  Unpacks the IPC message from `buffer`
 */
result_t ipc_unpack(u32 *buffer, ipc_message_t *msg);

/*
  Unflattens the IPC message described by `rq` from `msg`
*/
result_t ipc_unflatten_request(ipc_message_t *msg, ipc_request_fmt_t *rs, struct ipc_server_object_t *object);

/*
  Unflattens the IPC message described by `rs` from `msg`. `object` should
  be the object the request was sent to.
*/
result_t ipc_unflatten_response(ipc_message_t *msg, ipc_response_fmt_t *rs, ipc_object_t object);

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
  Validates and unpacks a request
 */
result_t ipc_incoming_unmarshal(u32 *buffer, ipc_request_fmt_t *rq);

/*
  Closes the `object`
*/
result_t ipc_close(ipc_object_t object);

/*
  Closes the whole `domain`
*/
result_t ipc_close_domain(ipc_domain_t domain);


extern int ipc_debug_flag;
