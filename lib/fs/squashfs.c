#include<libtransistor/fs/inode.h>
#include<libtransistor/fd.h>
#include<libtransistor/err.h>

#include<errno.h>
#include<string.h>
#include<stdlib.h>
#include<sys/stat.h>

#include "../squashfs/squashfuse.h"

static trn_dir_ops_t trn_sqfs_dir_ops;
static trn_file_ops_t trn_sqfs_file_ops;
static trn_inode_ops_t trn_sqfs_inode_ops;

typedef struct {
	sqfs *fs;
	sqfs_dir dir;
	sqfs_dir_entry dentry;
	char name_buf[SQUASHFS_NAME_LEN + 1];
} trn_sqfs_dir_t;

typedef struct {
	sqfs *fs;
	sqfs_inode inode;
	off_t head;
} trn_sqfs_file_t;

typedef struct {
	sqfs *fs;
	sqfs_inode inode;
} trn_sqfs_inode_t;

static result_t trn_sqfs_dir_next(void *data, trn_dirent_t *dirent) {
	trn_sqfs_dir_t *dir = data;
	sqfs_err err = SQFS_OK;
	if(!sqfs_dir_next(dir->fs, &dir->dir, &dir->dentry, &err)) {
		if(err != SQFS_OK) {
			return LIBTRANSISTOR_ERR_FS_INTERNAL_ERROR;
		} else {
			return LIBTRANSISTOR_ERR_FS_OUT_OF_DIR_ENTRIES;
		}
	}
	
	if(dir->dentry.name_size >= sizeof(dirent->name)-1)
		return LIBTRANSISTOR_ERR_FS_NAME_TOO_LONG;
	
	memcpy(dirent->name, dir->dentry.name, dir->dentry.name_size);
	dirent->name_size = dir->dentry.name_size;
	dirent->name[dirent->name_size] = 0;

	return RESULT_OK;
}

static trn_dir_ops_t trn_sqfs_dir_ops = {
	.next = trn_sqfs_dir_next,
	.close = NULL,
};

static result_t trn_sqfs_file_seek(void *data, off_t offset, int whence, off_t *position) {
	trn_sqfs_file_t *file = data;
	switch(whence) {
	case SEEK_SET:
		file->head = offset;
		break;
	case SEEK_CUR:
		file->head+= offset;
		break;
	case SEEK_END:
		file->head = file->inode.xtra.reg.file_size + offset;
		break;
	default:
		return LIBTRANSISTOR_ERR_INVALID_ARGUMENT;
	}
	*position = file->head;
	return RESULT_OK;
}

static result_t trn_sqfs_file_read(void *data, char *buf, size_t size, size_t *bytes_read) {
	trn_sqfs_file_t *file = data;
	off_t osize = size;
	if(sqfs_read_range(file->fs, &file->inode, file->head, &osize, buf)) {
		return LIBTRANSISTOR_ERR_FS_IO_ERROR;
	}
	file->head+= osize;
	*bytes_read = osize;
	return RESULT_OK;
}

static result_t trn_sqfs_file_write(void *data, const char *buf, size_t size, size_t *bytes_written) {
	return LIBTRANSISTOR_ERR_FS_READ_ONLY;
}

static result_t trn_sqfs_file_release(trn_file_t *f) {
	trn_sqfs_file_t *file = f->data;
	free(file);
	return RESULT_OK;
}

static trn_file_ops_t trn_sqfs_file_ops = {
	.seek = trn_sqfs_file_seek,
	.read = trn_sqfs_file_read,
	.write = trn_sqfs_file_write,
	.release = trn_sqfs_file_release,
};

static result_t trn_sqfs_is_dir(void *data, bool *out) {
	trn_sqfs_inode_t *inode = data;
	*out = S_ISDIR(inode->inode.base.mode);
	return RESULT_OK;
}

static result_t trn_sqfs_lookup(void *data, trn_inode_t *out, const char *name, size_t name_length) {
	trn_sqfs_inode_t *inode = data;

	out->ops = &trn_sqfs_inode_ops;
	if(!S_ISDIR(inode->inode.base.mode)) {
		return LIBTRANSISTOR_ERR_FS_NOT_A_DIRECTORY;
	}

	sqfs_dir_entry entry;
	char namebuf[SQUASHFS_NAME_LEN + 1];
	sqfs_dentry_init(&entry, namebuf);

	bool found;
	sqfs_err err = sqfs_dir_lookup(inode->fs, &inode->inode, name, name_length, &entry, &found);
	if(err != SQFS_OK) {
		return LIBTRANSISTOR_ERR_FS_INTERNAL_ERROR;
	}
	if(!found) {
		return LIBTRANSISTOR_ERR_FS_NOT_FOUND;
	}

	trn_sqfs_inode_t *out_data = malloc(sizeof(*out_data));
	if(out_data == NULL) {
		return LIBTRANSISTOR_ERR_OUT_OF_MEMORY;
	}
	out->data = out_data;

	out_data->fs = inode->fs;
	err = sqfs_inode_get(inode->fs, &out_data->inode, entry.inode);
	if(err != SQFS_OK) {
		free(out_data);
		return LIBTRANSISTOR_ERR_FS_INTERNAL_ERROR;
	}
	
	return RESULT_OK;
}

