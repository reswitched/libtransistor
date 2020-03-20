#include <libtransistor/fs/fspfs.h>

#include <libtransistor/types.h>
#include <libtransistor/err.h>
#include <libtransistor/fd.h>
#include <libtransistor/ipc/fs/ifilesystem.h>
#include <libtransistor/ipc/fs/err.h>
#include <string.h>
#include <stdio.h>
#include <fcntl.h>
#include <errno.h>
#include <libtransistor/util.h>

struct inode {
	bool is_dir;
	ifilesystem_t fs;
	size_t path_len;
	char path[0x301];// TODO: Static ? PTR ?
};

struct ifs_file {
	ifile_t file;
	off_t head;
};


static trn_file_ops_t fspfs_file_ops;
static trn_inode_ops_t fspfs_inode_ops;
static trn_dir_ops_t trn_fspfs_dir_ops;

static result_t fspfs_is_dir(void *data, bool *out) {
	struct inode *inode = (struct inode*)data;

	*out = inode->is_dir;
	return RESULT_OK;
}

static result_t fspfs_lookup(void *data, trn_inode_t *out, const char *name, size_t name_len) {
	struct inode *inode = (struct inode*)data;
	struct inode *new_inode;
	uint32_t type;
	result_t r;
	const char *base_path;
	size_t base_path_len;

	base_path = inode->path;
	base_path_len = inode->path_len;

	// First, calculate len
	size_t l = base_path_len + name_len + 1;
	if (l >= sizeof(new_inode->path) - 1)
		return LIBTRANSISTOR_ERR_FS_NAME_TOO_LONG;

	new_inode = malloc(sizeof(struct inode));
	if (new_inode == NULL)
		return LIBTRANSISTOR_ERR_OUT_OF_MEMORY;

	new_inode->fs = inode->fs;

	strncpy(new_inode->path, base_path, base_path_len);

	int extra_slash = 0;
	if (base_path_len == 0 || new_inode->path[base_path_len - 1] != '/') {
		new_inode->path[base_path_len] = '/';
		extra_slash = 1;
	}

	strncpy(new_inode->path + base_path_len + extra_slash, name, name_len);
	new_inode->path[base_path_len + extra_slash + name_len] = '\0';
	new_inode->path_len = base_path_len + name_len + extra_slash;


	if ((r = ifilesystem_get_entry_type(inode->fs, &type, new_inode->path)) != RESULT_OK)
		goto fail;

	new_inode->is_dir = type == 0;

	out->data = new_inode;
	out->ops = &fspfs_inode_ops;

	return RESULT_OK;
fail:
	free(new_inode);
	return r;
}

static result_t fspfs_create_file(void *data, const char *name) {
	struct inode *inode = (struct inode*)data;
	result_t r;
	char full_path[0x301];
	size_t name_len = strlen(name);
	
	char *base_path;
	size_t base_path_len;

	base_path = inode->path;
	base_path_len = inode->path_len;

	strncpy(full_path, base_path, base_path_len);
	full_path[base_path_len] = '/';
	strncpy(full_path + base_path_len + 1, name, name_len);
	full_path[base_path_len + 1 + name_len] = '\0';

	if ((r = ifilesystem_create_file(inode->fs, 0, 0, full_path)) == FSPSRV_ERR_EXISTS)
		return LIBTRANSISTOR_ERR_FS_PATH_EXISTS;
	else
		return r;
}

static result_t fspfs_create_directory(void *data, const char *name) {
	struct inode *inode = (struct inode*)data;
	char full_path[0x301];
	size_t name_len = strlen(name);

	char *base_path;
	size_t base_path_len;

	base_path = inode->path;
	base_path_len = inode->path_len;

	strncpy(full_path, base_path, base_path_len);

	int extra_slash = 0;
	if (base_path_len == 0 || full_path[base_path_len - 1] != '/') {
		full_path[base_path_len] = '/';
		extra_slash = 1;
	}

	strncpy(full_path + base_path_len + extra_slash, name, name_len);
	full_path[base_path_len + extra_slash + name_len] = '\0';

	return ifilesystem_create_directory(inode->fs, full_path);
}

