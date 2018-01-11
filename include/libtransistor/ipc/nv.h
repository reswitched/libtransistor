/**
 * @file libtransistor/ipc/nv.h
 * @brief Nvidia Services
 */

#pragma once

#include<libtransistor/types.h>

extern result_t nv_result;
extern int nv_errno;

/**
* @brief Initialize NV service
*/
result_t nv_init();

/**
* @brief Description here...
*
* @param path Description here...
*/
int nv_open(const char *path);

/**
* @brief Description here...
*
* @param fd Description here...
* @param rq Description here...
* @param arg Description here...
* @param size Description here...
*/
int nv_ioctl(int fd, uint32_t rq, void *arg, size_t size);

/**
* @brief Description here...
*
* @param fd Description here...
*/
int nv_close(int fd);

/**
* @brief Finalize NV service
*/
void nv_finalize();
