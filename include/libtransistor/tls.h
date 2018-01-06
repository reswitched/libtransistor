/**
 * @file libtransistor/tls.h
 * @brief Thread Local Storage functions
 */

#pragma once

#include <reent.h>

struct thread_ctx {
	struct _reent reent;
	void *pthread; // Pointer to pthread internal structure
};

struct tls {
	char ipc_buffer[0x100];
	char _unk1[0xF8];
	struct thread_ctx *ctx;
};

/**
 * @brief Gets the address of the thread-local storage
 */
struct tls *get_tls();
