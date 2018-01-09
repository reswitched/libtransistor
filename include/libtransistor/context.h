/**
 * @file libtransistor/context.h
 * @brief Represents resources, arguments, and values to be passed between this program and PegaSwitch or another NRO loader
 */

#pragma once

#include<libtransistor/types.h>
#include<libtransistor/ipc.h>
#include<libtransistor/ipc/bsd.h>

#define LIBTRANSISTOR_CONTEXT_MAGIC 0x007874635f656361
#define LIBTRANSISTOR_CONTEXT_VERSION 3

/// @brief Return Flag: Do not unload NRO from memory
#define RETF_KEEP_LOADED	1

/// @brief Return Flag: Show memory map after cleanup
#define RETF_RUN_MEMINFO	2

/// @brief Return Flag: Close the browser after this NRO exits (PegaSwitch loader only)
#define RETF_CLOSE_BROWSER	4

/**
 * @brief Add description here
 */
typedef struct {
	uint64_t magic;
	uint64_t version;
	size_t size; /// size of this struct (additional verification)

	// version 1
	char *log_buffer; /// out
	size_t *log_length; /// out
  
	char **argv; /// in
	uint64_t argc; /// in
  
	void *mem_base; /// in, usable contiguous block of free memory
	uint64_t mem_size; /// in, ^ size
  
	bool has_bsd; /// in
	ipc_object_t bsd_object; /// in, bsd object
	int std_socket; /// in, stdout socket from loader
  
	bool has_ro; /// in
	ipc_object_t ro_object; /// in, ldr:ro object

	uint32_t workstation_addr; /// in
  
	uint64_t return_flags; /// out

	thread_h main_thread; /// in, handle to main thread.
} libtransistor_context_t;

extern libtransistor_context_t libtransistor_context;

void libtransistor_set_keep_loaded();
void libtransistor_set_run_meminfo();
void libtransistor_set_close_browser();
