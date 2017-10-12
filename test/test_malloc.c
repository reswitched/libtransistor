#include<libtransistor/nx.h>
#include<malloc.h>

int main() {
  svcSleepThread(100000000);

  void *buf = malloc(4);

  dbg_printf("malloc returned %p", buf);

  if(buf == NULL) {
    return 1;
  }
  
  return 0;
}
