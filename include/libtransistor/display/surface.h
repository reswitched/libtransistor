#pragma once

#include<libtransistor/types.h>
#include<libtransistor/display/binder.h>
#include<libtransistor/display/graphic_buffer.h>
#include<libtransistor/display/fence.h>
#include<libtransistor/display/rect.h>

typedef struct {
  uint64_t layer_id;
  binder_t igbp_binder; // IGraphicBufferProducer
} surface_t;

// there are more but these are probably the only ones we're ever going to use
typedef enum {
  RGBA_8888 = 0x1,
  RGBX_8888 = 0x2,
  RGB_888 = 0x3,
} pixel_format_t;

typedef struct {
  int64_t deadline_ns;
  int64_t internal_ns;
  int64_t present_latency_ns;
} compositor_timing_t;

typedef struct {
  compositor_timing_t compositor_timing;
  // todo maybe someday: actually implement this
} frame_event_history_delta_t;

enum {
  UNKNOWN = 0x0
} dataspace_t;

typedef struct {
  int64_t timestamp;
  bool is_auto_timestamp;
  rect_t crop;
  int32_t scaling_mode;
  uint32_t transform;
  fence_t fence;
  // and a few more unknown fields
} queue_buffer_input_t;

typedef struct {
  uint32_t width;
  uint32_t height;
  uint32_t transform_hint;
  uint32_t num_pending_buffers;
  uint64_t next_frame_number;
  bool buffer_replaced;
  frame_event_history_delta_t frame_timestamps;
} queue_buffer_output_t;

result_t surface_request_buffer(surface_t *surf, int slot, int *status, graphic_buffer_t *gb);
result_t surface_dequeue_buffer(surface_t *surf, uint32_t width, uint32_t height, pixel_format_t pixel_format, uint32_t usage, bool get_frame_timestamps, int *status, int *slot, fence_t *fence, frame_event_history_delta_t *out_timestamps);
result_t surface_queue_buffer(surface_t *surf, int slot, queue_buffer_input_t *qbi, queue_buffer_output_t *qbo, int *status);
result_t surface_cancel_buffer(surface_t *surf, int slot, fence_t *fence);
result_t surface_query(surface_t *surf, int what, int *status, int *value);
result_t surface_connect(surface_t *surf, int api, bool producer_controlled_by_app, int *status, queue_buffer_output_t *qbo);
result_t surface_set_preallocated_buffer(surface_t *surf, int slot, graphic_buffer_t *gb);
