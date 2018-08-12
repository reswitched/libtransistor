/**
 * @file libtransistor/environment.h
 * @brief Functions to query the current environment
 */

#pragma once

#ifdef __cplusplus
extern "C" {
#endif

#include<libtransistor/types.h>

typedef enum {
	KERNEL_VERSION_INVALID,
	KERNEL_VERSION_100,
	KERNEL_VERSION_200,
	KERNEL_VERSION_300,
	KERNEL_VERSION_400,
	KERNEL_VERSION_500,
} kernel_version_t;

/**
 * @brief Returns the current kernel version, for feature-detection purposes
 */
kernel_version_t env_get_kernel_version();


/**
 * @brief Gets a pointer to the top of the stack
 */
void *env_get_stack_top();

#ifdef __cplusplus
}
#endif
