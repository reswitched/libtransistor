#pragma once

#include<libtransistor/types.h>

extern result_t bsd_result;
extern int      bsd_errno;

result_t bsd_init();
int bsd_socket(int domain, int type, int protocol);
void bsd_finalize();

struct sockaddr;
typedef uint32_t socklen_t;
