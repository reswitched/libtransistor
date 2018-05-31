/**
 * @file libtransistor/display/fence.h
 * @brief Fence data structures
 */

#pragma once

#ifdef __cplusplus
extern "C" {
#endif

#include<libtransistor/types.h>

/**
 * @struct fence_t
 * @brief Represents conditions for the completion of an asynchronous graphics operation
 */
typedef struct {
	uint32_t is_valid;
	gpu_fence_t sync[4];
} fence_t;

#ifdef __cplusplus
}
#endif
