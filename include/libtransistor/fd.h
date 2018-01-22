/**
 * @file libtransistor/fd.h
 * @brief File operations
 *
 *        Taken straight from the linux kernel
 */

#pragma once

#include <sys/types.h>
#include <stdint.h>
#include <stdatomic.h>

struct file;

/**
* @struct file_operations
*/
struct file_operations {
	off_t (*llseek) (void *, off_t, int);
	ssize_t (*read) (void *, char *, size_t);
	ssize_t (*write) (void *, const char *, size_t);
	/*ssize_t (*read_iter) (struct kiocb *, struct iov_iter *);
	ssize_t (*write_iter) (struct kiocb *, struct iov_iter *);
	int (*iterate) (struct file *, struct dir_context *);
	int (*iterate_shared) (struct file *, struct dir_context *);
	unsigned int (*poll) (struct file *, struct poll_table_struct *);
	long (*unlocked_ioctl) (struct file *, unsigned int, unsigned long);
	long (*compat_ioctl) (struct file *, unsigned int, unsigned long);
	int (*mmap) (struct file *, struct vm_area_struct *);
	int (*open) (struct inode *, struct file *);*/
	int (*flush) (void *);
	// Release data, and file_operations if it was allocated.
	int (*release) (struct file *f);
	/*int (*fsync) (struct file *, loff_t, loff_t, int datasync);
	int (*fasync) (int, struct file *, int);
	int (*lock) (struct file *, int, struct file_lock *);
	ssize_t (*sendpage) (struct file *, struct page *, int, size_t, loff_t *, int);
	unsigned long (*get_unmapped_area)(struct file *, unsigned long, unsigned long, unsigned long, unsigned long);
	int (*check_flags)(int);
	int (*flock) (struct file *, int, struct file_lock *);
	ssize_t (*splice_write)(struct pipe_inode_info *, struct file *, loff_t *, size_t, unsigned int);
	ssize_t (*splice_read)(struct file *, loff_t *, struct pipe_inode_info *, size_t, unsigned int);
	int (*setlease)(struct file *, long, struct file_lock **, void **);
	long (*fallocate)(struct file *file, int mode, loff_t offset,
			  loff_t len);
	void (*show_fdinfo)(struct seq_file *m, struct file *f);
#ifndef CONFIG_MMU
	unsigned (*mmap_capabilities)(struct file *);
#endif
	ssize_t (*copy_file_range)(struct file *, loff_t, struct file *,
			loff_t, size_t, unsigned int);
	int (*clone_file_range)(struct file *, loff_t, struct file *, loff_t,
			uint64_t);
	ssize_t (*dedupe_file_range)(struct file *, uint64_t, uint64_t, struct file *,
			uint64_t);*/
};

/**
* @struct file
*/
struct file {
	atomic_int refcount;
	struct file_operations *ops;
	void *data;
};

/**
* @brief Create a file from fops and data
*		
*        Data will be sent to the various functions in fops. Data will usually 
*        contain the underlying handle (like the fd for bsd)
*/
int fd_create_file(struct file_operations *fops, void *data);

/**
* @brief Get the file structure from a given fd, and increment its rc
*		
*        Any call to this function needs an equivalent call to `fd_file_put`.
*/
struct file *fd_file_get(int fd);

/**
* @brief Decrease the fd_file refcount, and release it if this is the last one
*/
void fd_file_put(struct file*);

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
