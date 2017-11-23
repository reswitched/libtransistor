#include<libtransistor/nx.h>

#include<stdio.h>

int main() {
  // there used to be a really nasty bug in hexdump where it'd segfault if your size wasn't divisible by 0x10
  uint32_t foo[11] = {0, 1, 2, 3, 4, 5, 6, 7, 8, 9, 10};
  hexdump(foo, sizeof(foo));
  return 0;
}
