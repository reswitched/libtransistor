#include<libtransistor/types.h>
#include<libtransistor/svc.h>
#include<libtransistor/ipc.h>
#include<libtransistor/err.h>
#include<libtransistor/util.h>
#include<libtransistor/ipc/sm.h>

static session_h sm_session = 0;

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
  printf("initializing sm");
  return svcConnectToNamedPort(&sm_session, "sm:");
}

void sm_finalize() {
  svcCloseHandle(sm_session);
}

result_t sm_get_service(session_h *session, char *name) {
  if(!sm_session) {
    return LIBTRANSISTOR_ERR_SM_NOT_INITIALIZED;
  }
  
  u64 service_name = str2u64(name);
  int i;
  for(i = 0; i < 9; i++) {
    if(name[i] == 0) { break; }
  }
  
  if(i >= 8) {
    return LIBTRANSISTOR_ERR_SM_SERVICE_NAME_TOO_LONG;
  }
  
  ipc_request_t rq = ipc_default_request;
  rq.request_id = 1;
  rq.raw_data = (u32*) &service_name;
  rq.raw_data_size = 2;

  ipc_response_fmt_t rs = ipc_default_response_fmt;
  rs.num_move_handles = 1;
  rs.move_handles = session;

  printf("sending to 0x%x", sm_session);
  return ipc_send(sm_session, &rq, &rs);
}
