#pragma once

#include <libtransistor/nx.h>

typedef thread_h phal_tid;
typedef struct {
	_Atomic(uint32_t) lock;
	uint32_t sem;
} phal_semaphore;
