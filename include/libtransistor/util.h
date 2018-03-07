/**
 * @file libtransistor/util.h
 * @brief Various utililty functions
 */

#pragma once

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
 * @brief Hexdump a buffer
 *
 * @param rawbuf The buffer you want to dump
 * @param size The size of the buffer
 *
 * Hexdump is written to standard output.
 */
void hexdump(const void *rawbuf, size_t size);

/**
 * @brief Hexdump a buffer using the debug logger
 *
 * @param rawbuf The buffer you want to dump
 * @param size The size of the buffer
 *
 * Hexdump is written over the basic debug logger.
 */
void hexdump_dbg(const void *rawbuf, size_t size);

/**
 * @brief Convert an int number to hex and prints it to stdout
 *
 * @param num The int that you want converted
 */
void hexnum(int num);

/**
 * @brief Log a string to the debug log
 *
 * @param string The string to log
 * @param len Length of the string
 *
 * The debug log does not depend on newlib or malloc, and is therefore safe
 * to use in environments such as the memory allocation code or threads that
 * do not have context properly set up.
 *
 */
int log_string(const char *string, size_t len);

/**
 * @brief Connect the debug log over a socket
 *
 * @param host Host to connect to
 * @param port Port to connect to
 */
result_t dbg_connect(const char *host, const char *port);

/**
 * @brief Disconnect the debug log from the socket
 */
void dbg_disconnect();

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
