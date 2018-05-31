/**
 * @file libtransistor/gpu/gpu.h
 * @brief GPU functions
 */

#pragma once

#ifdef __cplusplus
extern "C" {
#endif

#include<libtransistor/types.h>

/**
* @struct gpu_buffer_t
* @brief Buffer to be used for various GPU functions
*/
typedef struct {
	uint32_t nvmap_handle; ///< Handle for nvmap gpu memory management driver
	size_t size;
	uint32_t alignment;
	uint8_t kind;
} gpu_buffer_t;

typedef struct {
	uint32_t syncpt_id;
	uint32_t syncpt_value;
} gpu_fence_t;

/**
* @brief Initialize GPU
*/
result_t gpu_initialize();

/**
* @brief Initializes a GPU buffer with the args provided
*
* @param gpu_b GPU buffer
* @param addr Address of backing memory
* @param size Size of buffer to create
* @param heapmask Heapmask for buffer
* @param flags Flags for buffer
* @param alignment Alignment of buffer
* @param kind Kind of buffer
*/
result_t gpu_buffer_initialize(gpu_buffer_t *gpu_b, void *addr, size_t size, uint32_t heapmask, uint32_t flags, uint32_t alignment, uint8_t kind);

/**
 * @brief Destroys a GPU buffer
 *
 * @param gpu_b GPU buffer to destroy
 */
result_t gpu_buffer_destroy(gpu_buffer_t *gpu_b, uint64_t *refcount, uint32_t *flags);

/**
* @brief Get a GPU buffer's ID
*
* @param gpu_b GPU buffer
* @param id ID of GPU buffer
*/
result_t gpu_buffer_get_id(gpu_buffer_t *gpu_b, uint32_t *id);

/**
* @brief Create a structure to access an existing GPU buffer from a given ID
*
* @param gpu_b GPU buffer structure to initialize
* @param id ID of gpu buffer
*/
result_t gpu_buffer_initialize_from_id(gpu_buffer_t *gpu_b, uint32_t id);


/**
 * @brief Waits on a fence to complete
 *
 * @param fence Fence to wait for completion on
 */
result_t gpu_wait_fence(gpu_fence_t *fence, uint32_t timeout);

/**
* @brief Finalize GPU
*/
void gpu_finalize();

#ifdef __cplusplus
}
#endif
