#include<libtransistor/nx.h>

int foo = 88;

int calc() {
  return foo;
}

int main() {
  for(int i = 0; i < 10; i++) {
    if(sm_init() != RESULT_OK) {
      if(i == 9) {
        printf("failed to init sm");
        return 1;
      }
    } else {
      break;
    }
  }

  result_t r;
  if((r = bsd_init()) != RESULT_OK) {
    printf("failed to init bsd: 0x%x", r);
    sm_finalize();
    return 1;
  }

  int fd = bsd_socket(2, 1, 6); // AF_INET, SOCK_STREAM, PROTO_TCP
  if(fd < 0) {
    printf("failed to create socket: 0x%x, %d", bsd_result, bsd_errno);
  }

  printf("got socket %d", fd);
  
  bsd_finalize();
  sm_finalize();
  return 0;
}
