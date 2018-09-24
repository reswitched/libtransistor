/**
 * @file libtransistor/ipc/vi.h
 * @brief Visual Services
 */

#pragma once

#ifdef __cplusplus
extern "C" {
#endif

#include<libtransistor/types.h>
#include<libtransistor/ipc/am.h>
#include<libtransistor/display/display.h>
#include<libtransistor/display/surface.h>

/**
* @brief Initialize visual services
*/
result_t vi_init();

/**
* @brief Open display
*
* @param name Name of display to open
* @param out Structure to initialize
*
* `Default` is usually a good option for which display to open.
*/
result_t vi_open_display(const char *name, display_t *out);

/**
* @brief Close display
*
* @param display Display to close
*/
result_t vi_close_display(display_t *display);

/**
* @brief Get the V-Sync event for the given display
*
* @param display Display to get V-Sync event for
*/
result_t vi_get_display_vsync_event(display_t *display);

/**
* @brief Create a stray layer
*
* @param unknown Unknown
* @param display Display to create it for
* @param layer_id ID of created layer
* @param igbp IGraphicBufferProducer for the newly created layer
*/
result_t vi_create_stray_layer(uint32_t unknown, display_t *display, uint64_t *layer_id, igbp_t *igbp);

/**
* @brief Open a managed layer
*
* @param display_name Name of display
* @param layer_id ID of existing managed layer
* @param aruid Applet resource user ID
* @param igbp IGraphicBufferProducer for the layer
*/
result_t vi_open_layer(const char *display_name, uint64_t layer_id, aruid_t aruid, igbp_t *igbp);

/**
* @brief Close a managed layer
*
* @param layer_id ID of existing managed layer
*/
result_t vi_close_layer(uint64_t layer_id);

/**
* @brief Create a managed layer
*
* @param unknown Unknown
* @param display Display
* @param aruid Applet resource user ID
* @param layer_id ID of newly created layer
*/
result_t vi_create_managed_layer(uint32_t unknown, display_t *display, uint64_t aruid, uint64_t *layer_id);

/**
* @brief Destroy a managed layer
*
* @param layer_id Layer ID
*/
result_t vi_destroy_managed_layer(uint64_t layer_id);

/**
* @brief Adjust reference count
*
* @param handle Binder handle
* @param addval Value to add to reference count
* @param type Type of reference?
*/
result_t vi_adjust_refcount(int32_t handle, int32_t addval, int32_t type);

/**
* @brief Transact parcel
*
* @param handle Binder handle
* @param transaction Transaction ID
* @param flags Transaction flags
* @param in_parcel Parcel data
* @param in_parcel_size Size of parcel data
* @param out_parcel Parcel data
* @param out_parcel_size Size of parcel data
*/
result_t vi_transact_parcel(int32_t handle, uint32_t transaction, uint32_t flags, void *in_parcel, size_t in_parcel_size, void *out_parcel, size_t out_parcel_size);

/**
 * @brief Get a native handle from a binder
 */
result_t vi_get_native_handle(int32_t handle, uint32_t native_id, revent_h *out);

/**
* @brief IManagerDisplayServices - Set layer visibility
*
* @param visible Visible
* @param layer_id Layer ID
*/
result_t vi_imds_set_layer_visibility(bool visible, uint64_t layer_id);

/**
* @brief IManagerDisplayServices - Set display layer stack
*
* @param stack ID of layer stack
* @param display Display
*
* Not really sure about this, but I think it changes which layer stack
* is currently being displayed.
*/
result_t vi_imds_set_display_layer_stack(uint32_t stack, display_t *display);

/**
* @brief IManagerDisplayServices - Add to layer stack
*
* @param stack ID of layer stack
* @param layer_id Layer to add to stack
*/
result_t vi_imds_add_to_layer_stack(uint32_t stack, uint64_t layer_id);

/**
* @brief IManagerDisplayServices - Set conductor layer
*
* @param conductor Is conductor
* @param layer_id Layer ID
*
* No idea what "conductor" means in this context.
*/
result_t vi_imds_set_conductor_layer(bool conductor, uint64_t layer_id);

/**
* @brief IManagerDisplayServices - Set content visibility
*
* @param visible Visible
*/
result_t vi_imds_set_content_visibility(bool visible);

/**
* @brief ISystemDisplayServices - Get Z order count minimum
*
* @param layer_id Layer ID
* @param z_count_min Output for Z order count minimum
*/
result_t vi_isds_get_z_order_count_min(uint64_t layer_id, int64_t *z_count_min);

/**
* @brief ISystemDisplayServices - Get Z order count maximum
*
* @param layer_id Layer ID
* @param z_count_max Output for Z order count minimum
*/
result_t vi_isds_get_z_order_count_max(uint64_t layer_id, int64_t *z_count_max);

/**
* @brief ISystemDisplayServices - Get display logical resolution
*
* @param display Display
* @param width Output for width
* @param height Output for height
*/
result_t vi_isds_get_display_logical_resolution(display_t *display, int32_t *width, int32_t *height);

/**
* @brief ISystemDisplayServices - Set layer position
*
* @param x X position
* @param y Y position
* @param layer_id Layer
*/
result_t vi_isds_set_layer_position(float x, float y, uint64_t layer_id);

/**
* @brief ISystemDisplayServices - Set layer size
*
* @param layer_id Layer
* @param width Width
* @param height Height
*/
result_t vi_isds_set_layer_size(uint64_t layer_id, int64_t width, int64_t height);

/**
* @brief ISystemDisplayServices - Get layer Z order
*
* @param layer_id Layer
* @param z Output for Z order
*/
result_t vi_isds_get_layer_z(uint64_t layer_id, int64_t *z);

/**
* @brief ISystemDisplayServices - Set layer Z order
*
* @param layer_id Layer
* @param z Z order
*/
result_t vi_isds_set_layer_z(uint64_t layer_id, int64_t z);

/**
* @brief ISystemDisplayServices - Set layer visibility
*
* @param visible Is visible?
* @param layer_id Layer
*/
result_t vi_isds_set_layer_visibility(bool visible, uint64_t layer_id);

/**
* @brief IApplicationDisplayServices - Set display enabled
*
* @param enabled Enabled?
* @param display Display
*/
result_t vi_iads_set_display_enabled(bool enabled, display_t *display);

/**
* @brief IApplicationDisplayServices - Set layer scaling mode
*
* @param scaling_mode Scaling mode
* @param layer_id Layer
*
* see https://android.googlesource.com/platform/system/core/+/7cd3e0a3a2f9b104cd6c04f699ae62c4577787e2/include/system/window.h#270
*/
result_t vi_iads_set_layer_scaling_mode(uint32_t scaling_mode, uint64_t layer_id);

/**
* @brief Finalize visual services
*/
void vi_finalize();

#ifdef __cplusplus
}
#endif
