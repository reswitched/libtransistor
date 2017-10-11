#include<libtransistor/types.h>
#include<libtransistor/svc.h>
#include<libtransistor/ipc.h>
#include<libtransistor/err.h>
#include<libtransistor/util.h>
#include<libtransistor/ipc/sm.h>
#include<libtransistor/ipc/bsd.h>

#define TRANSFER_MEM_SIZE 256*1024

result_t bsd_result;
int      bsd_errno;

static ipc_domain_t bsd_domain;
static ipc_object_t bsd_object;

static ipc_domain_t iresolver_domain;
static ipc_object_t iresolver_object;

static uint8_t __attribute__((aligned(0x1000))) transfer_buffer[TRANSFER_MEM_SIZE];
static transfer_memory_h transfer_mem;

result_t bsd_init() {
  result_t r;
  r = sm_get_service(&bsd_object, "bsd:u");
  if(r) {
    r = sm_get_service(&bsd_object, "bsd:s");
    if(r) { return r; }
  }

  r = ipc_convert_to_domain(&bsd_object, &bsd_domain);
  if(r) {
    ipc_close_domain(bsd_domain);
    return r;
  }

  r = sm_get_service(&iresolver_object, "sfdnsres");
  if(r) {
    ipc_close_domain(bsd_domain);
    return r;
  }

  r = ipc_convert_to_domain(&iresolver_object, &iresolver_domain);
  if(r) {
    ipc_close_domain(bsd_domain);
    ipc_close_domain(iresolver_domain);
    return r;
  }
  
  r = svcCreateTransferMemory(&transfer_mem, transfer_buffer, TRANSFER_MEM_SIZE, 0);
  if(r) {
    ipc_close_domain(bsd_domain);
    ipc_close_domain(iresolver_domain);
    return r;
  }

  uint64_t raw[] = {32*1024, 32*1024, 16*1024, 16*1024,
                    0, // server copies pid to here
                    TRANSFER_MEM_SIZE};
  
  ipc_request_t rq = ipc_default_request;
  rq.type = 4;
  rq.request_id = 0;
  rq.raw_data = (uint32_t*) raw;
  rq.raw_data_size = sizeof(raw);
  rq.send_pid = true;
  rq.num_copy_handles = 1;
  rq.copy_handles = &transfer_mem;

  uint32_t response[1];
  
  ipc_response_fmt_t rs = ipc_default_response_fmt;
  rs.raw_data_size = sizeof(response);
  rs.raw_data = response;
  
  r = ipc_send(bsd_object, &rq, &rs); // not working under mephisto
  
  if(r) {
    svcCloseHandle(transfer_mem);
    ipc_close_domain(bsd_domain);
    ipc_close_domain(iresolver_domain);
    return r;
  }

  if(response[0]) {
    bsd_errno = response[0];
    svcCloseHandle(transfer_mem);
    ipc_close_domain(bsd_domain);
    ipc_close_domain(iresolver_domain);
    return LIBTRANSISTOR_ERR_BSD_ERRNO_SET;
  }
  
  return 0;
}

// def tested via PS
// impl tested via Mephisto
int bsd_socket(int domain, int type, int protocol) {
  result_t r;

  uint32_t raw[] = {domain, type, protocol};
  
  ipc_request_t rq = ipc_default_request;
  rq.request_id = 2;
  rq.raw_data = raw;
  rq.raw_data_size = sizeof(raw);

  int32_t response[2]; // fd, errno
  
  ipc_response_fmt_t rs = ipc_default_response_fmt;
  rs.raw_data_size = sizeof(response);
  rs.raw_data = (uint32_t*) response;
  
  r = ipc_send(bsd_object, &rq, &rs);
  if(r) {
    bsd_result = r;
    return -1;
  }

  if(response[0] < 0) {
    bsd_result = LIBTRANSISTOR_ERR_BSD_ERRNO_SET;
    bsd_errno = response[1];
    return -1;
  }
  
  return response[0];
}

