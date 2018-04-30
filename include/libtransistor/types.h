/**
 * @file libtransistor/types.h
 * @brief Various system types.
 *
 * Based on ctrulib's types.h
 */

#pragma once

#ifdef __cplusplus
extern "C" {
typedef bool _Bool;
#endif

#include <stdint.h>
#include <stdbool.h>
#include <stddef.h>

/// The maximum value of a u64.
#define U64_MAX	UINT64_MAX

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

typedef uint32_t handle_t;            ///< Resource handle
typedef handle_t thread_h;            ///< Thread handle
typedef handle_t shared_memory_h;     ///< Shared Memory handle
typedef handle_t transfer_memory_h;   ///< Transfer Memory handle
typedef handle_t session_h;           ///< Session handle
typedef handle_t port_h;              ///< Port handle
typedef handle_t dev_addr_space_h;    ///< Dev Address Space handle
typedef handle_t process_h;           ///< Process handle
typedef handle_t debug_h;             ///< Debug handle
typedef handle_t revent_h;            ///< revent handle
typedef handle_t wevent_h;            ///< wevent handle
typedef handle_t event_h;             ///< Either revent_h or wevent_h
typedef handle_t resource_limit_h;    ///< Resource limit handle
typedef uint32_t result_t;            ///< Function result
typedef uint64_t aruid_t;             ///< Applet resource user id
typedef void (*thread_entry)(void *); ///< Thread entrypoint function
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
#define INVALID_HANDLE 0xFFFFFFFF

#ifdef __cplusplus
}
#endif
