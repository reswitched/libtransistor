/**
 * @file libtransistor/tls.h
 * @brief Thread Local Storage functions
 */

#pragma once

#ifdef __cplusplus
extern "C" {
#endif

#include<libtransistor/types.h>
#include<libtransistor/thread.h>

#include<reent.h>
#include<stdint.h>

struct tls {
	uint8_t ipc_buffer[0x100];
	uint8_t _unk1[0xF8];
	trn_thread_t *thread;
};

/**
 * @brief Gets the address of the thread-local storage
 */
struct tls *get_tls();

/**
 * @brief Gets the current thread struct
 */
trn_thread_t *trn_get_thread();

/**
 * @brief Gets the current thread's handle
 */
thread_h get_thread_handle();

#ifdef __cplusplus
}
#endif
