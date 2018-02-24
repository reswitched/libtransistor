#include <libtransistor/types.h>
#include <libtransistor/err.h>
#include <libtransistor/fd.h>
#include <libtransistor/fs/fspfs.h>
#include <libtransistor/ipc/fs/ifilesystem.h>
#include <string.h>
#include <stdio.h>
#include <fcntl.h>
#include <errno.h>
#include <libtransistor/util.h>

struct inode {
	bool is_dir;
	ifilesystem_t fs;
	size_t name_len;
	char name[0x301];// TODO: Static ? PTR ?
};

struct ifs_file {
	ifile_t file;
	off_t head;
};


static struct file_operations fspfs_file_ops;
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
	const char *root_name;
	size_t root_name_len;

	// Ugly hack to strip leading /
	if (strcmp(inode->name, "/") == 0) {
		root_name = "";
		root_name_len = 0;
	} else {
		root_name = inode->name;
		root_name_len = inode->name_len;
	}

	printf("TRACING FSPFS_LOOKUP for (%d) %s/%.*s\n", root_name_len, root_name, name_len, name);

	// First, calculate len
	size_t l = root_name_len + name_len + 1;
	if (l >= sizeof(new_inode->name) - 1)
		return LIBTRANSISTOR_ERR_FS_NAME_TOO_LONG;

	new_inode = malloc(sizeof(struct inode));
	if (new_inode == NULL)
		return LIBTRANSISTOR_ERR_OUT_OF_MEMORY;

	new_inode->fs = inode->fs;

	strncpy(new_inode->name, root_name, root_name_len);
	new_inode->name[root_name_len] = '/';
	strncpy(new_inode->name + root_name_len + 1, name, name_len);
	new_inode->name[root_name_len + 1 + name_len] = '\0';
	new_inode->name_len = l;

	printf("Getting entry type of %s\n", new_inode->name);
	if ((r = ifilesystem_get_entry_type(inode->fs, &type, new_inode->name)) != RESULT_OK)
		// TODO: ERRNOTFOUND
		goto fail;
	printf("Success! %d\n", type);

	new_inode->is_dir = type == 0;

	out->data = new_inode;
	out->ops = &fspfs_inode_ops;

	return RESULT_OK;
fail:
	printf("Fail: %d\n", r);
	free(new_inode);
	return r;
}

static result_t fspfs_open_as_file(void *data, int flags, int *fd) {
	struct inode *inode = (struct inode*)data;
	result_t r;
	uint32_t ifs_flags;

	if (inode->is_dir)
		return LIBTRANSISTOR_ERR_FS_NOT_A_FILE;

	if (flags & O_RDWR)
		ifs_flags = 3;
	else if (flags & O_WRONLY)
		ifs_flags = 2;
	else
		ifs_flags = 1;
	if (flags & O_APPEND)
		ifs_flags |= 4;

	struct ifs_file *f = malloc(sizeof(struct ifs_file));
	if (f == NULL)
		return LIBTRANSISTOR_ERR_OUT_OF_MEMORY;

	printf("ifilesystem_open_file %s\n", inode->name);
	if ((r = ifilesystem_open_file(inode->fs, &f->file, ifs_flags, inode->name)) != RESULT_OK)
		goto fail;
	f->head = 0;

	*fd = fd_create_file(&fspfs_file_ops, f);
	if (*fd < 0)
		goto fail_ifs;

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

	printf("ifilesystem_open_directory %s\n", inode->name);
	if ((r = ifilesystem_open_directory(inode->fs, dir, 3, &inode->name)) != RESULT_OK)
		goto fail;
	printf("ifilesystem_open_directory succeeded\n");

	out->data = (void*)dir;
	out->ops = &trn_fspfs_dir_ops;
	return RESULT_OK;

fail:
	free(dir);
	return r;
}

static result_t fspfs_release(void *data) {
	// TODO: Should we take ownership of the ifilesystem_t ?
	printf("Freeing %p\n", data);
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

static off_t fspfs_file_llseek(void *data, off_t offset, int whence) {
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
			return -EIO;
		file->head = fsize + offset;
		break;
	default:
		return -EINVAL;
	}
	return file->head;
}

static ssize_t fspfs_file_read(void *data, char *buf, size_t buf_size) {
	struct ifs_file *f = data;
	uint64_t out_size;
	result_t r;

	printf("Reading file from %x to %x\n", f->head, f->head + buf_size);
	if ((r = ifile_read(f->file, &out_size, buf, buf_size, 0, f->head, buf_size)) != RESULT_OK) {
		printf("Got an error: %x\n", r);
		return -EIO;
	}
	printf("Successfuly read from file: %lu\n", out_size);
	hexdump(buf, out_size);
	f->head += out_size;
	return out_size;
}

static int fspfs_file_release(struct file *file) {
	struct ifs_file *f = file->data;

	ipc_close(f->file);
	free(f);
	return 0;
}

static struct file_operations fspfs_file_ops = {
	.llseek = fspfs_file_llseek,
	.read = fspfs_file_read,
	.write = NULL,
	.flush = NULL,
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
	.open_as_file = fspfs_open_as_file,
	.open_as_dir = fspfs_open_as_dir
};

result_t trn_fspfs_create(trn_inode_t *out, ifilesystem_t fs) {
	struct inode *inode = malloc(sizeof(struct inode));
	if (inode == NULL)
		return LIBTRANSISTOR_ERR_OUT_OF_MEMORY;

	inode->is_dir = true;
	inode->fs = fs;
	inode->name_len = 1;
	inode->name[0] = '/';
	inode->name[1] = '\0';

	out->data = inode;
	out->ops = &fspfs_inode_ops;
	return RESULT_OK;
}
