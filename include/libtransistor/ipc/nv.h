/**
 * @file libtransistor/ipc/nv.h
 * @brief Nvidia Services
 */

#pragma once

#ifdef __cplusplus
extern "C" {
#endif

#include<libtransistor/types.h>

extern result_t nv_result;
extern int nv_errno;

/**
* @brief Initialize NV service
*/
result_t nv_init();

/**
* @brief Open a device
*
* @param path Path of device to open
* @returns File descriptor of device or -1 upon error
*/
int nv_open(const char *path);

/**
* @brief Issues an ioctl on the device
*
* @param fd Device file descriptor
* @param rq Ioctl ID
* @param arg Arguments struct
* @param size Size of arguments struct
*/
int nv_ioctl(int fd, uint32_t rq, void *arg, size_t size);

/**
* @brief Close the device
*
* @param fd Device file descriptor
*/
int nv_close(int fd);

/**
* @brief Finalize NV service
*/
void nv_finalize();

#ifdef __cplusplus
}
#endif
