/**
 * @file libtransistor/ipc/vi.h
 * @brief Video Services
 */

#pragma once

#include<libtransistor/types.h>
#include<libtransistor/ipc/am.h>
#include<libtransistor/display/display.h>
#include<libtransistor/display/surface.h>

/**
* @brief Initialize video service
*/
result_t vi_init();

/**
* @brief Open display
*
* @param name Description
* @param out Description
*/
result_t vi_open_display(const char *name, display_t *out);

/**
* @brief Close display
*
* @param display Description
*/
result_t vi_close_display(display_t *display);

/**
* @brief Display V-Sync event
*
* @param display Description
*/
result_t vi_get_display_vsync_event(display_t *display);

/**
* @brief Create stray layer
*
* @param unknown Description
* @param display Description
* @param layer_id Description
* @param igbp Description
*/
result_t vi_create_stray_layer(uint32_t unknown, display_t *display, uint64_t *layer_id, igbp_t *igbp);

/**
* @brief Open a layer
*
* @param display_name Description
* @param layer_id Description
* @param aruid Description
* @param igbp Description
*/
result_t vi_open_layer(const char *display_name, uint64_t layer_id, aruid_t aruid, igbp_t *igbp);

/**
* @brief Create a managed layer
*
* @param unknown Description
* @param display Description
* @param aruid Description
* @param layer_id Description
*/
result_t vi_create_managed_layer(uint32_t unknown, display_t *display, uint64_t aruid, uint64_t *layer_id);

/**
* @brief Destroy a managed layer
*
* @param layer_id Description
*/
result_t vi_destroy_managed_layer(uint64_t layer_id);

/**
* @brief Adjust reference count
*
* @param handle Description
* @param addval Description
* @param type Description
*/
result_t vi_adjust_refcount(int32_t handle, int32_t addval, int32_t type);

/**
* @brief Transact parcel
*
* @param handle Description
* @param transaction Description
* @param flags Description
* @param in_parcel Description
* @param in_parcel_size Description
* @param out_parcel Description
* @param out_parcel_size Description
*/
result_t vi_transact_parcel(int32_t handle, uint32_t transaction, uint32_t flags, void *in_parcel, size_t in_parcel_size, void *out_parcel, size_t out_parcel_size);

/**
* @brief IManagerDisplayServices - Set layer visibility
*
* @param visible Description
* @param layer_id Description
*/
result_t vi_imds_set_layer_visibility(bool visible, uint64_t layer_id);

/**
* @brief IManagerDisplayServices - Set display layer
*
* @param stack Description
* @param display Description
*/
result_t vi_imds_set_display_layer_stack(uint32_t stack, display_t *display);

/**
* @brief IManagerDisplayServices - Add to layer stack
*
* @param stack Description
* @param layer_id Description
*/
result_t vi_imds_add_to_layer_stack(uint32_t stack, uint64_t layer_id);

/**
* @brief IManagerDisplayServices - Set conductor layer
*
* @param conductor Description
* @param layer_id Description
*/
result_t vi_imds_set_conductor_layer(bool conductor, uint64_t layer_id);

/**
* @brief IManagerDisplayServices - Set content visibility
*
* @param visible Description
*/
result_t vi_imds_set_content_visibility(bool visible);

/**
* @brief ISystemDisplayServices - Get Z order count minimum
*
* @param layer_id Description
* @param z_count_min Description
*/
result_t vi_isds_get_z_order_count_min(uint64_t layer_id, int64_t *z_count_min);

/**
* @brief ISystemDisplayServices - Get Z order count maximum
*
* @param layer_id Description
* @param z_count_max Description
*/
result_t vi_isds_get_z_order_count_max(uint64_t layer_id, int64_t *z_count_max);

/**
* @brief ISystemDisplayServices - Get display logical resolution
*
* @param display Description
* @param width Description
* @param height Description
*/
result_t vi_isds_get_display_logical_resolution(display_t *display, int32_t *width, int32_t *height);

/**
* @brief ISystemDisplayServices - Set layer position
*
* @param x Description
* @param y Description
* @param layer_id Description
*/
result_t vi_isds_set_layer_position(float x, float y, uint64_t layer_id);

/**
* @brief ISystemDisplayServices - Set layer size
*
* @param layer_id Description
* @param width Description
* @param height Description
*/
result_t vi_isds_set_layer_size(uint64_t layer_id, int64_t width, int64_t height);

/**
* @brief ISystemDisplayServices - Get layer Z order
*
* @param layer_id Description
* @param z Description
*/
result_t vi_isds_get_layer_z(uint64_t layer_id, int64_t *z);

/**
* @brief ISystemDisplayServices - Set layer Z order
*
* @param layer_id Description
* @param z Description
*/
result_t vi_isds_set_layer_z(uint64_t layer_id, int64_t z);

/**
* @brief ISystemDisplayServices - Set layer visibility
*
* @param visible Description
* @param layer_id Description
*/
result_t vi_isds_set_layer_visibility(bool visible, uint64_t layer_id);

/**
* @brief IApplicationDisplayServices - Set display enabled
*
* @param enabled Description
* @param display Description
*/
result_t vi_iads_set_display_enabled(bool enabled, display_t *display);

/**
* @brief IApplicationDisplayServices - Set layer scaling mode
*
* @param scaling_mode Description
* @param layer_id Description
*/
result_t vi_iads_set_layer_scaling_mode(uint32_t scaling_mode, uint64_t layer_id);

/**
* @brief Finalize video service
*/
void vi_finalize();
