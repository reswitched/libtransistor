#pragma once

#include<libtransistor/types.h>

typedef struct {
  session_h session;
  int32_t object_id; // -1 means not to a domain
} ipc_object_t;

typedef struct {
  void *addr;
  u64 size;
  u32 type;
} ipc_buffer_t;

typedef struct {
  u32 type;
  u32 num_buffers;
  ipc_buffer_t **buffers;
  u32 request_id;
  u32 *raw_data;
  u64 raw_data_size; // in BYTES
  bool send_pid;
  u8 num_copy_handles;
  u8 num_move_handles;
  u8 num_objects;
  handle_t *copy_handles;
  handle_t *move_handles;
  ipc_object_t *objects;
} ipc_request_t;

// fill this struct out with what you expect before passing it to ipc_unmarshal
typedef struct {
  int num_copy_handles;
  int num_move_handles;
  int num_objects;
  handle_t *copy_handles;
  handle_t *move_handles;
  ipc_object_t *objects;
  
  int raw_data_size; // in BYTES
  u32 *raw_data;

  bool has_pid;
  u32 *pid;
} ipc_response_fmt_t;

// see ipc.c for actual default values
extern ipc_request_t      ipc_default_request;
extern ipc_response_fmt_t ipc_default_response_fmt;

result_t ipc_marshal(u32 *buffer, ipc_request_t *rq);
result_t ipc_unmarshal(u32 *buffer, ipc_response_fmt_t *rs);
result_t ipc_send(ipc_object_t object, ipc_request_t *rq, ipc_response_fmt_t *rs);
result_t ipc_convert_to_domain(ipc_object_t *session);
