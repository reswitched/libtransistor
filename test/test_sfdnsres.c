#include<libtransistor/nx.h>

#include<sys/socket.h>

void dumpsockaddrin(struct sockaddr_in *sin) {
  dbg_printf("sin_family: %d", sin->sin_family);
  dbg_printf("sin_port: %d", ntohs(sin->sin_port));
  uint32_t addr = sin->sin_addr.s_addr;
  uint8_t *bytes = (uint8_t*) &addr;
  dbg_printf("sin_addr: %d.%d.%d.%d", bytes[0], bytes[1], bytes[2], bytes[3]);
}

void dumpaddrinfo(struct addrinfo *ai) {
  dbg_printf("ai_flags: %d", ai->ai_flags);
  dbg_printf("ai_family: %d", ai->ai_family);
  dbg_printf("ai_socktype: %d", ai->ai_socktype);
  dbg_printf("ai_protocol: %d", ai->ai_protocol);
  dbg_printf("ai_addrlen: %d", ai->ai_addrlen);
  if(ai->ai_family == AF_INET) {
    dumpsockaddrin((struct sockaddr_in*) ai->ai_addr);
  }
  if(ai->ai_canonname) {
    dbg_printf("ai_canonname: \"%s\"", ai->ai_canonname);
  } else {
    dbg_printf("ai_canonname: NULL");
  }
  if(ai->ai_next) {
    dbg_printf("ai_next:");
    dumpaddrinfo(ai->ai_next);
  }
}

int main() {
  svcSleepThread(100000000);
  
  result_t r;
  if((r = sm_init()) != RESULT_OK) {
    dbg_printf("failed to init sm: 0x%x", r);
    return 1;
  }

  if((r = bsd_init()) != RESULT_OK) {
    dbg_printf("failed to init bsd: 0x%x, %d", r, bsd_errno);
    goto err_only_sm;
  }

  struct addrinfo *ai = NULL;

  struct addrinfo hints;
  hints.ai_family = AF_INET;
  hints.ai_socktype = SOCK_STREAM;
  
  int e = bsd_getaddrinfo("conntest.nintendowifi.net", "6767", &hints, &ai);
  if(e) {
    dbg_printf("failed to getaddrinfo: %d, 0x%x", e, bsd_result);
    goto err;
  }

  if(ai == NULL) {
    dbg_printf("addrinfo is null?");
    goto err;
  }
  
  dumpaddrinfo(ai);

  bsd_finalize();
  sm_finalize();
  return 0;
  
 err:
  bsd_finalize();
 err_only_sm:
  sm_finalize();
  return 1;  

}
