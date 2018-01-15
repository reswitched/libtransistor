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
* @param session Acquired service
* @param name The name of the service to get
*/
result_t sm_get_service(ipc_object_t *session, char *name);

/**
* @brief Get a service by name, optinally requiring that it has been overriden by the loader
*
* @param session Acquired service
* @param name The name of the service to get
* @param require_override Whether or not to require that this service has been overriden by the loader
*/
result_t sm_get_service_ex(ipc_object_t *session, char *name, bool require_override);

/**
* @brief Finalize Service Manager
*/
void sm_finalize();
