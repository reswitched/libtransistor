#include<libtransistor/types.h>
#include<libtransistor/svc.h>
#include<libtransistor/ipc.h>
#include<libtransistor/err.h>
#include<libtransistor/util.h>
#include<libtransistor/ipc/sm.h>
#include<libtransistor/ipc/nv.h>

#include<string.h>
#include<malloc.h>

#define TRANSFER_MEM_SIZE 3*1024*1024

result_t nv_result;
int nv_errno;

static ipc_object_t nv_object;

static uint8_t __attribute__((aligned(0x1000))) transfer_buffer[TRANSFER_MEM_SIZE];
static transfer_memory_h transfer_mem;

result_t nv_init() {
  result_t r;
  r = sm_get_service(&nv_object, "nvdrv:a");
  if(r) {
    goto fail_no_service;
  }

  r = svcCreateTransferMemory(&transfer_mem, transfer_buffer, TRANSFER_MEM_SIZE, 0);
  if(r) {
    goto fail_no_tmem;
  }

  uint32_t raw[] = {TRANSFER_MEM_SIZE};
  uint32_t handles[] = {0xFFFF8001, transfer_mem};
  
  ipc_request_t rq = ipc_default_request;
  rq.request_id = 3;
  rq.raw_data = (uint32_t*) raw;
  rq.raw_data_size = sizeof(raw);
  rq.num_copy_handles = 2;
  rq.copy_handles = handles;

  uint32_t response[1];

  ipc_response_fmt_t rs = ipc_default_response_fmt;
  rs.raw_data_size = sizeof(response);
  rs.raw_data = response;

  r = ipc_send(nv_object, &rq, &rs);
  if(r) {
    goto fail;
  }

  if(response[0]) {
    nv_errno = response[0];
    r = LIBTRANSISTOR_ERR_NV_INITIALIZE_FAILED;
    goto fail;
  }

  return 0;
  
 fail:
  svcCloseHandle(transfer_mem);
 fail_no_tmem:
  ipc_close(nv_object);
 fail_no_service:
  return r;
}

int nv_open(const char *path) {
  result_t r;

  ipc_buffer_t path_buffer;
  path_buffer.addr = (void*) path;
  path_buffer.size = strlen(path);
  path_buffer.type = 0x5;

  ipc_buffer_t *buffers[] = {&path_buffer};
  
  ipc_request_t rq = ipc_default_request;
  rq.request_id = 0;
  rq.num_buffers = 1;
  rq.buffers = buffers;

  int32_t response[2];

  ipc_response_fmt_t rs = ipc_default_response_fmt;
  rs.raw_data_size = sizeof(response);
  rs.raw_data = (uint32_t*) response;

  r = ipc_send(nv_object, &rq, &rs);
  if(r) {
    nv_result = r;
    return -1;
  }

  if(response[1] != 0) {
    nv_result = LIBTRANSISTOR_ERR_NV_OPEN_FAILED;
    nv_errno = response[1];
    return -1;
  }

  return response[0]; // fd
}

int nv_ioctl(int fd, uint32_t rqid, void *arg, size_t size) {
  result_t r;

  ipc_buffer_t ioc_in_b;
  ioc_in_b.addr = arg;
  ioc_in_b.size = size;
  ioc_in_b.type = 0x21;

  ipc_buffer_t ioc_out_b;
  ioc_out_b.addr = arg;
  ioc_out_b.size = size;
  ioc_out_b.type = 0x22;

  ipc_buffer_t *buffers[] = {&ioc_in_b, &ioc_out_b};

  int32_t raw[] = {fd, rqid, 0, 0}; // don't know what the zeroes are
  
  ipc_request_t rq = ipc_default_request;
  rq.request_id = 1;
  rq.num_buffers = 2;
  rq.buffers = buffers;
  rq.raw_data = (uint32_t*) raw;
  rq.raw_data_size = sizeof(raw);

  int32_t response[1];

  ipc_response_fmt_t rs = ipc_default_response_fmt;
  rs.raw_data_size = sizeof(response);
  rs.raw_data = (uint32_t*) response;

  r = ipc_send(nv_object, &rq, &rs);
  if(r) {
    nv_result = r;
    return -1;
  }

  return response[0];
}

int nv_close(int fd) {
  result_t r;

  int32_t raw[] = {fd};
  
  ipc_request_t rq = ipc_default_request;
  rq.request_id = 2;
  rq.raw_data = (uint32_t*) raw;
  rq.raw_data_size = sizeof(raw);

  int32_t response[1];

  ipc_response_fmt_t rs = ipc_default_response_fmt;
  rs.raw_data_size = sizeof(response);
  rs.raw_data = (uint32_t*) response;

  r = ipc_send(nv_object, &rq, &rs);
  if(r) {
    nv_result = r;
    return -1;
  }

  return response[0];  
}

void nv_finalize() {
  svcCloseHandle(transfer_mem);
  ipc_close(nv_object);
}
