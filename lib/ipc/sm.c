#include<libtransistor/types.h>
#include<libtransistor/svc.h>
#include<libtransistor/ipc.h>
#include<libtransistor/err.h>
#include<libtransistor/util.h>
#include<libtransistor/ipc/sm.h>

#include<string.h>

static ipc_object_t sm_object;

static u64 str2u64(char *str) {
  char buf[8];
  int i = 0;
  for(; i < 8; i++) {
    if(str[i] == 0) { break; }
    buf[i] = str[i];
  }
  for(; i < 8; i++) {
    buf[i] = 0;
  }
  return *(u64*) buf;
}

result_t sm_init() {
  dbg_printf("initializing sm");
  sm_object.object_id = -1;
  return svcConnectToNamedPort(&(sm_object.session), "sm:");
}

void sm_finalize() {
  ipc_close(sm_object);
}

result_t sm_get_service(ipc_object_t *out_object, char *name) {
  if(!sm_object.session) {
    return LIBTRANSISTOR_ERR_SM_NOT_INITIALIZED;
  }
  
  u64 service_name = str2u64(name);
  int i;
  
  if(strlen(name) > 8) {
    return LIBTRANSISTOR_ERR_SM_SERVICE_NAME_TOO_LONG;
  }

  out_object->object_id = -1;
  
  ipc_request_t rq = ipc_default_request;
  rq.request_id = 1;
  rq.raw_data = (u32*) &service_name;
  rq.raw_data_size = sizeof(service_name);

  ipc_response_fmt_t rs = ipc_default_response_fmt;
  rs.num_move_handles = 1;
  rs.move_handles = &(out_object->session);

  return ipc_send(sm_object, &rq, &rs);
}
