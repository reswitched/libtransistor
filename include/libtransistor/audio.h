/**
 * @file libtransistor/audio.h
 * @brief Audio data structures
 */

#pragma once

#include<libtransistor/types.h>
#include<libtransistor/ipc.h>

typedef enum {
	PCM_INT16 = 2,
} sample_format_t;

typedef enum {
	PLAYING = 0,
	STOPPED = 1,
} audio_output_state_t;

typedef struct {
	ipc_object_t object;
	uint32_t num_channels;
	uint32_t sample_rate;
	sample_format_t sample_format;
} audio_output_t;

// this struct is sent over IPC and must look exactly like this
typedef struct {
	void *ptr;
	void *sample_data;
	uint64_t buffer_size;
	uint64_t data_size;
	uint64_t unknown;
} audio_output_buffer_t;
