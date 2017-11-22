#include<libtransistor/nx.h>

#include<string.h>

int main(int argc, char **argv) {
  dbg_printf("argc: %d", argc);
  dbg_printf("argv: %p", argv);
  for(int i = 0; i < argc; i++) {
    dbg_printf("  argv[%d] = %s", i, argv[i]);
  }
  
  if(argc != 1) {
    return 1;
  }
  
  if(strcmp("testarg", argv[0]) != 0) {
    return 1;
  }
  
  dbg_printf("argument test passed");
  return 0;
}
