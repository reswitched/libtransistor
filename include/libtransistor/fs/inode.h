#pragma once

#include<libtransistor/types.h>
#include<stdlib.h>

struct trn_inode_ops_t;

typedef struct {
	void *data;
	struct trn_inode_ops_t *ops;
} trn_inode_t; // libTRaNsistor INODE

typedef struct {
	trn_inode_t inode;
	char name[256];
	size_t name_size;
} trn_dirent_t;

typedef struct {
	result_t (*rewind)(void *dir);
	result_t (*next)(void *dir, trn_dirent_t *dirent);
	void (*close)(void *dir);
} trn_dir_ops_t;

typedef struct {
	void *data;
	trn_dir_ops_t *ops;
} trn_dir_t;

typedef struct trn_inode_ops_t {
	result_t (*is_dir)(void *inode, bool *out);
	result_t (*lookup)(void *inode, trn_inode_t *out, const char *name, size_t name_length);
	result_t (*release)(void *inode);
	result_t (*open_as_file)(void *inode, int mode, int *fd);
	result_t (*open_as_dir)(void *inode, trn_dir_t *out);
} trn_inode_ops_t;
