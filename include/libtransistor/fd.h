/**
 * @file libtransistor/fd.h
 * @brief File operations
 *
 * File operations
 */

#pragma once

#ifdef __cplusplus
extern "C" {
#endif

#include<libtransistor/types.h>

#include <sys/types.h>
#include <stdint.h>
#include <stdatomic.h>

typedef struct trn_file_t trn_file_t;

/**
 * @struct trn_fops_t
 * File operations
 */
typedef struct {
	result_t (*seek) (void *data, off_t offset, int whence, off_t *out);
	result_t (*read) (void *data, void *buf, size_t size, size_t *bytes_read);
	result_t (*write) (void *data, const void *buf, size_t size, size_t *bytes_written);
	//result_t (*flush) (void *data);
	
	// Release data, and file_operations if it was allocated.
	result_t (*release) (trn_file_t *file);
} trn_file_ops_t;

/**
 * @struct file
 */
struct trn_file_t {
	atomic_int refcount;
	trn_file_ops_t *ops;
	void *data;
};

/**
* @brief Create a file from fops and data
*		
*        Data will be sent to the various functions in fops. Data will usually 
*        contain the underlying handle (like the fd for bsd)
*/
int fd_create_file(trn_file_ops_t *fops, void *data);

/**
* @brief Get the file structure from a given fd, and increment its rc
*		
*        Any call to this function needs an equivalent call to `fd_file_put`.
*/
trn_file_t *fd_file_get(int fd);

/**
* @brief Decrease the fd_file refcount, and release it if this is the last one
*/
void fd_file_put(trn_file_t *file);

/**
* @brief Close the file descriptor
*/
int fd_close(int fd);

// Duplicates oldfd, and all its associated locks, into newfd. Newfd is closed
// if necessary
/**
 * @brief Duplicates oldfd, and all its associated locks, into newfd
 *
 *        Newfd is closed if necessary.
 */
int fd_dup2(int oldfd, int newfd);

#ifdef __cplusplus
}
#endif
