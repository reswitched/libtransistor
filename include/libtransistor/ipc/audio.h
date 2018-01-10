/**
 * @file libtransistor/ipc/audio.h
 * @brief Audio output
 */

#pragma once

#include<libtransistor/types.h>
#include<libtransistor/audio.h>
/**
* @brief Initialize Audio
*/
result_t audio_ipc_init();


/**
* @brief Lists the audio outputs
*
* @param names Description here...
* @param max_names Description here...
* @param num_names Description here...
*/
result_t audio_ipc_list_outputs(char (*names)[0x20], int max_names, uint32_t *num_names);

/**
* @brief Opens audio output
*
* @param name Description here...
* @param out Description here...
*/
result_t audio_ipc_open_output(const char name[0x20], audio_output_t *out);

/**
* @brief Get the current state of the audio output
*
* @param out Description here...
* @param state Description here...
*/
result_t audio_ipc_output_get_state(audio_output_t *out, audio_output_state_t *state);

/**
* @brief Start audio output
*
* @param out Description here...
*/
result_t audio_ipc_output_start(audio_output_t *out);

/**
* @brief Stop audio output
*
* @param out Description here...
*/
result_t audio_ipc_output_stop(audio_output_t *out);

/**
* @brief audio_ipc_output_register_buffer_event
*
* @param out Description here...
* @param event Description here...
*/
result_t audio_ipc_output_register_buffer_event(audio_output_t *out, handle_t *event);

/**
* @brief audio_ipc_output_append_buffer
*
* @param out Description here...
* @param buffer Description here...
*/
result_t audio_ipc_output_append_buffer(audio_output_t *out, audio_output_buffer_t *buffer);

/**
* @brief audio_ipc_output_get_released_buffer
*
* @param out Description here...
* @param num_released Description here...
* @param buffer Description here...
*/
result_t audio_ipc_output_get_released_buffer(audio_output_t *out, uint32_t *num_released, audio_output_buffer_t **buffer);

/**
* @brief audio_ipc_output_contains_buffer
*
* @param out Description here...
* @param buffer Description here...
* @param contains Description here...
*/
result_t audio_ipc_output_contains_buffer(audio_output_t *out, audio_output_buffer_t *buffer, bool *contains); // guessed

/**
* @brief Closes the audio output
*
* @param out Description here...
*/
void audio_ipc_output_close(audio_output_t *out);

/**
* @brief Finalize audio
*/
void audio_ipc_finalize();
