/**
 * @file libtransistor/ipc/audio.h
 * @brief Audio output
 */

#pragma once

#ifdef __cplusplus
extern "C" {
#endif

#include<libtransistor/types.h>
#include<libtransistor/audio.h>
/**
* @brief Initialize Audio
*/
result_t audio_ipc_init();


/**
* @brief Lists the audio outputs
*
* @param names Array of audio output names
* @param max_names Maximum number of names that will fit in the array
* @param num_names Actual number of names returned
*/
result_t audio_ipc_list_outputs(char (*names)[0x20], int max_names, uint32_t *num_names);

/**
* @brief Opens an audio output
*
* @param name Name of the output (from \ref audio_ipc_list_outputs)
* @param out Output structure to initialize
*/
result_t audio_ipc_open_output(const char name[0x20], audio_output_t *out);

/**
* @brief Get the current state of the audio output
*
* @param out Audio output to query
* @param state Returned state
*/
result_t audio_ipc_output_get_state(audio_output_t *out, audio_output_state_t *state);

/**
* @brief Start audio output
*
* @param out Audio output to start
*/
result_t audio_ipc_output_start(audio_output_t *out);

/**
* @brief Stop audio output
*
* @param out Audio output to stop
*/
result_t audio_ipc_output_stop(audio_output_t *out);

/**
* @brief Get buffer-release event
*
* @param out Audio output
* @param event Acquired event
*
* This event is signalled whenever an audio buffer is released.
*/
result_t audio_ipc_output_register_buffer_event(audio_output_t *out, handle_t *event);

/**
* @brief audio_ipc_output_append_buffer
*
* @param out Audio output to append buffer to
* @param buffer Audio buffer to append
*/
result_t audio_ipc_output_append_buffer(audio_output_t *out, audio_output_buffer_t *buffer);

/**
* @brief audio_ipc_output_get_released_buffer
*
* @param out Audio output to query
* @param num_released Number of released buffers
* @param buffer Pointer to released buffer
*/
result_t audio_ipc_output_get_released_buffer(audio_output_t *out, uint32_t *num_released, audio_output_buffer_t **buffer);

/**
* @brief audio_ipc_output_contains_buffer
*
* @param out Audio output to query
* @param buffer Buffer to query
* @param contains Whether or not the buffer has been appended
*/
result_t audio_ipc_output_contains_buffer(audio_output_t *out, audio_output_buffer_t *buffer, bool *contains); // guessed

/**
* @brief Closes the audio output
*
* @param out Audio output to query
*/
void audio_ipc_output_close(audio_output_t *out);

/**
* @brief Finalize audio
*/
void audio_ipc_finalize();

#ifdef __cplusplus
}
#endif
