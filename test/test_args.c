#include<libtransistor/nx.h>

#include<string.h>
#include<stdio.h>

int main(int argc, char **argv) {
  printf("argc: %d\n", argc);
  printf("argv: %p\n", argv);
  for(int i = 0; i < argc; i++) {
    printf("  argv[%d] = %s\n", i, argv[i]);
  }
  
  if(argc != 1) {
    return 1;
  }
  
  if(strcmp("testarg", argv[0]) != 0) {
    return 1;
  }
  
  printf("argument test passed\n");
  return 0;
}
