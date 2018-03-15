/**
 * @file libtransistor/ipc/am.h
 * @brief AM (Applet Manager)
 */

#pragma once

#ifdef __cplusplus
extern "C" {
#endif

#include<libtransistor/types.h>

/**
 * @brief Initialize Applet Manager
 */
result_t am_init();

/**
 * @brief Creates a new managed display layer
 */
result_t am_isc_create_managed_display_layer(uint64_t *layer_id);

/**
 * @brief 
 */
result_t am_isc_approve_to_display();

/**
 * @brief Get the aruid from the window controller
 */ 
result_t am_iwc_get_applet_resource_user_id(aruid_t *aruid);

/**
 * @brief Acquire the foureground rights from the window controller
 */
result_t am_iwc_acquire_foreground_rights();

/**
 * @brief Finalize Applet Mangager
 */
void am_finalize();

#ifdef __cplusplus
}
#endif
