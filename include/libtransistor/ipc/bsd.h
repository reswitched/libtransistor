#pragma once

#include<libtransistor/types.h>
#include<sys/types.h>
#include<sys/socket.h>
#include<netinet/in.h>
#include<netdb.h>

extern result_t bsd_result;
extern int      bsd_errno;

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

result_t bsd_ai_pack(const struct addrinfo *ai, uint8_t *buf, int size);
result_t bsd_ai_unpack(struct addrinfo **ai, const uint8_t *buf, int size);
