/**
 * @file libtransistor/gpu/nv_ioc.h
 * @brief NVMAP_IOC data structures
 */

#pragma once

#define NVMAP_IOC_CREATE 0xC0080101
#define NVMAP_IOC_FROM_ID 0xC0080103
#define NVMAP_IOC_ALLOC 0xC0200104
#define NVMAP_IOC_PARAM 0xC00C0109
#define NVMAP_IOC_GET_ID 0xC008010E

/**
* @struct nvmap_ioc_create_args
* @brief Args to create an nvmap object 
*
*        Identical to Linux driver.
*/
typedef struct {
	uint32_t size; ///< In
	uint32_t handle; ///< Out
} nvmap_ioc_create_args;

/**
* @struct nvmap_ioc_from_id_args
* @brief Args to get the handle to an existing nvmap object
*
*        Identical to Linux driver.
*/
typedef struct {
	uint32_t id; ///< In
	uint32_t handle; ///< Out
} nvmap_ioc_from_id_args;

/**
* @struct nvmap_ioc_alloc_args
* @brief Memory allocation args structure for the nvmap object. 
*
*        Nintendo extended this one with 16 bytes, and changed it from in to inout.
*/
typedef struct {
	uint32_t handle;
	uint32_t heapmask;
	uint32_t flags; ///< (0=read-only, 1=read-write)
	uint32_t align;
	uint8_t kind;
	uint8_t pad[7];
	uint64_t addr;
} nvmap_ioc_alloc_args;

/**
* @struct nvmap_ioc_param_args
* @brief Info about a nvmap object. 
*
*        Identical to Linux driver, but extended with further params.
*/
typedef struct {
	uint32_t handle;
	uint32_t param; ///< // 1=SIZE, 2=ALIGNMENT, 3=BASE (returns error), 4=HEAP (always 0x40000000), 5=KIND, 6=COMPR (unused)
	uint32_t value;
} nvmap_ioc_param_args;

/**
* @struct nvmap_ioc_get_id_args
* @brief An id for a nvmap object. 
*
*        Identical to Linux driver.
*/
typedef struct {
	uint32_t id; ///< Out ~0 indicates error
	uint32_t handle; ///< In
} nvmap_ioc_get_id_args;
