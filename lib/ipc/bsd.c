#include<libtransistor/types.h>
#include<libtransistor/svc.h>
#include<libtransistor/ipc.h>
#include<libtransistor/err.h>
#include<libtransistor/util.h>
#include<libtransistor/ipc/sm.h>
#include<libtransistor/ipc/bsd.h>

#define TRANSFER_MEM_SIZE 64*1024

result_t bsd_result;
int      bsd_errno;

static session_h bsd_session = 0;

static uint8_t __attribute__((aligned(0x1000))) transfer_buffer[TRANSFER_MEM_SIZE];
static transfer_memory_h transfer_mem;

result_t bsd_init() {
  result_t r;
  r = sm_get_service(&bsd_session, "bsd:u");
  if(r) {
    r = sm_get_service(&bsd_session, "bsd:s");
    if(r) { return r; }
  }

  printf("opened bsd: 0x%x", bsd_session);
  printf("transfer mem at %p", transfer_buffer);
  
  r = svcCreateTransferMemory(&transfer_mem, transfer_buffer, TRANSFER_MEM_SIZE, 0);
  if(r) { return r; }
  printf("opened transfer mem 0x%x", transfer_mem);

  uint64_t raw[] = {256*1024, 256*1024, 256*1024, 256*1024, 0, TRANSFER_MEM_SIZE};
  ipc_request_t rq;
  rq.type = 4;
  rq.num_buffers = 0;
  rq.is_to_domain = false;
  rq.request_id = 0;
  rq.raw_data = (uint32_t*) raw;
  rq.raw_data_size = sizeof(raw)/sizeof(uint32_t);
  rq.send_pid = true;
  rq.num_copy_handles = 1;
  rq.num_move_handles = 0;
  rq.copy_handles = &transfer_mem;

  uint32_t response[1];
  
  ipc_response_fmt_t rs;
  rs.num_copy_handles = 0;
  rs.num_move_handles = 0;
  rs.raw_data_size = 1;
  rs.raw_data = response;
  rs.has_pid = false;
  
  r = ipc_send(bsd_session, &rq, &rs);
  
  if(r) {
    svcCloseHandle(transfer_mem);
    return r;
  }

  if(response[0]) {
    svcCloseHandle(transfer_mem);
    bsd_errno = response[0];
    return LIBTRANSISTOR_ERR_BSD_ERRNO_SET;
  }
  
  return 0;
}

int bsd_socket(int domain, int type, int protocol) {
  result_t r;

  uint32_t raw[] = {domain, type, protocol};
  
  ipc_request_t rq;
  rq.type = 4;
  rq.num_buffers = 0;
  rq.is_to_domain = false;
  rq.request_id = 2;
  rq.raw_data = raw;
  rq.raw_data_size = 3;
  rq.send_pid = false;
  rq.num_copy_handles = 0;
  rq.num_move_handles = 0;

  uint32_t response[2]; // fd, errno
  
  ipc_response_fmt_t rs;
  rs.num_copy_handles = 0;
  rs.num_move_handles = 0;
  rs.raw_data_size = 2;
  rs.raw_data = response;
  rs.has_pid = false;
  
  r = ipc_send(bsd_session, &rq, &rs);
  if(r) {
    bsd_result = r;
    return -1;
  }

  if(response[1]) {
    bsd_result = LIBTRANSISTOR_ERR_BSD_ERRNO_SET;
    bsd_errno = response[1];
    return -1;
  }
  
  return response[0];
}

result_t bsd_recv(int socket, void *buffer, size_t length, int flags) {
  return 0;
}

result_t bsd_send(int socket, const void *buffer, size_t length, int flags) {
  return 0;
}

result_t bsd_sendto(int socket, const void *message, size_t length, int flags, const struct sockaddr *dest_addr, socklen_t dest_len) {
  return 0;
}

result_t bsd_accept(int socket, struct sockaddr *restrict address, socklen_t *restrict address_len) {
  return 0;
}

result_t bsd_bind(int socket, const struct sockaddr *address, socklen_t address_len) {
  return 0;
}

result_t bsd_connect(int socket, const struct sockaddr *address, socklen_t address_len) {
  return 0;
}

result_t bsd_getsockname(int socket, struct sockaddr *restrict address, socklen_t *restrict address_len) {
  return 0;
}

result_t bsd_listen(int socket, int backlog) {
  return 0;
}

result_t bsd_setsockopt(int socket, int level, int option_name, const void *option_value, socklen_t option_len) {
  return 0;
}

result_t bsd_shutdown(int socket, int how) {
  return 0;
}

result_t bsd_close(int socket) {
  return 0;
}

void bsd_finalize() {
  svcCloseHandle(transfer_mem);
  svcCloseHandle(bsd_session);
}