static result_t fspfs_remove_file(void *data) {
	struct inode *inode = (struct inode*)data;

	return ifilesystem_delete_file(inode->fs, inode->path);
}

static result_t fspfs_remove_empty_directory(void *data) {
	struct inode *inode = (struct inode*)data;

	return ifilesystem_delete_directory(inode->fs, inode->path);
}

static result_t fspfs_rename(void *data, const char *newpath) {
	struct inode *inode = (struct inode*)data;
	result_t r;
	char newpath_buf[0x301];

	if (sizeof(newpath_buf) < strlen(newpath))
		return LIBTRANSISTOR_ERR_FS_NAME_TOO_LONG;
	strncpy(newpath_buf, newpath, 0x301);

	if (inode->is_dir)
		// newpath must not exist, or be an existing empty directory.
		r = ifilesystem_rename_directory(inode->fs, inode->path, newpath_buf);
	else
		// newpath will be replaced with oldpath. The behavior if newpath is a
		// directory isn't really specified...
		r = ifilesystem_rename_file(inode->fs, inode->path, newpath_buf);

	// If this is a success, we need to fix this... Also, might want to have a
	// way to invalidate the traversal.
	if (r == RESULT_OK)
		strncpy(inode->path, newpath, 0x301);

	return r;
}

static result_t fspfs_open_as_file(void *data, int flags, int *fd) {
	struct inode *inode = (struct inode*)data;
	result_t r;
	uint32_t ifs_flags;
	uint64_t file_size;

	if (inode->is_dir)
		return LIBTRANSISTOR_ERR_FS_NOT_A_FILE;

	if (flags & O_RDWR)
		ifs_flags = 3;
	else if (flags & O_WRONLY)
		ifs_flags = 2;
	else
		ifs_flags = 1;
	// In unix land, we're kinda sorta *always* in append mode.
	ifs_flags |= 4;

	struct ifs_file *f = malloc(sizeof(struct ifs_file));
	if (f == NULL)
		return LIBTRANSISTOR_ERR_OUT_OF_MEMORY;

	if ((r = ifilesystem_open_file(inode->fs, &f->file, ifs_flags, inode->path)) != RESULT_OK)
		goto fail;

	if (flags & O_TRUNC) {
		if ((r = ifile_set_size(f->file, 0)) != RESULT_OK) {
			printf("Got an error: %x\n", r);
			goto fail;
		}
	}

	if (flags & O_APPEND) {
		if ((r = ifile_get_size(f->file, &file_size)) != RESULT_OK) {
			printf("Got an error: %x\n", r);
			goto fail;
		}
		f->head = file_size;
	} else {
		f->head = 0;
	}

	*fd = fd_create_file(&fspfs_file_ops, f);
	if (*fd < 0) {
		// TODO: We should have an errno_to_result
		r = LIBTRANSISTOR_ERR_UNSPECIFIED;
		goto fail_ifs;
	}

	return RESULT_OK;

fail_ifs:
	ipc_close(f->file);
fail:
	free(f);
	return r;
}

static result_t fspfs_open_as_dir(void *data, trn_dir_t *out) {
	struct inode *inode = (struct inode*)data;
	result_t r;

	if (!inode->is_dir)
		return LIBTRANSISTOR_ERR_FS_NOT_A_DIRECTORY;

	idirectory_t *dir = malloc(sizeof(idirectory_t));
	if (dir == NULL)
		return LIBTRANSISTOR_ERR_OUT_OF_MEMORY;

	if ((r = ifilesystem_open_directory(inode->fs, dir, 3, inode->path)) != RESULT_OK)
		goto fail;

	out->data = (void*)dir;
	out->ops = &trn_fspfs_dir_ops;
	return RESULT_OK;

fail:
	free(dir);
	return r;
}

static result_t fspfs_release(void *data) {
	struct inode *inode = (struct inode*)data;

	if(inode->path_len == 0) { // is this the root inode?
		ipc_close(inode->fs);
	}
	
	free(data);
	return RESULT_OK;
}

