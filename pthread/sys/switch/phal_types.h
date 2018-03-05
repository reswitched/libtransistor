#pragma once

#include<stdint.h>
#include<stdatomic.h>

typedef struct {
	uint32_t id;
	void *stack;
} phal_tid;

typedef struct {
	_Atomic(uint32_t) lock;
	uint32_t sem;
} phal_semaphore;
