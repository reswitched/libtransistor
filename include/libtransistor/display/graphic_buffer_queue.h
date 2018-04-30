/**
 * @file libtransistor/display/graphic_buffer_queue.h
 * @brief Graphics buffer queues data structures and functions
 */

#pragma once

#ifdef __cplusplus
extern "C" {
#endif

#include<libtransistor/types.h>
#include<libtransistor/display/binder.h>
#include<libtransistor/display/graphic_buffer.h>
#include<libtransistor/display/fence.h>
#include<libtransistor/display/rect.h>

/**
* @struct igbp_t
* @brief IGraphicBufferProducer object
*
* https://source.android.com/reference/hidl/android/hardware/graphics/bufferqueue/1.0/IGraphicBufferProducer
*/
typedef struct {
	binder_t igbp_binder; ///< IGraphicBufferProducer
} igbp_t;

/**
* @enum pixel_format_t
* @brief Various pixel formats
*
* There are more but these are probably the only ones we're ever going to use
*/
typedef enum {
	RGBA_8888 = 0x1, ///< Full RGBA channels
	RGBX_8888 = 0x2, ///< RGB channels normal, X always 255 (Alpha is ignored)
	RGB_888 = 0x3, ///< Only RGB channels, no alpha
} pixel_format_t;

/**
 * @enum disconnect_mode_t
 * @brief Disconnection mode
 *
 * https://source.android.com/reference/hidl/android/hardware/graphics/bufferqueue/1.0/IGraphicBufferProducer#disconnectmode
 */
typedef enum {
	API,
	ALL_LOCAL
} disconnect_mode_t;

/**
* @struct compositor_timing_t
* @brief Description here...
*
* https://source.android.com/reference/hidl/android/hardware/graphics/bufferqueue/1.0/IGraphicBufferProducer#compositortiming
*/
typedef struct {
	int64_t deadline_ns;
	int64_t internal_ns;
	int64_t present_latency_ns;
} compositor_timing_t;

/**
* @struct frame_event_history_delta_t
* @brief ToDo: maybe someday actually implement this
*
* https://source.android.com/reference/hidl/android/hardware/graphics/bufferqueue/1.0/IGraphicBufferProducer#frameeventhistorydelta
*/
typedef struct {
	compositor_timing_t compositor_timing;
} frame_event_history_delta_t;

typedef enum {
	UNKNOWN = 0x0
} dataspace_t;

/**
* @struct queue_buffer_input_t
* @brief Parameters passed to queueBuffer
*
* https://source.android.com/reference/hidl/android/hardware/graphics/bufferqueue/1.0/IGraphicBufferProducer#queuebufferinput
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
* @brief Values received back from queueBuffer
*
* https://source.android.com/reference/hidl/android/hardware/graphics/bufferqueue/1.0/IGraphicBufferProducer#queuebufferoutput
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
* @param igbp IGraphicBufferProducer to request buffer from
* @param slot Slot to request buffer from
* @param status The returned status from the IGraphicBufferProducer interface
* @param gb The requested GraphicBuffer
*
* https://source.android.com/reference/hidl/android/hardware/graphics/bufferqueue/1.0/IGraphicBufferProducer#requestbuffer
*/
result_t igbp_request_buffer(igbp_t *igbp, uint32_t slot, uint32_t *status, graphic_buffer_t *gb);

/**
* @brief Dequeue a buffer from the IGraphicBufferProducer
*
* @param igbp IGraphicBufferProducer to dequeue buffer from
* @param width Width of buffer to dequeue
* @param height Height of buffer to dequeue
* @param pixel_format Pixel format of buffer to dequeue
* @param usage Usage flags of buffer to sequeue
* @param get_frame_timestamps Whether or not to get frame timestamps
* @param status The returned status from the IGraphicBufferProducer interface
* @param slot The slot of the buffer that was dequeued
* @param fence The fence to wait on before writing to the dequeued buffer
* @param out_timestamps Frame event timestamp history
*
* https://source.android.com/reference/hidl/android/hardware/graphics/bufferqueue/1.0/IGraphicBufferProducer#dequeuebuffer
*/
result_t igbp_dequeue_buffer(igbp_t *igbp, uint32_t width, uint32_t height, pixel_format_t pixel_format, uint32_t usage, bool get_frame_timestamps, uint32_t *status, uint32_t *slot, fence_t *fence, frame_event_history_delta_t *out_timestamps);

/**
* @brief Queue a buffer to the IGraphicBufferProducer
*
* @param igbp IGraphicBufferProducer to queue buffer to
* @param slot Slot of the buffer to queue
* @param qbi Input parameters
* @param qbo Output values
* @param status Status returned from IGraphicBufferProducer
*
* https://source.android.com/reference/hidl/android/hardware/graphics/bufferqueue/1.0/IGraphicBufferProducer#queuebuffer
*/
result_t igbp_queue_buffer(igbp_t *igbp, int slot, queue_buffer_input_t *qbi, queue_buffer_output_t *qbo, int *status);

/**
* @brief Cancel a buffer on the IGraphicBufferProducer
*
* @param igbp IGraphicBufferProducer to cancel a buffer on
* @param slot Slot of the buffer to cancel
* @param fence Fence that must be waited on before it's ok to overwrite the buffer
*
* https://source.android.com/reference/hidl/android/hardware/graphics/bufferqueue/1.0/IGraphicBufferProducer#cancelbuffer
*/
result_t igbp_cancel_buffer(igbp_t *igbp, int slot, fence_t *fence);

/**
* @brief Query values on the IGraphicBufferProducer
*
* @param igbp IGBP to query
* @param what Which value to query
* @param status Returned status
* @param value Returned value
*
* https://source.android.com/reference/hidl/android/hardware/graphics/bufferqueue/1.0/IGraphicBufferProducer#query
*/
result_t igbp_query(igbp_t *igbp, int what, int *status, int *value);

/**
* @brief Connect to the IGraphicBufferProducer
*
* @param igbp IGBP to connect to
* @param api Description
* @param producer_controlled_by_app Description
* @param status Description
* @param qbo Description
*
* https://source.android.com/reference/hidl/android/hardware/graphics/bufferqueue/1.0/IGraphicBufferProducer#connect
*/
result_t igbp_connect(igbp_t *igbp, int api, bool producer_controlled_by_app, int *status, queue_buffer_output_t *qbo);

/**
* @brief Disconnect from the IGraphicBufferProducer
*
* @param igbp IGBP to disconnect from
* @param api Description
* @param mode Disconnect mode
* @param status Status output
*
* https://source.android.com/reference/hidl/android/hardware/graphics/bufferqueue/1.0/IGraphicBufferProducer#disconnect
*/
result_t igbp_disconnect(igbp_t *igbp, int api, disconnect_mode_t mode, int *status);

/**
* @brief Set a pre-allocated buffer on the IGraphicBufferProducer
*
* @param igbp IGBP to preallocate a buffer on
* @param slot Slot to preallocate the buffer in
* @param gb Preallocated GraphicBuffer
*
* This one seems to be Nintendo custom.
*/
result_t igbp_set_preallocated_buffer(igbp_t *igbp, int slot, graphic_buffer_t *gb);

#ifdef __cplusplus
}
#endif
