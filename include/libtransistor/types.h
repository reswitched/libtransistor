/**
 * @file types.h
 * @brief Various system types.
 */

// Based on ctrulib's types.h

#pragma once

#include <stdint.h>
#include <stdbool.h>
#include <stddef.h>

/// The maximum value of a u64.
#define U64_MAX	UINT64_MAX

/// would be nice if newlib had this already
#ifndef SSIZE_MAX
#ifdef SIZE_MAX
#define SSIZE_MAX ((SIZE_MAX) >> 1)
#endif
#endif

typedef volatile uint8_t vu8;   ///<  8-bit volatile unsigned integer.
typedef volatile uint16_t vu16; ///< 16-bit volatile unsigned integer.
typedef volatile uint32_t vu32; ///< 32-bit volatile unsigned integer.
typedef volatile uint64_t vu64; ///< 64-bit volatile unsigned integer.

typedef volatile int8_t vs8;   ///<  8-bit volatile signed integer.
typedef volatile int16_t vs16; ///< 16-bit volatile signed integer.
typedef volatile int32_t vs32; ///< 32-bit volatile signed integer.
typedef volatile int64_t vs64; ///< 64-bit volatile signed integer.

typedef uint32_t handle_t;                 ///< Resource handle.
typedef handle_t thread_h;
typedef handle_t shared_memory_h;
typedef handle_t transfer_memory_h;
typedef handle_t session_h;
typedef handle_t port_h;
typedef handle_t dev_addr_space_h;
typedef handle_t process_h;
typedef handle_t debug_h;
typedef uint32_t result_t;                 ///< Function result.
typedef void (*thread_entry)(void *); ///< Thread entrypoint function.
typedef void (*voidfn)(void);

/// Creates a bitmask from a bit number.
#define BIT(n) (1U<<(n))

/// Aligns a struct (and other types?) to m, making sure that the size of the struct is a multiple of m.
#define ALIGN(m)   __attribute__((aligned(m)))
/// Packs a struct (and other types?) so it won't include padding bytes.
#define PACKED     __attribute__((packed))

#ifndef LIBTRANSISTOR
/// Flags a function as deprecated.
#define DEPRECATED __attribute__ ((deprecated))
#else
/// Flags a function as deprecated.
#define DEPRECATED
#endif

#define RESULT_OK 0
