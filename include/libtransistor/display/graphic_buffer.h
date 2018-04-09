/**
 * @file libtransistor/display/graphic_buffer.h
 * @brief Graphics buffer data structures
 */

#pragma once

#ifdef __cplusplus
extern "C" {
#endif

#include<libtransistor/types.h>
#include<libtransistor/gpu/gpu.h>

/**
* @struct graphic_buffer_t
* @brief Graphics buffer
*/
typedef struct {
	uint32_t width;
	uint32_t height;
	uint32_t stride;
	uint32_t format;
	uint32_t usage;
	gpu_buffer_t *gpu_buffer;

	int index;
	int unknown; ///< This is probably related to the offset within the gpu_buffer that this buffer lives in
} graphic_buffer_t;

#ifdef __cplusplus
}
#endif
