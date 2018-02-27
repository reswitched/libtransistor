#ifndef _LIBTRANSISTOR_TIME_H_
#define _LIBTRANSISTOR_TIME_H_

#define _POSIX_MONOTONIC_CLOCK
#define _POSIX_TIMERS

#include_next <time.h>

int nanosleep(const struct timespec *rqtp, struct timespec *rmtp);

#endif
