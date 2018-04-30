/**
 * @file libtransistor/ipc/twili.h
 * @brief Twili Services
 * See https://github.com/misson20000/twili
 */

#pragma once

#ifdef __cplusplus
extern "C" {
#endif

#include<libtransistor/types.h>
#include<libtransistor/ipc.h>

typedef struct {
	ipc_object_t object;
} twili_pipe_t;

/**
 * @brief Initialize Twili services
 */
result_t twili_init();

/**
 * @brief Open Twili stdin
 */
result_t twili_open_stdin(twili_pipe_t *pipe);

/**
 * @brief Open Twili stdout
 */
result_t twili_open_stdout(twili_pipe_t *pipe);

/**
 * @brief Open Twili stderr
 */
result_t twili_open_stderr(twili_pipe_t *pipe);

/**
 * @brief Read from a Twili pipe
 */
result_t twili_pipe_read(twili_pipe_t *pipe, void *buffer, size_t limit, size_t *bytes_read);

/**
 * @brief Write to a Twili pipe
 * Errors if not all bytes can be written
 */
result_t twili_pipe_write(twili_pipe_t *pipe, const void *buffer, size_t size);

/**
 * @brief Creates a file descriptor for a Twili pipe
 * Copies and takes ownership of pipe
 */
int twili_pipe_fd(twili_pipe_t *pipe);

/**
 * @brief Finalize Twili services
 */
void twili_finalize();

#ifdef __cplusplus
}
#endif