static result_t trn_fspfs_dir_next(void *data, trn_dirent_t *dirent) {
	idirectory_t *dir = (idirectory_t*)data;
	result_t r;
	idirectoryentry_t entry;
	uint64_t entries_read;

	if ((r = idirectory_read(*dir, &entries_read, &entry, 1 * sizeof(idirectoryentry_t))) != RESULT_OK)
		return r;
	if (entries_read == 0)
		return LIBTRANSISTOR_ERR_FS_OUT_OF_DIR_ENTRIES;

	size_t entry_path_len = strlen(entry.path);
	if (entry_path_len >= sizeof(dirent->name))
		return LIBTRANSISTOR_ERR_FS_NAME_TOO_LONG;

	dirent->name_size = entry_path_len;
	strcpy(dirent->name, entry.path);

	return RESULT_OK;
}

static void trn_fspfs_dir_close(void *data) {
	idirectory_t *dir = (idirectory_t*)data;

	ipc_close(*dir);
	free(dir);
}

static result_t fspfs_file_seek(void *data, off_t offset, int whence, off_t *position) {
	struct ifs_file *file = data;
	uint64_t fsize;
	result_t r;

	switch(whence) {
	case SEEK_SET:
		file->head = offset;
		break;
	case SEEK_CUR:
		file->head+= offset;
		break;
	case SEEK_END:
		if ((r = ifile_get_size(file->file, &fsize)) != RESULT_OK)
			return r;
		file->head = fsize + offset;
		break;
	default:
		return LIBTRANSISTOR_ERR_INVALID_ARGUMENT;
	}

	*position = file->head;
	return RESULT_OK;
}

static result_t fspfs_file_read(void *data, void *buf, size_t buf_size, size_t *bytes_read) {
	struct ifs_file *f = data;
	uint64_t out_size;
	result_t r;

	if ((r = ifile_read(f->file, &out_size, buf, buf_size, 0, f->head, buf_size)) != RESULT_OK) {
		printf("Got an error: %x\n", r);
		return r;
	}
	f->head += out_size;
	*bytes_read = out_size;
	return RESULT_OK;
}

static result_t fspfs_file_write(void *data, const void *buf, size_t buf_size, size_t *bytes_written) {
	struct ifs_file *f = data;
	result_t r;

	if ((r = ifile_write(f->file, 0, f->head, buf_size, buf, buf_size)) != RESULT_OK) {
		printf("Got an error: %x\n", r);
		return r;
	}
	f->head += buf_size;
	*bytes_written = buf_size;
	return RESULT_OK;
}

static result_t fspfs_file_release(trn_file_t *file) {
	struct ifs_file *f = file->data;

	ipc_close(f->file);
	free(f);
	return RESULT_OK;
}

static trn_file_ops_t fspfs_file_ops = {
	.seek = fspfs_file_seek,
	.read = fspfs_file_read,
	.write = fspfs_file_write,
	.release = fspfs_file_release
};

static trn_dir_ops_t trn_fspfs_dir_ops = {
	.next = trn_fspfs_dir_next,
	.close = trn_fspfs_dir_close,
};

static trn_inode_ops_t fspfs_inode_ops = {
	.is_dir = fspfs_is_dir,
	.lookup = fspfs_lookup,
	.release = fspfs_release,
	.create_file = fspfs_create_file,
	.create_directory = fspfs_create_directory,
	.rename = fspfs_rename,
	.remove_file = fspfs_remove_file,
	.remove_empty_directory = fspfs_remove_empty_directory,
	.open_as_file = fspfs_open_as_file,
	.open_as_dir = fspfs_open_as_dir
};

// Takes ownership of the ifilesystem. Will close it automatically on release.
result_t trn_fspfs_create(trn_inode_t *out, ifilesystem_t fs) {
	struct inode *inode = malloc(sizeof(struct inode));
	if (inode == NULL)
		return LIBTRANSISTOR_ERR_OUT_OF_MEMORY;

	inode->is_dir = true;
	inode->fs = fs;
	inode->path_len = 1;
	inode->path[0] = '/';
	inode->path[1] = '\0';

	out->data = inode;
	out->ops = &fspfs_inode_ops;
	return RESULT_OK;
}
