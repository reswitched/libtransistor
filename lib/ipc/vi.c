#include<libtransistor/types.h>
#include<libtransistor/svc.h>
#include<libtransistor/ipc.h>
#include<libtransistor/err.h>
#include<libtransistor/util.h>
#include<libtransistor/ipc/sm.h>
#include<libtransistor/ipc/vi.h>

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

static result_t get_object(ipc_object_t iface, int command, ipc_object_t *out) {
  ipc_request_t rq = ipc_default_request;
  rq.request_id = command;

  ipc_response_fmt_t rs = ipc_default_response_fmt;
  rs.num_objects = 1;
  rs.objects = out;

  return ipc_send(iface, &rq, &rs);
}

result_t vi_init() {
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

void vi_finalize() {
  ipc_close(isds_object);
  ipc_close(ihosbd_object);
  ipc_close(iads_object);
  ipc_close(imrs_object);
  ipc_close_domain(vi_domain);
}
