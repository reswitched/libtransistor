#include<libtransistor/fs/inode.h>
#include<libtransistor/fd.h>
#include<libtransistor/err.h>

#include<errno.h>
#include<string.h>
#include<stdlib.h>
#include<sys/stat.h>
#include<stdio.h>

#define max(a,b) ((a) > (b) ? (a) : (b))

struct mountpoint {
	struct mountpoint *next;
	const char *name; // TODO: Static array ?
	trn_inode_t *fs;
	trn_inode_ops_t ops_clone;
};

static struct trn_inode_ops_t rootfs_inode_ops;
static trn_dir_ops_t trn_rootfs_dir_ops;

static result_t empty_release(void *inode) {
	return RESULT_OK;
}

// This borrows the name. Maybe I should make a copy?
// It takes ownership of the mountpoint, and will call release on it automatically
// on umount.
result_t trn_rootfs_mount_fs(trn_inode_t *fs, const char *name, trn_inode_t *mountpoint) {
	if (fs == NULL || fs->ops != &rootfs_inode_ops)
		return LIBTRANSISTOR_ERR_FS_INTERNAL_ERROR;

	struct mountpoint **cur_root = (struct mountpoint**)fs->data;

	struct mountpoint *m = malloc(sizeof(struct mountpoint));
	if (m == NULL)
		return LIBTRANSISTOR_ERR_OUT_OF_MEMORY;

	if (name[0] != '/')
		return LIBTRANSISTOR_ERR_FS_INTERNAL_ERROR;

	size_t i;
	for (i = 0; name[i] == '/'; i++) ;
	for (size_t j = i; name[j] != '\0'; j++) {
		if (name[j] == '/')
			return LIBTRANSISTOR_ERR_FS_INVALID_PATH;
	}
	m->name = name + i;
	m->fs = mountpoint;
	m->ops_clone = *m->fs->ops;
	m->fs->ops->release = empty_release;

	// TODO: Locking
	m->next = *cur_root;
	*cur_root = m;

	return RESULT_OK;
}

static result_t trn_rootfs_is_dir(void *data, bool *out) {
	// Everything is a dir in rootfs.
	*out = 1;
	return RESULT_OK;
}

static result_t trn_rootfs_lookup(void *data, trn_inode_t *out, const char *name, size_t name_length) {
	// This should only have a single inode ever. So I don't need to check the data out.
	struct mountpoint **mounts = (struct mountpoint**)data;
	struct mountpoint *cur_mount = *mounts;
	for (; cur_mount != NULL; cur_mount = cur_mount->next) {
		if (strncmp(cur_mount->name, name, name_length) == 0)
			break;
	}
	if (cur_mount == NULL)
		return LIBTRANSISTOR_ERR_FS_NOT_FOUND;

	// Eh. That "pointer begone" thing is pretty ugly.
	*out = *cur_mount->fs;
	return RESULT_OK;
}

static result_t trn_rootfs_release(void *data) {
	struct mountpoint **mounts = (struct mountpoint**)data;
	struct mountpoint *cur_mount = *mounts;
	result_t r;

	for (; cur_mount != NULL; cur_mount = cur_mount->next) {
		printf("Unmounting %s\n", cur_mount->name);
		// Print the error, and discard it.
		r = cur_mount->ops_clone.release(cur_mount->fs->data);
		if (r != RESULT_OK)
			printf("Error unmounting %s: %lx\n", cur_mount->name, r);
	}
	return RESULT_OK;
}

static result_t trn_rootfs_create_file(void *data, const char *name) {
	return LIBTRANSISTOR_ERR_FS_INTERNAL_ERROR;
}

static result_t trn_rootfs_create_directory(void *data, const char *name) {
	return LIBTRANSISTOR_ERR_FS_INTERNAL_ERROR;
}

static result_t trn_rootfs_open_as_file(void *data, int mode, int *fd) {
	return LIBTRANSISTOR_ERR_FS_NOT_A_FILE;
}

static result_t trn_rootfs_remove_file(void *inode) {
	return LIBTRANSISTOR_ERR_FS_INTERNAL_ERROR;
}

static result_t trn_rootfs_remove_empty_directory(void *inode) {
	return LIBTRANSISTOR_ERR_FS_INTERNAL_ERROR;
}

static result_t trn_rootfs_open_as_dir(void *data, trn_dir_t *out) {
	// TODO: Clone the linked list.
	// TODO: Same comment as trn_rootfs_create below.
	struct mountpoint **mounts = malloc(sizeof(struct mountpoint*));
	if (mounts == NULL)
		return LIBTRANSISTOR_ERR_OUT_OF_MEMORY;

	*mounts = *(struct mountpoint**)data;
	out->data = mounts;
	out->ops = &trn_rootfs_dir_ops;
	return RESULT_OK;
}

static result_t trn_rootfs_dir_next(void *data, trn_dirent_t *dirent) {
	struct mountpoint **mount = (struct mountpoint**)data;
	if (*mount == NULL)
		return LIBTRANSISTOR_ERR_FS_OUT_OF_DIR_ENTRIES;

	size_t mount_len = strlen((*mount)->name);
	if (!(mount_len < sizeof(dirent->name)))
		return LIBTRANSISTOR_ERR_FS_NAME_TOO_LONG;

	strncpy(dirent->name, (*mount)->name, mount_len);
	dirent->name_size = mount_len;
	*mount = (*mount)->next;
	return RESULT_OK;
}

static trn_dir_ops_t trn_rootfs_dir_ops = {
	.next = trn_rootfs_dir_next,
	.close = free,
};

static struct trn_inode_ops_t rootfs_inode_ops = {
	.is_dir = trn_rootfs_is_dir,
	.lookup = trn_rootfs_lookup,
	.release = trn_rootfs_release,
	.create_file = trn_rootfs_create_file,
	.create_directory = trn_rootfs_create_directory,
	.remove_file = trn_rootfs_remove_file,
	.remove_empty_directory = trn_rootfs_remove_empty_directory,
	.open_as_file = trn_rootfs_open_as_file,
	.open_as_dir = trn_rootfs_open_as_dir
};

result_t trn_rootfs_create(trn_inode_t *out) {
	// TODO: This is a bit dumb. Functions should be passed a pointer to their
	// data so they can change it directly. This would avoid this allocation.
	struct mountpoint **mountpoint = malloc(sizeof(struct mountpoint*));
	if (mountpoint == NULL)
		return LIBTRANSISTOR_ERR_OUT_OF_MEMORY;

	*mountpoint = NULL;
	out->data = mountpoint;
	out->ops = &rootfs_inode_ops;
	return RESULT_OK;
}
