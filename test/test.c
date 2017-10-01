#include<libtransistor/nx.h>

int foo = 88;

int calc() {
  return foo;
}

int main() {
  log_string("Hello from log_string! This was linked with lld!", 0x200);
  return 2;
  printf("Hello from printf!");
  return 2;

  if(sm_init()) {
    printf("failed to init sm");
    svcExitThread();
  }

  session_h service;
  if(sm_get_service(&service, "bsd:u")) {
    printf("failed to get service");
    svcExitThread();
  }
    
  printf("got back handle 0x%x", service);
  svcExitThread();
}
