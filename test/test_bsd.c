#include<libtransistor/nx.h>

#include<sys/socket.h>
#include<stdio.h>

int main() {
  svcSleepThread(100000000);
  
  result_t r;
  if((r = sm_init()) != RESULT_OK) {
    printf("failed to init sm: 0x%x\n", r);
    return 1;
  }

  if((r = bsd_init()) != RESULT_OK) {
    printf("failed to init bsd: 0x%x, %d\n", r, bsd_errno);
    goto err_only_sm;
  }

  char bind_ip_addr[4] = {0, 0, 0, 0};
  char server_ip_addr[4] = {127, 0, 0, 1};
  
  struct sockaddr_in bind_addr = {
    .sin_family = AF_INET,
    .sin_port = htons(4444),
    .sin_addr = {
      .s_addr = *(uint32_t*) bind_ip_addr
    }
  };

  struct sockaddr_in server_addr = {
    .sin_family = AF_INET,
    .sin_port = htons(5555),
    .sin_addr = {
      .s_addr = *(uint32_t*) server_ip_addr
    }
  };  

  // client socket test
  // socket, connect, sendto, recv, close
  int cfd = bsd_socket(2, 1, 6); // AF_INET, SOCK_STREAM, PROTO_TCP
  if(cfd < 0) {
    printf("failed to create socket: 0x%x, %d\n", bsd_result, bsd_errno);
    goto err;
  }

  printf("made client socket %d\n", cfd);
  
  if(bsd_connect(cfd, (struct sockaddr*) &server_addr, sizeof(server_addr)) < 0) {
    printf("failed to connect socket: 0x%x, %d\n", bsd_result, bsd_errno);
    goto err;
  }

  char hello[] = "Hello from libtransistor over a socket!";  
  if(bsd_sendto(cfd, hello, sizeof(hello), 0, (struct sockaddr*) &server_addr, sizeof(server_addr)) < 0) {
    printf("failed to sendto: 0x%x, %d\n", bsd_result, bsd_errno);
    goto err;
  }

  int num_bytes;
  char response[512];
  char expected_response[] = "testing recv...";
  if((num_bytes = bsd_recv(cfd, response, sizeof(response), 0)) < 0) {
    printf("failed to recv: 0x%x, %d\n", bsd_result, bsd_errno);
    goto err;
  }
  response[num_bytes] = 0;
  if(num_bytes != sizeof(expected_response)) {
    printf("got back wrong response: %s\n", response);
    goto err;
  }
  for(int i = 0; i < num_bytes; i++) {
    if(response[i] != expected_response[i]) {
      printf("got back wrong response: %s\n", response);
      goto err;
    }
  }
  
  // server socket test
  // socket, bind, listen, accept, send, recv, close
  int sfd = bsd_socket(2, 1, 6); // AF_INET, SOCK_STREAM, PROTO_TCP
  if(sfd < 0) {
    printf("failed to create socket: 0x%x, %d\n", bsd_result, bsd_errno);
    goto err;
  }
  
  if(bsd_bind(sfd, (struct sockaddr*) &bind_addr, sizeof(bind_addr)) < 0) {
    printf("failed to bind socket: 0x%x, %d\n", bsd_result, bsd_errno);
    goto err;
  }

  if(bsd_listen(sfd, 20) != 0) {
    printf("failed to listen on socket: 0x%x, %d\n", bsd_result, bsd_errno);
    goto err;
  }

  // don't close client test's socket until we're all set up.
  // closing the client test's socket signals to the test helper
  // that we're listening.
  if(bsd_close(cfd) < 0) {
    printf("failed to close: 0x%x, %d\n", bsd_result, bsd_errno);
    goto err;
  }
  
  struct sockaddr_in remote_addr;
  socklen_t remote_addr_len = sizeof(remote_addr);
  
  int rfd;
  if((rfd = bsd_accept(sfd, (struct sockaddr*) &remote_addr, &remote_addr_len)) < 0) {
    printf("failed to accept: 0x%x, %d\n", bsd_result, bsd_errno);
    goto err;
  }
  
  if(bsd_send(rfd, hello, sizeof(hello), 0) < 0) {
    printf("failed to send: 0x%x, %d\n", bsd_result, bsd_errno);
    goto err;
  }

  if((num_bytes = bsd_recv(rfd, response, sizeof(response), 0)) < 0) {
    printf("failed to recv: 0x%x, %d\n", bsd_result, bsd_errno);
    goto err;
  }
  response[num_bytes] = 0;
  if(num_bytes != sizeof(expected_response)) {
    printf("got back wrong response: %s\n", response);
    goto err;
  }
  for(int i = 0; i < num_bytes; i++) {
    if(response[i] != expected_response[i]) {
      printf("got back wrong response: %s\n", response);
      goto err;
    }
  }

  if(bsd_close(rfd) < 0) {
    printf("failed to close: 0x%x, %d\n", bsd_result, bsd_errno);
    goto err;
  }
  
  if(bsd_close(sfd) < 0) {
    printf("failed to close: 0x%x, %d\n", bsd_result, bsd_errno);
    goto err;
  }
  
  bsd_finalize();
  sm_finalize();
  printf("bsd tests passed.\n");
  return 0;

 err:
  bsd_finalize();
 err_only_sm:
  sm_finalize();
  return 1;  
}
