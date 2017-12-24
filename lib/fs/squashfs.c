#include<libtransistor/fs/inode.h>
#include<libtransistor/fd.h>
#include<libtransistor/err.h>

#include<errno.h>
#include<string.h>
#include<stdlib.h>
#include<sys/stat.h>

#include "../squashfs/squashfuse.h"

static trn_dir_ops_t trn_sqfs_dir_ops;
static struct file_operations trn_sqfs_file_ops;
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
	
	trn_sqfs_inode_t *out_data = malloc(sizeof(*out_data));
	if(out_data == NULL) {
		return LIBTRANSISTOR_ERR_OUT_OF_MEMORY;
	}
	
	dirent->inode.data = out_data;
	err = sqfs_inode_get(dir->fs, &out_data->inode, dir->dentry.inode);
	if(err) {
		free(out_data);
		return LIBTRANSISTOR_ERR_FS_INTERNAL_ERROR;
	}
	dirent->inode.ops = &trn_sqfs_inode_ops;

	if(dir->dentry.name_size > sizeof(dirent->name)) {
		free(out_data);
		return LIBTRANSISTOR_ERR_FS_NAME_TOO_LONG;
	}
	
	memcpy(dirent->name, dir->dentry.name, dir->dentry.name_size);
	dirent->name_size = dir->dentry.name_size;

	return RESULT_OK;
}

static trn_dir_ops_t trn_sqfs_dir_ops = {
	.next = trn_sqfs_dir_next,
	.close = NULL,
};

static off_t trn_sqfs_file_llseek(void *data, off_t offset, int whence) {
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
		return -EINVAL;
	}
	return file->head;
}

static ssize_t trn_sqfs_file_read(void *data, char *buf, size_t size) {
	trn_sqfs_file_t *file = data;
	off_t osize = size;
	if(sqfs_read_range(file->fs, &file->inode, file->head, &osize, buf)) {
		return -EIO;
	}
	file->head+= osize;
	return osize;
}

static ssize_t trn_sqfs_file_write(void *data, const char *buf, size_t size) {
	return -EROFS;
}

static int trn_sqfs_file_flush(void *data) {
	return -EROFS;
}

static int trn_sqfs_file_release(struct file *f) {
	trn_sqfs_file_t *file = f->data;
	free(file);
	return 0;
}

static struct file_operations trn_sqfs_file_ops = {
	.llseek = trn_sqfs_file_llseek,
	.read = trn_sqfs_file_read,
	.write = trn_sqfs_file_write,
	.flush = trn_sqfs_file_flush,
	.release = trn_sqfs_file_release,
};

static result_t trn_sqfs_is_dir(void *data, bool *out) {
	trn_sqfs_inode_t *inode = data;
	return S_ISDIR(inode->inode.base.mode);
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

static trn_inode_ops_t trn_sqfs_inode_ops = {
	.is_dir = trn_sqfs_is_dir,
	.lookup = trn_sqfs_lookup,
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
