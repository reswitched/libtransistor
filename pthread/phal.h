#pragma once

#include <phal_types.h>

int phal_thread_create(phal_tid *tid, void (*start_routine)(void*), void *arg);
void phal_thread_exit(phal_tid *tid);
void **phal_get_tls();

// TODO: pass timespec instead
int phal_thread_sleep(int msec);
