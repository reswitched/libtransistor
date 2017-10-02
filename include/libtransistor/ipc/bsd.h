#pragma once

#include<libtransistor/types.h>

extern result_t bsd_result;
extern int      bsd_errno;

struct sockaddr;
typedef uint32_t socklen_t;

struct in_addr {
  uint32_t s_addr;
};

struct sockaddr_in {
  uint16_t sin_family;
  uint16_t sin_port;
  struct in_addr sin_addr;
  uint8_t pad[8]; // struct size has to be 16
} __attribute__((packed));

result_t bsd_init();
int bsd_socket(int domain, int type, int protocol);
int bsd_connect(int socket, const struct sockaddr *address, socklen_t address_len);
int bsd_send(int socket, const void *data, size_t length, int flags);
void bsd_finalize();
