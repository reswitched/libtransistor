#pragma once

char nybble2hex(u8 nybble);
void hexdump(void *rawbuf, size_t size);
void hexnum(int num);
int log_string(char *string, size_t len);

#define STB_SPRINTF_DECORATE(name) dbg_##name
#include "stb_sprintf.h"

#include<stdarg.h>

int dbg_printf(char const *fmt, ...);
int dbg_vprintf(char const *fmt, va_list va);

