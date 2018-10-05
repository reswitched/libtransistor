/**
 * @file libtransistor/encoding.h
 * @brief String encoding functions
 * Based on https://github.com/nothings/stb
 */

#pragma once

#ifdef __cplusplus
extern "C" {
#endif

#include<stdint.h>
#include<string.h>

typedef uint16_t trn_char16_t;

/**
 * @brief Converts a UTF-8 string to UTF-16
 * Writes at most n characters to out, returning NULL if there is an error.
 */
trn_char16_t *trn_utf8_to_utf16(trn_char16_t *out, const char *in, size_t n);

/**
 * @brief Converts a UTF-16 string to UTF-8
 * Writes at most n characters to out, returning NULL if there is an error.
 */
char   *trn_utf16_to_utf8(char *out, const trn_char16_t *in, size_t n);

#ifdef __cplusplus
}
#endif
