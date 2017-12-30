#include<libtransistor/types.h>
#include<libtransistor/fs/fs.h>
#include<libtransistor/fs/inode.h>
#include<libtransistor/err.h>

#include<stdio.h>
#include<string.h>

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

// if this exits OK, it is the caller's responsiblity to close traverse[ (borrowed_recursion_out, traverse_recursion_out] ]
//  (the interval from borrowed_recursion_out to traverse_recursion_out, excluding borrowed_recursion_out but including traverse_recursion_out)
static result_t trn_fs_traverse(const char *path, trn_traverse_t *traverse, int *borrowed_recursion_out, int *traverse_recursion_out) {
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

	while(segment[0] != 0) {
		seglen = 0;
		while(segment[0] == '/') {
			segment++; // trim leading slashes
		}
		while(segment[seglen] != '/' && segment[seglen] != 0) {
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

	printf("realpath(\"%s\")\n", path);
	
	if((r = trn_fs_traverse(path, traverse, &borrowed_recursion, &traverse_recursion)) != RESULT_OK) {
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

result_t trn_fs_open(int *fd, const char *path, int flags) {
	result_t r;
	trn_traverse_t traverse[MAX_RECURSION];
	int borrowed_recursion = 0;
	int traverse_recursion = 0;
	if((r = trn_fs_traverse(path, traverse, &borrowed_recursion, &traverse_recursion)) != RESULT_OK) {
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
	if((r = trn_fs_traverse(path, traverse, &borrowed_recursion, &traverse_recursion)) != RESULT_OK) {
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
	if((r = trn_fs_traverse(path, traverse, &borrowed_recursion, &traverse_recursion)) != RESULT_OK) {
		return r;
	}

	for(int i = borrowed_recursion + 1; i <= cwd_recursion; i++) {
		cwd[i].inode.ops->release(cwd[i].inode.data);
	}
	
	cwd_recursion = traverse_recursion;
	memcpy(cwd, traverse, (cwd_recursion + 1) * sizeof(cwd[0]));
	printf("chdir, cwd_recursion is now %d\n", cwd_recursion);
}
