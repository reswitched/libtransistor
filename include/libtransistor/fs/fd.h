/**
 * @file libtransistor/fd.h
 * @brief File operations
 *
 *        Operations that can be performed on an open file
 */

#pragma once

#include<libtransistor/types.h>
#include<sys/types.h>
#include<stdatomic.h>

typedef struct trn_file_t trn_file_t;

typedef struct {
	result_t (*lseek)(void *file, off_t *offset, int whence, int *err); ///< Seek the file. offset is both input and output
	result_t (*read)(void *file, void *buf, size_t *nbyte, int *err); ///< Read from the file. nbyte is both input and output
	result_t (*write)(void *file, const void *buf, size_t *nbyte, int *err); ///< Write to the file. nbyte is both input and output
	result_t (*flush)(void *file, int *err); ///< Flush the file
	void (*release)(trn_file_t *file); ///< Release file and any associated structures (including this one)
} trn_file_ops_t;

/**
 * @struct file
 */
typedef struct trn_file_t {
	atomic_int refcount;
	const trn_file_ops_t *ops;
	void *data;
} trn_file_t;

/**
 * @brief Create a file from fops and data
 *
 *        Data will be sent to the various functions in fops. Data will usually 
 *        contain the underlying handle (like the fd for bsd)
 */
int fd_create_file(const trn_file_ops_t *fops, void *data);

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
