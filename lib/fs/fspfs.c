#include <libtransistor/types.h>
#include <libtransistor/err.h>
#include <libtransistor/fs/fspfs.h>
#include <libtransistor/ipc/fs/ifilesystem.h>
#include <string.h>
#include <stdio.h>

struct inode {
	bool is_dir;
	ifilesystem_t fs;
	size_t name_len;
	char name[0x301];// TODO: Static ? PTR ?
};

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

	// First, calculate len
	size_t l = inode->name_len + name_len + 1;
	if (l >= sizeof(new_inode->name) - 1)
		return LIBTRANSISTOR_ERR_FS_NAME_TOO_LONG;

	new_inode = malloc(sizeof(struct inode));
	if (new_inode == NULL)
		return LIBTRANSISTOR_ERR_OUT_OF_MEMORY;

	new_inode->fs = inode->fs;
	strncpy(new_inode->name, inode->name, inode->name_len);
	new_inode->name[inode->name_len] = '/';
	strncpy(new_inode->name + inode->name_len + 1, name, name_len);
	new_inode->name[inode->name_len + 1 + name_len] = '\0';

	if ((r = ifilesystem_get_entry_type(inode->fs, &type, new_inode->name)))
		// TODO: ERRNOTFOUND
		goto fail;
	new_inode->is_dir = type == 0;

	out->data = new_inode;
	out->ops = &fspfs_inode_ops;

	return RESULT_OK;
fail:
	free(new_inode);
	return r;
}

static result_t fspfs_open_as_file(void *data, int mode, int *fd) {
	return LIBTRANSISTOR_ERR_FS_INTERNAL_ERROR;
}

static result_t fspfs_open_as_dir(void *data, trn_dir_t *out) {
	struct inode *inode = (struct inode*)data;
	result_t r;

	idirectory_t *dir = malloc(sizeof(idirectory_t));
	if (dir == NULL)
		return LIBTRANSISTOR_ERR_OUT_OF_MEMORY;

	printf("ifilesystem_open_directory %s\n", inode->name);
	if ((r = ifilesystem_open_directory(inode->fs, dir, 3, inode->name)) != RESULT_OK)
		goto fail;
	printf("ifilesystem_open_directory succeeded\n");

	out->data = (void*)dir;
	printf("1\n");
	out->ops = &trn_fspfs_dir_ops;
	printf("2\n");
	return RESULT_OK;

fail:
	free(dir);
	return r;
}

static result_t fspfs_release(void *data) {
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
