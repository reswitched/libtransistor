/**
 * @file libtransistor/ipc/vi.h
 * @brief Video Services
 */

#pragma once

#include<libtransistor/types.h>
#include<libtransistor/ipc/am.h>
#include<libtransistor/display/display.h>
#include<libtransistor/display/surface.h>

result_t vi_init();
result_t vi_open_display(const char *name, display_t *out);
result_t vi_close_display(display_t *display);
result_t vi_get_display_vsync_event(display_t *display);
result_t vi_create_stray_layer(uint32_t unknown, display_t *display, uint64_t *layer_id, igbp_t *igbp);
result_t vi_open_layer(const char *display_name, uint64_t layer_id, aruid_t aruid, igbp_t *igbp);
result_t vi_create_managed_layer(uint32_t unknown, display_t *display, uint64_t aruid, uint64_t *layer_id);
result_t vi_destroy_managed_layer(uint64_t layer_id);

result_t vi_adjust_refcount(int32_t handle, int32_t addval, int32_t type);
result_t vi_transact_parcel(int32_t handle, uint32_t transaction, uint32_t flags, void *in_parcel, size_t in_parcel_size, void *out_parcel, size_t out_parcel_size);

// imds
result_t vi_imds_set_layer_visibility(bool visible, uint64_t layer_id);
result_t vi_imds_set_display_layer_stack(uint32_t stack, display_t *display);
result_t vi_imds_add_to_layer_stack(uint32_t stack, uint64_t layer_id);
result_t vi_imds_set_conductor_layer(bool conductor, uint64_t layer_id);
result_t vi_imds_set_content_visibility(bool visible);

// isds
result_t vi_isds_get_z_order_count_min(uint64_t layer_id, int64_t *z_count_min);
result_t vi_isds_get_z_order_count_max(uint64_t layer_id, int64_t *z_count_max);
result_t vi_isds_get_display_logical_resolution(display_t *display, int32_t *width, int32_t *height);
result_t vi_isds_set_layer_position(float x, float y, uint64_t layer_id);
result_t vi_isds_set_layer_size(uint64_t layer_id, int64_t width, int64_t height);
result_t vi_isds_get_layer_z(uint64_t layer_id, int64_t *z);
result_t vi_isds_set_layer_z(uint64_t layer_id, int64_t z);
result_t vi_isds_set_layer_visibility(bool visible, uint64_t layer_id);

// iads
result_t vi_iads_set_display_enabled(bool enabled, display_t *display);
result_t vi_iads_set_layer_scaling_mode(uint32_t scaling_mode, uint64_t layer_id);

void vi_finalize();
