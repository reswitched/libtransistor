#include<libtransistor/err.h>
#include<libtransistor/types.h>
#include<libtransistor/display/binder.h>
#include<libtransistor/display/graphic_buffer.h>
#include<libtransistor/display/fence.h>
#include<libtransistor/display/surface.h>

#define INTERFACE_TOKEN "android.gui.IGraphicBufferProducer"

enum {
  REQUEST_BUFFER = 0x1,
  SET_BUFFER_COUNT = 0x2,
  DEQUEUE_BUFFER = 0x3,
  DETACH_BUFFER = 0x4,
  DETACH_NEXT_BUFFER = 0x5,
  ATTACH_BUFFER = 0x6,
  QUEUE_BUFFER = 0x7,
  CANCEL_BUFFER = 0x8,
  QUERY = 0x9,
  CONNECT = 0xA,
  DISCONNECT = 0xB,
  // 0xC might be SET_SIDEBAND_STREAM but I'm not sure
  ALLOCATE_BUFFERS = 0xD,
  SET_PREALLOCATED_BUFFER = 0xE
};

static result_t queue_buffer_output_unflatten(parcel_t *parcel, queue_buffer_output_t *qbo) {
  if(parcel_read_remaining(parcel) < 4*sizeof(uint32_t)) {
    return LIBTRANSISTOR_ERR_PARCEL_DATA_UNDERRUN;
  }

  qbo->width = parcel_read_u32(parcel);
  qbo->height = parcel_read_u32(parcel);
  qbo->transform_hint = parcel_read_u32(parcel);
  qbo->num_pending_buffers = parcel_read_u32(parcel);

  return RESULT_OK;
}

result_t surface_request_buffer(surface_t *surf, int slot, int *status, graphic_buffer_t *gb) {
  return LIBTRANSISTOR_ERR_UNIMPLEMENTED;
}

result_t surface_dequeue_buffer(surface_t *surf, uint32_t width, uint32_t height, pixel_format_t pixel_format, uint32_t usage, bool get_frame_timestamps, int *status, int *slot, fence_t *fence, frame_event_history_delta_t *out_timestamps) {
  return LIBTRANSISTOR_ERR_UNIMPLEMENTED;
}

result_t surface_queue_buffer(surface_t *surf, int slot, queue_buffer_input_t *qbi, queue_buffer_output_t *qbo) {
  return LIBTRANSISTOR_ERR_UNIMPLEMENTED;
}

result_t surface_cancel_buffer(surface_t *surf, int slot, fence_t *fence) {
  return LIBTRANSISTOR_ERR_UNIMPLEMENTED;
}

result_t surface_query(surface_t *surf, int what, int *status, int *value) {
  return LIBTRANSISTOR_ERR_UNIMPLEMENTED;
}

result_t surface_connect(surface_t *surf, int api, bool producer_controlled_by_app, int *status, queue_buffer_output_t *qbo) {
  result_t r;
  
  parcel_t parcel;
  parcel_initialize(&parcel);

  parcel_write_interface_token(&parcel, INTERFACE_TOKEN);
  parcel_write_u32(&parcel, 0); // IProducerListener is null because we don't support it in libtransistor (yet)
  parcel_write_u32(&parcel, api);
  parcel_write_u32(&parcel, producer_controlled_by_app ? 1 : 0);

  parcel_t response;
  r = binder_transact_parcel(&(surf->igbp_binder), CONNECT, 0, &parcel, &response);
  if(r) {
    return r;
  }

  r = queue_buffer_output_unflatten(&response, qbo);
  if(r) {
    return r;
  }

  if(parcel_read_remaining(&response) < sizeof(uint32_t)) {
    return LIBTRANSISTOR_ERR_PARCEL_DATA_UNDERRUN;
  }

  *status = parcel_read_u32(&response);

  return RESULT_OK;
}

result_t surface_set_preallocated_buffer(surface_t *surf, int slot, graphic_buffer_t *gb) {
  return LIBTRANSISTOR_ERR_UNIMPLEMENTED;
}
