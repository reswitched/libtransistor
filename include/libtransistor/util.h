/**
 * @file libtransistor/util.h
 * @brief Various utililty functions
 */

#pragma once

#include <libtransistor/err.h>

#define ARRAY_LENGTH(x) (sizeof(x) / sizeof((x)[0]))


/**
 * @brief Finds an empty memory block
 *
 * @param len The length of the empty memory block you want to find.
 */
void *find_empty_memory_block(size_t len);

/**
 * @brief Converts a string to a u64
 *
 * @param str String to convert to u64
 */
uint64_t str2u64(const char *str);

/**
 * @brief Convert a uint8 nybble to a hex char
 *
 * @param nybble The uint8 that you want converted
 */
char nybble2hex(uint8_t nybble);

/**
 * @brief Convert a uint8 nybble to a hex char
 *
 * @param rawbuf The buffer you want to dump
 * @param size The size of the buffer
 *
 * Hexdump is written to standard output.
 */
void hexdump(const void *rawbuf, size_t size);

/**
 * @brief Convert an int number to hex and prints it to stdout
 *
 * @param num The int that you want converted
 */
void hexnum(int num);

/**
 * @brief Log a string to the bss log
 *
 * @param string The string to log
 * @param len Length of the string
 */
int log_string(const char *string, size_t len);

/**
 * @brief Turns a libtransistor result_t into a POSIX errno. The POSIX errno
 * will be positive. You might want to negate it before returning!
 *
 * @param r The libtransistor result to transform
 */
int trn_result_to_errno(result_t r);

// TODO: A perror for result_t.

#define STB_SPRINTF_DECORATE(name) dbg_##name
#include "stb_sprintf.h"

#include<stdarg.h>

int dbg_printf(char const *fmt, ...);
int dbg_vprintf(char const *fmt, va_list va);
void dbg_set_bsd_log(int fd);
