/**
 * @file libtransistor/ipc/sm.h
 * @brief Service Manager
 */

#pragma once

#include<libtransistor/types.h>

/**
* @brief Initialize Service Manager
*/
result_t sm_init();

/**
* @brief Get a service by name
*
* @param session Description here...
* @param name The name of the service to get
*/
result_t sm_get_service(ipc_object_t *session, char *name);

/**
* @brief Finalize Service Manager
*/
void sm_finalize();