// def tested via PS
// impl untested
int bsd_recv(int socket, void *message, size_t length, int flags) {
  result_t r;

  uint32_t raw[] = {socket, flags};

  ipc_buffer_t buffer;
  buffer.addr = message;
  buffer.size = length;
  buffer.type = 0x22;

  ipc_buffer_t *buffers[] = {&buffer};

  ipc_request_t rq = ipc_default_request;
  rq.num_buffers = 1;
  rq.buffers = buffers;
  rq.request_id = 8;
  rq.raw_data = raw;
  rq.raw_data_size = sizeof(raw);

  int32_t response[2]; // ret, errno

  ipc_response_fmt_t rs = ipc_default_response_fmt;
  rs.raw_data_size = sizeof(response);
  rs.raw_data = (uint32_t*) response;

  r = ipc_send(bsd_object, &rq, &rs);
  if(r) {
    bsd_result = r;
    return -1;
  }

  if(response[0] < 0) {
    bsd_result = LIBTRANSISTOR_ERR_BSD_ERRNO_SET;
    bsd_errno = response[1];
    return -1;
  }

  return response[0];
}

// def tested via PS
// impl tested via Mephisto
int bsd_send(int socket, const void *data, size_t length, int flags) {
  result_t r;

  uint32_t raw[] = {socket, flags};

  ipc_buffer_t buffer;
  buffer.addr = (void*) data;
  buffer.size = length;
  buffer.type = 0x21; // A+X

  ipc_buffer_t *buffers[] = {&buffer};
  
  ipc_request_t rq = ipc_default_request;
  rq.num_buffers = 1;
  rq.buffers = buffers;
  rq.request_id = 10;
  rq.raw_data = raw;
  rq.raw_data_size = sizeof(raw);

  int32_t response[2]; // ret, errno

  ipc_response_fmt_t rs = ipc_default_response_fmt;
  rs.raw_data_size = sizeof(response);
  rs.raw_data = (uint32_t*) response;

  r = ipc_send(bsd_object, &rq, &rs);
  if(r) {
    bsd_result = r;
    return -1;
  }

  if(response[0] < 0) {
    bsd_result = LIBTRANSISTOR_ERR_BSD_ERRNO_SET;
    bsd_errno = response[1];
    return -1;
  }
  
  return response[0];
}

// def tested via PS
// impl untested
int bsd_sendto(int socket, const void *message, size_t length, int flags, const struct sockaddr *dest_addr, socklen_t dest_len) {
  result_t r;

  uint32_t raw[] = {socket, flags};

  ipc_buffer_t message_buffer;
  message_buffer.addr = (void*) message;
  message_buffer.size = length;
  message_buffer.type = 0x21; // A+X

  ipc_buffer_t addr_buffer;
  addr_buffer.addr = (void*) dest_addr;
  addr_buffer.size = dest_len;
  addr_buffer.type = 0x21; // A+X

  ipc_buffer_t *buffers[] = {&message_buffer, &addr_buffer};

  ipc_request_t rq = ipc_default_request;
  rq.num_buffers = 2;
  rq.buffers = buffers;
  rq.request_id = 11;
  rq.raw_data = raw;
  rq.raw_data_size = sizeof(raw);

  int32_t response[2]; // ret, errno

  ipc_response_fmt_t rs = ipc_default_response_fmt;
  rs.raw_data_size = sizeof(response);
  rs.raw_data = (uint32_t*) response;

  r = ipc_send(bsd_object, &rq, &rs);
  if(r) {
    bsd_result = r;
    return -1;
  }

  if(response[0] < 0) {
    bsd_result = LIBTRANSISTOR_ERR_BSD_ERRNO_SET;
    bsd_errno = response[1];
    return -1;
  }
  
  return response[0];
}

