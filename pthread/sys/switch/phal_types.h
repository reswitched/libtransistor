#pragma once

#include <libtransistor/nx.h>

typedef struct {
	thread_h id;
	void *stack;
} phal_tid;

typedef struct {
	_Atomic(uint32_t) lock;
	uint32_t sem;
} phal_semaphore;
