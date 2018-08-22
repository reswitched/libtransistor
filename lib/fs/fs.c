#include<libtransistor/fs/fs.h>

#include<libtransistor/types.h>
#include<libtransistor/fs/inode.h>
#include<libtransistor/fs/mountfs.h>
#include<libtransistor/err.h>
#include<libtransistor/util.h>

#include<stdio.h>
#include<string.h>
#include<sys/stat.h>
#include<fcntl.h>

#define TRN_FS_DEBUG_ENABLED 0
#define TRN_FS_DEBUG(...) if(TRN_FS_DEBUG_ENABLED) dbg_printf(__VA_ARGS__)

#define MAX_RECURSION 256

static trn_inode_t *root = NULL;

typedef struct {
	trn_inode_t inode;
	char *name;
} trn_traverse_t;

static trn_traverse_t cwd[MAX_RECURSION];
static int cwd_recursion = -1;
static char *empty_name = "";

result_t trn_fs_set_root(trn_inode_t *new_root) {
	if(root != NULL) {
		root->ops->release(root->data);
	}
	
	root = new_root;
	
	cwd[0].inode = *new_root;
	cwd[0].name = empty_name;
	cwd_recursion = 0;

	return RESULT_OK;
}

// This will only work if trn_fs_set_root has not been called!
result_t trn_fs_mount(const char *mount_name, trn_inode_t mount) {
	if (root != NULL)
		return trn_mountfs_mount_fs(root, mount_name, mount);
	return LIBTRANSISTOR_ERR_FS_INTERNAL_ERROR;
}


// if this exits OK, it is the caller's responsiblity to close traverse[ (borrowed_recursion_out, traverse_recursion_out] ]
//  (the interval from borrowed_recursion_out to traverse_recursion_out, excluding borrowed_recursion_out but including traverse_recursion_out)
//
// Max_len is useful for partial traversal (as required by mkdir). It is not a required argument: if your path is \0-terminated, you can just set
// max_len to SIZE_MAX.
static result_t trn_fs_traverse(const char *path, size_t max_len, trn_traverse_t *traverse, int *borrowed_recursion_out, int *traverse_recursion_out) {
	memcpy(traverse, cwd, (cwd_recursion + 1) * sizeof(*traverse));
	int borrowed_recursion = cwd_recursion; // traverse[i<=borrowed_recursion] aren't owned by us, so we shouldn't close them
	int traverse_recursion = cwd_recursion;
	if(path[0] == '/') {
		borrowed_recursion = 0;
		traverse_recursion = 0;
	}
	const char *segment = path;
	int seglen = 0;

	result_t r;

	while(max_len > 0 && segment[0] != 0) {
		seglen = 0;
		while(max_len > 0 && segment[0] == '/') {
			max_len--;
			segment++; // trim leading slashes
		}
		while(max_len > 0 && segment[seglen] != '/' && segment[seglen] != 0) {
			max_len--;
			seglen++;
		}

		if(seglen == 0) { // trailing slash
			break;
		}

		trn_traverse_t *trv = &traverse[traverse_recursion];
		if(seglen == 2 && strncmp("..", segment, seglen) == 0) {
			if(traverse_recursion > 0) { // root is its own parent
				if(traverse_recursion > borrowed_recursion) { // this is an inode that we opened and that we own
					trv->inode.ops->release(trv->inode.data);
				} else {
					// reduce how many we're borrowing, because the only place we ever increment traverse_recursion
					// is when we open an inode that we own
					borrowed_recursion--;
				}
				traverse_recursion--;
			}
		} else if(seglen == 1 && strncmp(".", segment, seglen) == 0) {
		} else {
			if(traverse_recursion + 1 >= MAX_RECURSION) {
				r = LIBTRANSISTOR_ERR_FS_PATH_TOO_DEEP;
				goto fail;
			}

			r = trv->inode.ops->lookup(trv[0].inode.data, &trv[1].inode, segment, seglen);
			trv[1].name = malloc(seglen+1);
			if(trv[1].name == NULL) {
				r = LIBTRANSISTOR_ERR_OUT_OF_MEMORY;
				goto fail;
			}
			memcpy(trv[1].name, segment, seglen);
			trv[1].name[seglen] = 0;
			
			if(r) {
				goto fail;
			}
			traverse_recursion++;
		}
		
		segment+= seglen;
		seglen = 0;
	}

	if(traverse_recursion_out != NULL) {
		*traverse_recursion_out = traverse_recursion;
	}

	if(borrowed_recursion_out != NULL) {
		*borrowed_recursion_out = borrowed_recursion;
	}
	
	return RESULT_OK;
fail:
	for(int i = borrowed_recursion + 1; i <= traverse_recursion; i++) {
		traverse[i].inode.ops->release(traverse[i].inode.data);
	}
	return r;
}

