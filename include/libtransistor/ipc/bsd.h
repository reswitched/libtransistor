#pragma once

#include<libtransistor/types.h>
#include<netinet/in.h>

extern result_t bsd_result;
extern int      bsd_errno;

typedef uint64_t fd_mask;
typedef struct fd_set {
  fd_mask fds_bits[16];
} fd_set;

#define NFDBITS (sizeof(fd_mask) * 8)
#define FD_SET(n, p) ((p)->fds_bits[(n)/NFDBITS] |= (1L << ((n) % NFDBITS)))
#define FD_CLR(n, p) ((p)->fds_bits[(n)/NFDBITS] &= ~(1L << ((n) % NFDBITS)))
#define FD_ISSET(n, p) ((p)->fds_bits[(n)/NFDBITS] & (1L << ((n) % NFDBITS)))
#define FD_ZERO(p) memset(p, 0, sizeof(p))

struct timeval {
  int64_t tv_sec;
  int64_t tv_usec;
};

struct addrinfo;
struct addrinfo {
  int ai_flags;
  int ai_family;
  int ai_socktype;
  int ai_protocol;
  socklen_t ai_addrlen;
  struct sockaddr *ai_addr;
  char *ai_canonname;
  struct addrinfo *ai_next;
};

result_t bsd_init();
int bsd_socket(int domain, int type, int protocol);
int bsd_recv(int socket, void *message, size_t length, int flags);
int bsd_send(int socket, const void *data, size_t length, int flags);
int bsd_sendto(int socket, const void *message, size_t length, int flags, const struct sockaddr *dest_addr, socklen_t dest_len);
int bsd_accept(int socket, struct sockaddr *restrict address, socklen_t *restrict address_len);
int bsd_bind(int socket, const struct sockaddr *address, socklen_t address_len);
int bsd_connect(int socket, const struct sockaddr *address, socklen_t address_len);
int bsd_getsockname(int socket, struct sockaddr *restrict address, socklen_t *restrict address_len);
int bsd_listen(int socket, int backlog);
int bsd_setsockopt(int socket, int level, int option_name, const void *option_value, socklen_t option_len);
int bsd_shutdown(int socket, int how);
int bsd_select(int nfds, fd_set *restrict readfds, fd_set *restrict writefds, fd_set *restrict errorfds, struct timeval *restrict timeout);
int bsd_getaddrinfo(const char *node, const char *service, const struct addrinfo *hints, struct addrinfo **res);
void bsd_freeaddrinfo(struct addrinfo *res);
int bsd_close(int socket);
void bsd_finalize();
