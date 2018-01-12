/**
 * @file libtransistor/display/graphic_buffer_queue.h
 * @brief Graphics buffer queues data structures and functions
 */

#pragma once

#include<libtransistor/types.h>
#include<libtransistor/display/binder.h>
#include<libtransistor/display/graphic_buffer.h>
#include<libtransistor/display/fence.h>
#include<libtransistor/display/rect.h>

/**
* @struct igbp_t
* @brief IGraphicBufferProducer
*/
typedef struct {
	binder_t igbp_binder; ///< IGraphicBufferProducer
} igbp_t;

/**
* @enum pixel_format_t
* @brief Various pixel formats
*
*        There are more but these are probably the only ones we're ever going to use
*/
typedef enum {
	RGBA_8888 = 0x1, ///< Full RGBA channels
	RGBX_8888 = 0x2, ///< RGB channels normal, X always 255 (Alpha is ignored)
	RGB_888 = 0x3, ///< Only RGB channels, no alpha
} pixel_format_t;

/**
* @struct compositor_timing_t
* @brief Description here...
*/
typedef struct {
	int64_t deadline_ns;
	int64_t internal_ns;
	int64_t present_latency_ns;
} compositor_timing_t;

/**
* @struct frame_event_history_delta_t
* @brief ToDo: maybe someday actually implement this
*/
typedef struct {
	compositor_timing_t compositor_timing;
} frame_event_history_delta_t;

/**
* @enum dataspace_t
* @brief Unknown
*/
enum {
	UNKNOWN = 0x0
} dataspace_t;

/**
* @struct queue_buffer_input_t
* @brief Description here...
*/
typedef struct {
	int64_t timestamp;
	bool is_auto_timestamp;
	rect_t crop;
	int32_t scaling_mode;
	uint32_t transform;
	fence_t fence;
	// and a few more unknown fields
} queue_buffer_input_t;

/**
* @struct queue_buffer_output_t
* @brief Output buffer for graphics queue
*/
typedef struct {
	uint32_t width;
	uint32_t height;
	uint32_t transform_hint;
	uint32_t num_pending_buffers;
	uint64_t next_frame_number;
	bool buffer_replaced;
	frame_event_history_delta_t frame_timestamps;
} queue_buffer_output_t;


/**
* @brief Request a buffer from the IGraphicBufferProducer 
*
* @param igbp Description
* @param slot Description
* @param status Description
* @param gb Description
*/
result_t igbp_request_buffer(igbp_t *igbp, int slot, int *status, graphic_buffer_t *gb);

/**
* @brief Dequeue a buffer from the IGraphicBufferProducer
*
* @param igbp Description
* @param width Description
* @param height Description
* @param pixel_format Description
* @param usage Description
* @param get_frame_timestamps Description
* @param status Description
* @param slot Description
* @param fence Description
* @param out_timestamps Description
*/
result_t igbp_dequeue_buffer(igbp_t *igbp, uint32_t width, uint32_t height, pixel_format_t pixel_format, uint32_t usage, bool get_frame_timestamps, int *status, int *slot, fence_t *fence, frame_event_history_delta_t *out_timestamps);

/**
* @brief Queue a buffer to the IGraphicBufferProducer
*
* @param igbp Description
* @param slot Description
* @param qbi Description
* @param qbo Description
* @param status Description
*/
result_t igbp_queue_buffer(igbp_t *igbp, int slot, queue_buffer_input_t *qbi, queue_buffer_output_t *qbo, int *status);

/**
* @brief Cancel a buffer on the IGraphicBufferProducer
*
* @param igbp Description
* @param slot Description
* @param fence Description
*/
result_t igbp_cancel_buffer(igbp_t *igbp, int slot, fence_t *fence);

/**
* @brief Query a buffer on the IGraphicBufferProducer
*
* @param igbp Description
* @param what Description
* @param status Description
* @param value Description
*/
result_t igbp_query(igbp_t *igbp, int what, int *status, int *value);

/**
* @brief Connect to the IGraphicBufferProducer
*
* @param igbp Description
* @param api Description
* @param producer_controlled_by_app Description
* @param status Description
* @param qbo Description
*/
result_t igbp_connect(igbp_t *igbp, int api, bool producer_controlled_by_app, int *status, queue_buffer_output_t *qbo);

/**
* @brief Set a pre-allocated buffer on the IGraphicBufferProducer
*
* @param igbp Description
* @param slot Description
* @param gb Description
*/
result_t igbp_set_preallocated_buffer(igbp_t *igbp, int slot, graphic_buffer_t *gb);
