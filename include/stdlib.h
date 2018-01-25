#ifndef _LIBTRANSISTOR_STDLIB_H_
#define _LIBTRANSISTOR_STDLIB_H_

#ifdef __cplusplus
extern "C" {
#endif

#include_next <stdlib.h>
#include <locale.h>

long double strtold (const char *__restrict, char **__restrict);
long double strtold_l (const char *__restrict, char **__restrict, locale_t);

#ifdef __cplusplus
} // extern "C"
#endif

#endif