// def tested via PS
// impl untested
int bsd_accept(int socket, struct sockaddr *restrict address, socklen_t *restrict address_len) {
  result_t r;

  uint32_t raw[] = {socket};

  ipc_buffer_t addr_buffer;
  addr_buffer.addr = (void*) address;
  addr_buffer.size = *address_len;
  addr_buffer.type = 0x22;

  ipc_buffer_t *buffers[] = {&addr_buffer};
  
  ipc_request_t rq = ipc_default_request;
  rq.num_buffers = 1;
  rq.buffers = buffers;
  rq.request_id = 12;
  rq.raw_data = raw;
  rq.raw_data_size = sizeof(raw);

  int32_t response[3]; // ret, errno, address_len
  
  ipc_response_fmt_t rs = ipc_default_response_fmt;
  rs.raw_data_size = sizeof(response);
  rs.raw_data = (uint32_t*) response;

  r = ipc_send(bsd_object, &rq, &rs);
  if(r) {
    bsd_result = r;
    return -1;
  }

  if(response[0] < 0) {
    bsd_result = LIBTRANSISTOR_ERR_BSD_ERRNO_SET;
    bsd_errno = response[1];
    return -1;
  }

  *address_len = response[2];
  
  return response[0];
}

// def tested via PS
// impl untested
int bsd_bind(int socket, const struct sockaddr *address, socklen_t address_len) {
  result_t r;

  uint32_t raw[] = {socket};

  ipc_buffer_t buffer;
  buffer.addr = (void*) address;
  buffer.size = address_len;
  buffer.type = 0x21; // A+X

  ipc_buffer_t *buffers[] = {&buffer};
  
  ipc_request_t rq = ipc_default_request;
  rq.num_buffers = 1;
  rq.buffers = buffers;
  rq.request_id = 13;
  rq.raw_data = raw;
  rq.raw_data_size = sizeof(raw);

  int32_t response[2]; // ret, errno

  ipc_response_fmt_t rs = ipc_default_response_fmt;
  rs.raw_data_size = sizeof(response);
  rs.raw_data = (uint32_t*) response;

  r = ipc_send(bsd_object, &rq, &rs);
  if(r) {
    bsd_result = r;
    return -1;
  }

  if(response[0] < 0) {
    bsd_result = LIBTRANSISTOR_ERR_BSD_ERRNO_SET;
    bsd_errno = response[1];
    return -1;
  }
  
  return response[0];
}

// def tested via PS
// impl tested via Mephisto
int bsd_connect(int socket, const struct sockaddr *address, socklen_t address_len) {
  result_t r;

  uint32_t raw[] = {socket};

  ipc_buffer_t buffer;
  buffer.addr = (void*) address;
  buffer.size = address_len;
  buffer.type = 0x21; // A+X

  ipc_buffer_t *buffers[] = {&buffer};
  
  ipc_request_t rq = ipc_default_request;
  rq.num_buffers = 1;
  rq.buffers = buffers;
  rq.request_id = 14;
  rq.raw_data = raw;
  rq.raw_data_size = sizeof(raw);

  uint32_t response[2]; // ret, errno

  ipc_response_fmt_t rs = ipc_default_response_fmt;
  rs.raw_data_size = sizeof(response);
  rs.raw_data = response;

  r = ipc_send(bsd_object, &rq, &rs);
  if(r) {
    bsd_result = r;
    return -1;
  }

  if(response[0] != 0) {
    bsd_result = LIBTRANSISTOR_ERR_BSD_ERRNO_SET;
    bsd_errno = response[1];
    return -1;
  }
  
  return response[0];
}

// def untested
int bsd_getsockname(int socket, struct sockaddr *restrict address, socklen_t *restrict address_len) {
  return 0;
}

// def tested via PS
int bsd_listen(int socket, int backlog) {
  result_t r;

  uint32_t raw[] = {socket, backlog};
  
  ipc_request_t rq = ipc_default_request;
  rq.request_id = 18;
  rq.raw_data = raw;
  rq.raw_data_size = sizeof(raw);

  int32_t response[2]; // ret, errno
  
  ipc_response_fmt_t rs = ipc_default_response_fmt;
  rs.raw_data_size = sizeof(response);
  rs.raw_data = (uint32_t*) response;
  
  r = ipc_send(bsd_object, &rq, &rs);
  if(r) {
    bsd_result = r;
    return -1;
  }

  if(response[0] < 0) {
    bsd_result = LIBTRANSISTOR_ERR_BSD_ERRNO_SET;
    bsd_errno = response[1];
    return -1;
  }
  
  return response[0];
}