result_t trn_fs_realpath(const char *path, char **resolved_path) {
	result_t r;
	trn_traverse_t traverse[MAX_RECURSION];
	int borrowed_recursion;
	int traverse_recursion;

	TRN_FS_DEBUG("realpath(\"%s\")\n", path);
	
	if((r = trn_fs_traverse(path, SIZE_MAX, traverse, &borrowed_recursion, &traverse_recursion)) != RESULT_OK) {
		return r;
	}
	size_t path_size = 0;
	for(int i = 0; i <= traverse_recursion; i++) {
		path_size+= strlen(traverse[i].name) + 1; // name and a trailing slash or terminating zero
	}
	if(path_size > 256) { // TODO: use PATH_MAX
		r = LIBTRANSISTOR_ERR_FS_NAME_TOO_LONG;
		goto fail;
	}
	if(*resolved_path == NULL) {
		*resolved_path = malloc(path_size);
		if(*resolved_path == NULL) {
			r = LIBTRANSISTOR_ERR_OUT_OF_MEMORY;
			goto fail;
		}
	}
	off_t copy_offset = 0;
	for(int i = 0; i <= traverse_recursion; i++) {
		strcpy(*resolved_path + copy_offset, traverse[i].name);
		copy_offset+= strlen(traverse[i].name);
		(*resolved_path)[copy_offset++] = '/';
	}
	(*resolved_path)[copy_offset-1] = 0;

	r = RESULT_OK;

fail: // release inodes that were opened during traversal
	for(int i = borrowed_recursion + 1; i <= traverse_recursion; i++) {
		traverse[i].inode.ops->release(traverse[i].inode.data);
	}
	return r;
}

static void get_path_parent_child(const char *path, const char **out_parent, size_t *out_len_parent, const char **out_child, size_t *out_child_len) {
	const char *path_end = path + strlen(path) - 1;
	const char *child;

	while (path < path_end && *path_end == '/') {
		// Skip trailing slashes
		path_end--;
	}

	child = path_end;
	while (path < child && *child != '/') {
		// Get child path
		child--;
	}
	*out_child = child + 1;
	*out_child_len = (path_end - child + 1);
	if (path < child - 1) {
		// We have a parent
		*out_parent = path;
		*out_len_parent = child - path;
	} else {
		// Parent is CWD
		*out_parent = "";
		*out_len_parent = 0;
	}
}

result_t trn_fs_mkdir(const char *path) {
	result_t r;
	trn_traverse_t traverse[MAX_RECURSION];
	int borrowed_recursion = 0;
	int traverse_recursion = 0;
	const char *parent_path, *child_path;
	size_t parent_path_size, child_path_size;

	get_path_parent_child(path, &parent_path, &parent_path_size, &child_path, &child_path_size);
	TRN_FS_DEBUG("Parent is %.*s, child is %.*s\n", parent_path_size, parent_path, child_path_size, child_path);
	if((r = trn_fs_traverse(parent_path, parent_path_size, traverse, &borrowed_recursion, &traverse_recursion)) != RESULT_OK) {
		return r;
	}

	TRN_FS_DEBUG("Creating child\n");
	r = traverse[traverse_recursion].inode.ops->create_directory(traverse[traverse_recursion].inode.data, child_path);

	for(int i = borrowed_recursion + 1; i <= traverse_recursion; i++) {
		traverse[i].inode.ops->release(traverse[i].inode.data);
	}
	
	return r;
}

result_t trn_fs_unlink(const char *path) {
	result_t r;
	trn_traverse_t traverse[MAX_RECURSION];
	int borrowed_recursion = 0;
	int traverse_recursion = 0;
	if((r = trn_fs_traverse(path, SIZE_MAX, traverse, &borrowed_recursion, &traverse_recursion)) != RESULT_OK) {
		return r;
	}
	
	r = traverse[traverse_recursion].inode.ops->remove_file(traverse[traverse_recursion].inode.data);

	for(int i = borrowed_recursion + 1; i <= traverse_recursion; i++) {
		traverse[i].inode.ops->release(traverse[i].inode.data);
	}

	return r;
}

result_t trn_fs_rmdir(const char *path) {
	result_t r;
	trn_traverse_t traverse[MAX_RECURSION];
	int borrowed_recursion = 0;
	int traverse_recursion = 0;
	if((r = trn_fs_traverse(path, SIZE_MAX, traverse, &borrowed_recursion, &traverse_recursion)) != RESULT_OK) {
		return r;
	}
	
	r = traverse[traverse_recursion].inode.ops->remove_empty_directory(traverse[traverse_recursion].inode.data);

	for(int i = borrowed_recursion + 1; i <= traverse_recursion; i++) {
		traverse[i].inode.ops->release(traverse[i].inode.data);
	}

	return r;
}

