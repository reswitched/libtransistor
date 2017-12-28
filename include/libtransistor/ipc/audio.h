#pragma once

#include<libtransistor/types.h>
#include<libtransistor/audio.h>

result_t audio_ipc_init();

// IAudioOutManager
result_t audio_ipc_list_outputs(char (*names)[0x20], int max_names, uint32_t *num_names);
result_t audio_ipc_open_output(const char name[0x20], audio_output_t *out);

// IAudioOut
result_t audio_ipc_output_get_state(audio_output_t *out, audio_output_state_t *state);
result_t audio_ipc_output_start(audio_output_t *out);
result_t audio_ipc_output_stop(audio_output_t *out);
result_t audio_ipc_output_register_buffer_event(audio_output_t *out, handle_t *event);
result_t audio_ipc_output_append_buffer(audio_output_t *out, audio_output_buffer_t *buffer);
result_t audio_ipc_output_get_released_buffer(audio_output_t *out, uint32_t *num_released, audio_output_buffer_t **buffer);
result_t audio_ipc_output_contains_buffer(audio_output_t *out, audio_output_buffer_t *buffer, bool *contains); // guessed
void audio_ipc_output_close(audio_output_t *out);

void audio_ipc_finalize();
