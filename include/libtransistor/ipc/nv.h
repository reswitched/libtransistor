#pragma once

#include<libtransistor/types.h>

extern result_t nv_result;
extern int nv_errno;

result_t nv_init();
int nv_open(const char *path);
int nv_ioctl(int fd, uint32_t rq, void *arg, size_t size);
int nv_close(int fd);
void nv_finalize();
