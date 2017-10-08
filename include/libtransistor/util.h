#pragma once

char nybble2hex(u8 nybble);
void hexdump(void *rawbuf, size_t size);
void hexnum(int num);
int log_string(char *string, size_t len);

void *memset(void *s, int c, size_t n);
void *memcpy(void *dest, const void *src, size_t n);

#define STB_SPRINTF_DECORATE(name) name
#include "stb_sprintf.h"

#include<stdarg.h>

int printf(char const *fmt, ...);
int vprintf(char const *fmt, va_list va);
