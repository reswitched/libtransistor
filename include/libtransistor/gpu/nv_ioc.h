/**
 * @file libtransistor/gpu/nv_ioc.h
 * @brief /dev/nvmap ioctl structures and definitions
 */

#pragma once

#ifdef __cplusplus
extern "C" {
#endif

#define NVHOST_IOCTL_CTRL_SYNCPT_READ 0xC0080014
#define NVHOST_IOCTL_CTRL_SYNCPT_INCR 0x40040015
#define NVHOST_IOCTL_CTRL_SYNCPT_WAIT 0xC00C0016
#define NVHOST_IOCTL_CTRL_MODULE_MUTEX 0x40080017
#define NVHOST_IOCTL_CTRL_MODULE_REGRDWR 0xC0180018
#define NVHOST_IOCTL_CTRL_SYNCPT_WAITEX 0xC0100019
#define NVHOST_IOCTL_CTRL_SYNCPT_READ_MAX 0xC008001A
#define NVHOST_IOCTL_CTRL_GET_CONFIG 0xC183001B
#define NVHOST_IOCTL_CTRL_EVENT_SIGNAL 0xC004001C
#define NVHOST_IOCTL_CTRL_EVENT_WAIT 0xC010001D
#define NVHOST_IOCTL_CTRL_EVENT_WAIT_ASYNC 0xC010001E
#define NVHOST_IOCTL_CTRL_EVENT_REGISTER 0xC004001F
#define NVHOST_IOCTL_CTRL_EVENT_UNREGISTER 0xC0040020
#define NVHOST_IOCTL_CTRL_EVENT_KILL 0x40080021

#define NVMAP_IOC_CREATE 0xC0080101
#define NVMAP_IOC_FROM_ID 0xC0080103
#define NVMAP_IOC_ALLOC 0xC0200104
#define NVMAP_IOC_FREE 0xC0180105
#define NVMAP_IOC_PARAM 0xC00C0109
#define NVMAP_IOC_GET_ID 0xC008010E

/**
 * @struct nvhost_ioctl_ctrl_event_wait_args
 * @brief Arguments to wait on a syncpt
 */
typedef struct {
	uint32_t syncpt_id; ///< In
	uint32_t threshold; ///< In
	int32_t timeout; ///< In
	uint32_t value; ///< Inout
} nvhost_ioctl_ctrl_event_wait_args;

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
 * @struct nvmap_ioc_free_args
 * @brief Memory freeing args structure for the nvmap object. 
 */
typedef struct {
	uint32_t handle;
	uint32_t pad;
	uint64_t refcount; ///< out
	uint32_t size; ///< out
	uint32_t flags; ///< out (1=NOT_FREED_YET)
} nvmap_ioc_free_args;

/**
* @struct nvmap_ioc_param_args
* @brief Info query args structure for an nvmap object.
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
* @brief ID query args structure for an nvmap object.
*
*        Identical to Linux driver.
*/
typedef struct {
	uint32_t id; ///< Out ~0 indicates error
	uint32_t handle; ///< In
} nvmap_ioc_get_id_args;

#ifdef __cplusplus
}
#endif