static result_t trn_sqfs_release(void *data) {
	// TODO: implement this
	return RESULT_OK;
}

static result_t trn_sqfs_open_as_file(void *data, int mode, int *fd) {
	trn_sqfs_inode_t *inode = data;
	
	if(!S_ISREG(inode->inode.base.mode)) {
		return LIBTRANSISTOR_ERR_FS_NOT_A_FILE;
	}
	
	trn_sqfs_file_t *file = malloc(sizeof(*file));
	if(file == NULL) {
		return LIBTRANSISTOR_ERR_OUT_OF_MEMORY;
	}

	file->fs = inode->fs;
	file->inode = inode->inode;
	file->head = 0;
	
	*fd = fd_create_file(&trn_sqfs_file_ops, file);
	if(*fd < 0) {
		return LIBTRANSISTOR_ERR_FS_INTERNAL_ERROR;
	}

	return RESULT_OK;
}

static result_t trn_sqfs_open_as_dir(void *data, trn_dir_t *out) {
	trn_sqfs_inode_t *inode = data;
	
	if(!S_ISDIR(inode->inode.base.mode)) {
		return LIBTRANSISTOR_ERR_FS_NOT_A_DIRECTORY;
	}
	
	trn_sqfs_dir_t *dir = malloc(sizeof(*dir));
	if(dir == NULL) {
		return LIBTRANSISTOR_ERR_OUT_OF_MEMORY;
	}

	dir->fs = inode->fs;
	sqfs_err err = sqfs_dir_open(inode->fs, &inode->inode, &dir->dir, 0);
	if(err != SQFS_OK) {
		return LIBTRANSISTOR_ERR_FS_INTERNAL_ERROR;
	}
	sqfs_dentry_init(&dir->dentry, dir->name_buf);
	
	out->data = dir;
	out->ops = &trn_sqfs_dir_ops;

	return RESULT_OK;
}

static result_t trn_sqfs_create_file(void *data, const char *name) {
    return LIBTRANSISTOR_ERR_FS_READ_ONLY;
}

static result_t trn_sqfs_create_directory(void *data, const char *name) {
    return LIBTRANSISTOR_ERR_FS_READ_ONLY;
}

static result_t trn_sqfs_rename(void *data, const char *newpath) {
    return LIBTRANSISTOR_ERR_FS_READ_ONLY;
}

static result_t trn_sqfs_remove_file(void *inode) {
	return LIBTRANSISTOR_ERR_FS_READ_ONLY;
}

static result_t trn_sqfs_remove_empty_directory(void *inode) {
	return LIBTRANSISTOR_ERR_FS_READ_ONLY;
}

static trn_inode_ops_t trn_sqfs_inode_ops = {
	.is_dir = trn_sqfs_is_dir,
	.lookup = trn_sqfs_lookup,
	.release = trn_sqfs_release,
	.create_file = trn_sqfs_create_file,
	.create_directory = trn_sqfs_create_directory,
	.rename = trn_sqfs_rename,
	.remove_file = trn_sqfs_remove_file,
	.remove_empty_directory = trn_sqfs_remove_empty_directory,
	.open_as_file = trn_sqfs_open_as_file,
	.open_as_dir = trn_sqfs_open_as_dir,
};

result_t trn_sqfs_open_root(trn_inode_t *out, sqfs *fs) {
	trn_sqfs_inode_t *out_data = malloc(sizeof(*out_data));
	if(out_data == NULL) {
		return LIBTRANSISTOR_ERR_OUT_OF_MEMORY;
	}

	out_data->fs = fs;
	sqfs_err err = SQFS_OK;
	err = sqfs_inode_get(fs, &out_data->inode, sqfs_inode_root(fs));
	if(err != SQFS_OK) {
		free(out_data);
		return LIBTRANSISTOR_ERR_FS_INTERNAL_ERROR;
	}
	
	out->data = out_data;
	out->ops = &trn_sqfs_inode_ops;

	return RESULT_OK;
}
