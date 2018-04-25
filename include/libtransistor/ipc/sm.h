/**
 * @file libtransistor/ipc/sm.h
 * @brief Service Manager
 */

#pragma once

#ifdef __cplusplus
extern "C" {
#endif

#include<libtransistor/types.h>
#include<libtransistor/ipc.h>

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
result_t sm_get_service(ipc_object_t *session, const char *name);

/**
* @brief Get a service by name, optinally requiring that it has been overriden by the loader
*
* @param session Acquired service
* @param name The name of the service to get
* @param require_override Whether or not to require that this service has been overriden by the loader
*/
result_t sm_get_service_ex(ipc_object_t *session, const char *name, bool require_override);

/**
 * @brief Register a service by name
 *
 * @param port Output for newly created port
 * @param name Name to register service under
 * @param max_sessions Maximum number of sessions allowed
 */
result_t sm_register_service(port_h *port, const char *name, uint32_t max_sessions);

/**
 * @brief Unregister a service
 *
 * @param name Name of service to unregister
 */
result_t sm_unregister_service(const char *name);

/**
* @brief Finalize Service Manager
*/
void sm_finalize();

#ifdef __cplusplus
}
#endif
