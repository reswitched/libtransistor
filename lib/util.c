#include<libtransistor/types.h>
#include<libtransistor/svc.h>
#include<libtransistor/util.h>

char nybble2hex(u8 nybble) {
  if(nybble < 10) {
    return '0' + nybble;
  } else {
    return 'a' + (nybble - 10);
  }
}

size_t log_length = 0;
char log_buffer[0x10000];

int log_string(char *string, size_t len) {
  svcOutputDebugString(string, len);
  for(int i = 0; i < len; i++) {
    if(string[i] == 0) { break; }
    log_buffer[log_length++] = string[i];
  }
  log_buffer[log_length++] = '\n';
  log_buffer[log_length] = 0;
  return 4;
}

void hexdump(void *rawbuf, size_t size) {
  u8 *buf = rawbuf;
  char line[0x31 + 4 + 0x10 + 1];
  int i = 0;
  int total = 0;
  while(total < size) {
    i = 0;

    int linestart = total;

    // hexdump section
    while(total < linestart + 0x10) {
      if(total < size) {
        u8 byte = buf[total++];
        line[i++] = nybble2hex(byte >> 4);
        line[i++] = nybble2hex(byte & 15);
        line[i++] = ' ';
      } else {
        line[i++] = ' ';
        line[i++] = ' ';
        line[i++] = ' ';
      }
      if(i == 3*8) { line[i++] = ' '; }
    }

    line[i++] = ' ';
    line[i++] = '|';
    line[i++] = ' ';
    line[i++] = ' ';

    total = linestart;
    
    while(total < linestart + 0x10) {
      if(total < size) {
        u8 ch = buf[total++];
        if(ch >= ' ' && ch < 0x7F) {
          line[i++] = ch;
        } else {
          line[i++] = '.';
        }
      } else {
        line[i++] = ' ';
      }
    }

    line[i++] = 0;

    log_string(line, sizeof(line));
  }
}

void hexnum(int num) {
  char buf[16];
  buf[15] = 0;
  int i = 14;
  for(; num; i--, num>>= 4) {
    buf[i] = nybble2hex(num & 0xF);
  }
  buf[i--] = 'x';
  buf[i--] = '0';
  log_string(buf + i + 1, 16 - i);
}

#define STB_SPRINTF_IMPLEMENTATION
#include<libtransistor/stb_sprintf.h>

#include<stdarg.h>

int dbg_printf(char const *fmt, ...) {
  va_list vl;
  char buf[512];
  int ret;
  va_start(vl, fmt);
  ret = dbg_vsnprintf(buf, 511, fmt, vl);
  log_string(buf, ret+1);
  va_end(vl);
  return ret;
}