// def untested
int bsd_setsockopt(int socket, int level, int option_name, const void *option_value, socklen_t option_len) {
  return 0;
}

// def untested
int bsd_shutdown(int socket, int how) {
  return 0;
}

// def untested
int bsd_select(int nfds, fd_set *restrict readfds, fd_set *restrict writefds, fd_set *restrict errorfds, struct timeval *restrict timeout) {
  result_t r;

  uint64_t timeout_words[3];
  if(timeout != NULL) {
    timeout_words[0] = timeout->tv_sec;
    timeout_words[1] = timeout->tv_usec;
    timeout_words[2] = 0;
  } else {
    timeout_words[0] = 0;
    timeout_words[1] = 0;
    timeout_words[2] = 1;
  }

  uint32_t raw[7];
  raw[0] = nfds;
  memcpy(raw + 1, timeout_words, sizeof(timeout_words));
  
  ipc_buffer_t readfds_in = {
    .addr = readfds,
    .size = (readfds == NULL) ? 0 : sizeof(readfds),
    .type = 0x21
  };
  ipc_buffer_t writefds_in = {
    .addr = writefds,
    .size = (writefds == NULL) ? 0 : sizeof(writefds),
    .type = 0x21
  };
  ipc_buffer_t errorfds_in = {
    .addr = errorfds,
    .size = (errorfds == NULL) ? 0 : sizeof(errorfds),
    .type = 0x21
  };
  ipc_buffer_t readfds_out = {
    .addr = readfds,
    .size = (readfds == NULL) ? 0 : sizeof(readfds),
    .type = 0x22
  };
  ipc_buffer_t writefds_out = {
    .addr = writefds,
    .size = (writefds == NULL) ? 0 : sizeof(writefds),
    .type = 0x22
  };
  ipc_buffer_t errorfds_out = {
    .addr = errorfds,
    .size = (errorfds == NULL) ? 0 : sizeof(errorfds),
    .type = 0x22
  };
  
  ipc_buffer_t *buffers[] = {
    &readfds_in,
    &writefds_in,
    &errorfds_in,
    &readfds_out,
    &writefds_out,
    &errorfds_out
  };
    
  ipc_request_t rq = ipc_default_request;
  rq.num_buffers = 6;
  rq.buffers = buffers;
  rq.request_id = 5;
  rq.raw_data = raw;
  rq.raw_data_size = sizeof(raw);

  int32_t response[2];

  ipc_response_fmt_t rs = ipc_default_response_fmt;
  rs.raw_data_size = sizeof(response);
  rs.raw_data = (uint32_t*) response;

  r = ipc_send(bsd_object, &rq, &rs);
  if(r) {
    bsd_result = r;
    return -1;
  }

  if(response[0] < 0) {
    bsd_result = LIBTRANSISTOR_ERR_BSD_ERRNO_SET;
    bsd_errno = response[1];
    return -1;
  }

  return response[0];
}

// def tested via PS
int bsd_close(int socket) {
  result_t r;

  uint32_t raw[] = {socket};
  
  ipc_request_t rq = ipc_default_request;
  rq.request_id = 26;
  rq.raw_data = raw;
  rq.raw_data_size = sizeof(raw);

  int32_t response[2]; // ret, errno
  
  ipc_response_fmt_t rs = ipc_default_response_fmt;
  rs.raw_data_size = sizeof(response);
  rs.raw_data = (uint32_t*) response;
  
  r = ipc_send(bsd_object, &rq, &rs);
  if(r) {
    bsd_result = r;
    return -1;
  }

  if(response[0] < 0) {
    bsd_result = LIBTRANSISTOR_ERR_BSD_ERRNO_SET;
    bsd_errno = response[1];
    return -1;
  }
  
  return response[0];
}

void bsd_finalize() {
  svcCloseHandle(transfer_mem);
  ipc_close(bsd_object);
  ipc_close_domain(bsd_domain);
}
