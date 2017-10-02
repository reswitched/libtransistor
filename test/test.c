#include<libtransistor/nx.h>

int foo = 88;

int calc() {
  return foo;
}

int main() {
  result_t r;
  
  svcSleepThread(100000000);
  if((r = sm_init()) != RESULT_OK) {
    printf("failed to init sm: 0x%x", r);
    return 1;
  }

  if((r = bsd_init()) != RESULT_OK) {
    printf("failed to init bsd: 0x%x, %d", r, bsd_errno);
    sm_finalize();
    return 1;
  }

  int fd = bsd_socket(2, 1, 6); // AF_INET, SOCK_STREAM, PROTO_TCP
  if(fd < 0) {
    printf("failed to create socket: 0x%x, %d", bsd_result, bsd_errno);
    bsd_finalize();
    sm_finalize();
    return 1;
  }

  printf("got socket %d", fd);

  char ip_addr[4] = {10, 0, 0, 192};
  
  struct sockaddr_in addr = {
    .sin_family = 0x0200, // AF_INET
    .sin_port = 0x5c11, // 4444 in big endian
    .sin_addr = {
      .s_addr = *(uint32_t*) ip_addr
    }
  };
  
  if(bsd_connect(fd, (struct sockaddr*) &addr, sizeof(addr)) < 0) {
    printf("failed to connect socket: 0x%x, %d", bsd_result, bsd_errno);
    bsd_finalize();
    sm_finalize();
    return 1;
  }

  char hello[] = "Hello from libtransistor over a socket!";
  
  if(bsd_send(fd, hello, sizeof(hello)) < 0) {
    printf("failed to send: 0x%x, %d", bsd_result, bsd_errno);
    bsd_finalize();
    sm_finalize();
    return 1;
  }
  
  bsd_finalize();
  sm_finalize();
  return 0;
}
