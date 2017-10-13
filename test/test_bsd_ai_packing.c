#include<libtransistor/nx.h>

#include<sys/socket.h>
#include<string.h>

int main() {
  result_t r;

  char ip_addr[4] = {10, 0, 0, 192};
  
  struct sockaddr_in sa;
  sa.sin_family = AF_INET;
  sa.sin_port = htons(6767);
  sa.sin_addr.s_addr = *(uint32_t*) ip_addr;
  
  struct addrinfo ai_udp;
  struct addrinfo ai_tcp;
  
  ai_udp.ai_flags = 0;
  ai_udp.ai_family = AF_INET;
  ai_udp.ai_socktype = SOCK_DGRAM;
  ai_udp.ai_protocol = IPPROTO_UDP;
  ai_udp.ai_addrlen = sizeof(sa);
  ai_udp.ai_addr = (struct sockaddr*) &sa;
  ai_udp.ai_canonname = NULL;
  ai_udp.ai_next = &ai_tcp;

  ai_tcp.ai_flags = 0;
  ai_tcp.ai_family = AF_INET;
  ai_tcp.ai_socktype = SOCK_STREAM;
  ai_tcp.ai_protocol = IPPROTO_TCP;
  ai_tcp.ai_addrlen = sizeof(sa);
  ai_tcp.ai_addr = (struct sockaddr*) &sa;
  ai_tcp.ai_canonname = NULL;
  ai_tcp.ai_next = NULL;

  uint8_t buf[0x400];
  r = bsd_ai_pack(&ai_udp, buf, sizeof(buf));
  if(r) {
    dbg_printf("failed to pack addrinfo: 0x%x", r);
    return 1;
  }

  uint8_t template[] = {
    0xbe, 0xef, 0xca, 0xfe, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x02, 0x00, 0x00, 0x00, 0x02,
    0x00, 0x00, 0x00, 0x11, 0x00, 0x00, 0x00, 0x10, 0x00, 0x02, 0x6f, 0x1a, 0xc0, 0x00, 0x00, 0x0a,
    0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0xbe, 0xef, 0xca, 0xfe, 0x00, 0x00, 0x00,
    0x00, 0x00, 0x00, 0x00, 0x02, 0x00, 0x00, 0x00, 0x01, 0x00, 0x00, 0x00, 0x06, 0x00, 0x00, 0x00,
    0x10, 0x00, 0x02, 0x6f, 0x1a, 0xc0, 0x00, 0x00, 0x0a, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
    0x00, 0x00
  };
  
  for(int i = 0; i < sizeof(template); i++) {
    if(buf[i] != template[i]) {
      dbg_printf("packing mismatch at +0x%x", i);
      hexdump(buf, 0x50);
      return 1;
    }
  }

  dbg_printf("bsd addrinfo packing test passed");

  struct addrinfo *out;
  r = bsd_ai_unpack(&out, template, sizeof(template));
  if(r) {
    dbg_printf("failed to unpack addrinfo: 0x%x", r);
    return 1;
  }

  if(!(memcmp(out, &ai_udp, sizeof(struct addrinfo) - sizeof(ai_udp.ai_next)))) {
    dbg_printf("ai_udp does not match");
    return 1;
  }

  if(out->ai_next == NULL) {
    dbg_printf("only unpacked one addrinfo struct");
    return 1;
  }
  
  if(!(memcmp(out->ai_next, &ai_tcp, sizeof(struct addrinfo)))) {
    dbg_printf("ai_tcp does not match");
    return 1;
  }

  bsd_freeaddrinfo(out);
  
  dbg_printf("bsd addrinfo unpacking test passed");
  return 0;
}