// TODO: Does not work in the case of nested mountfs, or if trn_fs_set_root was
// called.
result_t trn_fs_rename(const char *oldpath, const char *newpath) {
	result_t r;
	trn_traverse_t traverse[MAX_RECURSION];

	// Find handle to old path
	int borrowed_recursion = 0;
	int traverse_recursion = 0;
	if((r = trn_fs_traverse(oldpath, SIZE_MAX, traverse, &borrowed_recursion, &traverse_recursion)) != RESULT_OK) {
		return r;
	}

	// Skip the first element, of newpath, as that's the mountfs.
	// TODO: Find a better way to find the common ancestor in the face of
	// mountpoints...
	while (*newpath == '/')
		newpath++;
	while (*newpath != '/' && *newpath != '\0')
		newpath++;

	r = traverse[traverse_recursion].inode.ops->rename(traverse[traverse_recursion].inode.data, newpath);

	for(int i = borrowed_recursion + 1; i <= traverse_recursion; i++) {
		traverse[i].inode.ops->release(traverse[i].inode.data);
	}

	return r;
}

result_t trn_fs_open(int *fd, const char *path, int flags) {
	result_t r;
	trn_traverse_t traverse[MAX_RECURSION];
	int borrowed_recursion = 0;
	int traverse_recursion = 0;

	if (flags & O_CREAT) {
		// Create file if it does not exist. First traverse to the parent.
		const char *parent_path, *child;
		size_t parent_path_size, child_path_size;
		get_path_parent_child(path, &parent_path, &parent_path_size, &child, &child_path_size);

		if ((r = trn_fs_traverse(parent_path, parent_path_size, traverse, &borrowed_recursion, &traverse_recursion)) != RESULT_OK)
			return r;

		// Create the child (fail if it already exists).
		r = traverse[traverse_recursion].inode.ops->create_file(traverse[traverse_recursion].inode.data, child);

		// TODO: Reuse borrow to open the file ?
		for(int i = borrowed_recursion + 1; i <= traverse_recursion; i++) {
			traverse[i].inode.ops->release(traverse[i].inode.data);
		}

		if (r != RESULT_OK && (flags & O_EXCL || r != LIBTRANSISTOR_ERR_FS_PATH_EXISTS)) {
			return r;
		}
	}

	if((r = trn_fs_traverse(path, SIZE_MAX, traverse, &borrowed_recursion, &traverse_recursion)) != RESULT_OK) {
		return r;
	}
	
	r = traverse[traverse_recursion].inode.ops->open_as_file(traverse[traverse_recursion].inode.data, flags, fd);
	
	for(int i = borrowed_recursion + 1; i <= traverse_recursion; i++) {
		traverse[i].inode.ops->release(traverse[i].inode.data);
	}
	
	return r;
}

result_t trn_fs_opendir(trn_dir_t *dir, const char *path) {
	result_t r;
	trn_traverse_t traverse[MAX_RECURSION];
	int borrowed_recursion = 0;
	int traverse_recursion = 0;
	if((r = trn_fs_traverse(path, SIZE_MAX, traverse, &borrowed_recursion, &traverse_recursion)) != RESULT_OK) {
		return r;
	}
	
	r = traverse[traverse_recursion].inode.ops->open_as_dir(traverse[traverse_recursion].inode.data, dir);

	for(int i = borrowed_recursion + 1; i <= traverse_recursion; i++) {
		traverse[i].inode.ops->release(traverse[i].inode.data);
	}
	
	return r;
}

result_t trn_fs_chdir(const char *path) {
	result_t r;
	trn_traverse_t traverse[MAX_RECURSION];
	int borrowed_recursion;
	int traverse_recursion;
	if((r = trn_fs_traverse(path, SIZE_MAX, traverse, &borrowed_recursion, &traverse_recursion)) != RESULT_OK) {
		return r;
	}

	for(int i = borrowed_recursion + 1; i <= cwd_recursion; i++) {
		cwd[i].inode.ops->release(cwd[i].inode.data);
	}
	
	cwd_recursion = traverse_recursion;
	memcpy(cwd, traverse, (cwd_recursion + 1) * sizeof(cwd[0]));
	TRN_FS_DEBUG("chdir, cwd_recursion is now %d\n", cwd_recursion);

	return RESULT_OK;
}

result_t trn_fs_stat(const char *path, struct stat *st) {
	result_t r;
	trn_traverse_t traverse[MAX_RECURSION];
	int borrowed_recursion = 0;
	int traverse_recursion = 0;
	if((r = trn_fs_traverse(path, SIZE_MAX, traverse, &borrowed_recursion, &traverse_recursion)) != RESULT_OK) {
		return r;
	}

	bool is_dir;
	r = traverse[traverse_recursion].inode.ops->is_dir(traverse[traverse_recursion].inode.data, &is_dir);

	st->st_mode = is_dir ? S_IFDIR : S_IFREG;
	
	for(int i = borrowed_recursion + 1; i <= traverse_recursion; i++) {
		traverse[i].inode.ops->release(traverse[i].inode.data);
	}
	
	return r;
}
