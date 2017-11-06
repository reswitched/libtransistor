#include<libtransistor/types.h>
#include<libtransistor/svc.h>
#include<libtransistor/ipc.h>
#include<libtransistor/err.h>
#include<libtransistor/util.h>
#include<libtransistor/ipc/sm.h>
#include<libtransistor/ipc/vi.h>
#include<libtransistor/display/parcel.h>
#include<libtransistor/display/surface.h>

#include<string.h>
#include<malloc.h>

result_t vi_result;
int vi_errno;

static ipc_domain_t vi_domain;
static ipc_object_t imrs_object; // nn::visrv::sf::IManagerRootService
static ipc_object_t iads_object; // nn::visrv::sf::IApplicationDisplayService
static ipc_object_t imds_object; // nn::visrv::sf::IManagerDisplayService
static ipc_object_t isds_object; // nn::visrv::sf::ISystemDisplayService
static ipc_object_t ihosbd_object; // nn::visrv::sf::IHOSBinderDriver
static bool vi_initialized = false;

static result_t get_object(ipc_object_t iface, int command, ipc_object_t *out) {
  ipc_request_t rq = ipc_default_request;
  rq.request_id = command;

  ipc_response_fmt_t rs = ipc_default_response_fmt;
  rs.num_objects = 1;
  rs.objects = out;

  return ipc_send(iface, &rq, &rs);
}

result_t vi_init() {
  if(vi_initialized) {
    return RESULT_OK;
  }
  
  result_t r;
  r = sm_get_service(&imrs_object, "vi:m");
  if(r) {
    goto fail_no_service;
  }

  r = ipc_convert_to_domain(&imrs_object, &vi_domain);
  if(r) {
    goto fail_domain;
  }

  {
    uint32_t raw[] = {0};
    ipc_request_t rq = ipc_default_request;
    rq.request_id = 2;
    rq.raw_data_size = sizeof(raw);
    rq.raw_data = raw;

    ipc_response_fmt_t rs = ipc_default_response_fmt;
    rs.num_objects = 1;
    rs.objects = &iads_object;

    r = ipc_send(imrs_object, &rq, &rs);
    if(r) {
      goto fail_imrs;
    }
  }

  if((r = get_object(iads_object, 100, &ihosbd_object)) != 0) { goto fail_iads; }
  if((r = get_object(iads_object, 101, &isds_object)) != 0) { goto fail_ihosbd; }
  if((r = get_object(iads_object, 102, &imds_object)) != 0) { goto fail_isds; }

  vi_initialized = true;
  
  return 0;
  
 fail_isds:
  ipc_close(isds_object);
 fail_ihosbd:
  ipc_close(ihosbd_object);
 fail_iads:
  ipc_close(iads_object);
 fail_imrs:
  ipc_close(imrs_object);
 fail_domain:
  ipc_close_domain(vi_domain);
 fail_no_service:
  return r;
}

result_t vi_open_display(const char *name, display_t *out) {
  uint8_t raw[0x40];
  memset(raw, 0, sizeof(raw));
  strncpy((char*) raw, name, sizeof(raw)-1);

  ipc_request_t rq = ipc_default_request;
  rq.request_id = 1010; // OpenDisplay
  rq.raw_data_size = sizeof(raw);
  rq.raw_data = (uint32_t*) raw;

  ipc_response_fmt_t rs = ipc_default_response_fmt;
  rs.raw_data_size = sizeof(out->id);
  rs.raw_data = (uint32_t*) &(out->id);

  return ipc_send(iads_object, &rq, &rs);
}

result_t vi_create_stray_layer(uint32_t unknown, display_t *display, surface_t *surface) {
  uint8_t parcel_buf[0x210];
  ipc_buffer_t parcel_ipc_buf;
  parcel_ipc_buf.addr = parcel_buf;
  parcel_ipc_buf.size = sizeof(parcel_buf);
  parcel_ipc_buf.type = 6;

  ipc_buffer_t *buffers[] = {&parcel_ipc_buf};
  
  struct {
    uint32_t unknown;
    uint32_t padding;
    uint64_t display;
  } rq_args;

  rq_args.unknown = unknown;
  rq_args.display = display->id;
  
  ipc_request_t rq = ipc_default_request;
  rq.request_id = 2030;
  rq.num_buffers = 1;
  rq.buffers = buffers;
  rq.raw_data_size = sizeof(rq_args);
  rq.raw_data = (uint32_t*) &rq_args;

  struct {
    uint64_t layer_id;
    uint64_t surface_size;
  } rs_vals;

  ipc_response_fmt_t rs = ipc_default_response_fmt;
  rs.raw_data_size = sizeof(rs_vals);
  rs.raw_data = (uint32_t*) &rs_vals;

  result_t r = ipc_send(iads_object, &rq, &rs);
  if(r) {
    return r;
  }

  surface->layer_id = rs_vals.layer_id;

  parcel_t parcel;
  r = parcel_load(&parcel, parcel_buf);
  if(r) {
    return r;
  }

  r = parcel_read_binder(&parcel, &(surface->igbp_binder));
  if(r) {
    return r;
  }

  return 0;
}

result_t vi_transact_parcel(int32_t handle, uint32_t transaction, uint32_t flags, void *rq_parcel, size_t rq_parcel_size, void *rs_parcel, size_t rs_parcel_size) {

  ipc_buffer_t rq_buffer;
  rq_buffer.addr = rq_parcel;
  rq_buffer.size = rq_parcel_size;
  rq_buffer.type = 5;

  ipc_buffer_t rs_buffer;
  rs_buffer.addr = rs_parcel;
  rs_buffer.size = rs_parcel_size;
  rs_buffer.type = 6;
  
  ipc_buffer_t *buffers[] = {&rq_buffer, &rs_buffer};

  struct {
    int32_t handle;
    uint32_t transaction;
    uint32_t flags;
  } raw;

  raw.handle = handle;
  raw.transaction = transaction;
  raw.flags = flags;
  
  ipc_request_t rq = ipc_default_request;
  rq.request_id = 0;
  rq.num_buffers = 2;
  rq.buffers = buffers;
  rq.raw_data_size = sizeof(raw);
  rq.raw_data = (uint32_t*) &raw;

  ipc_response_fmt_t rs = ipc_default_response_fmt;

  return ipc_send(ihosbd_object, &rq, &rs);
}

void vi_finalize() {
  ipc_close(isds_object);
  ipc_close(ihosbd_object);
  ipc_close(iads_object);
  ipc_close(imrs_object);
  ipc_close_domain(vi_domain);
}
