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
	root = new_root;
	if(cwd_recursion == -1) {
		cwd[0].inode = *new_root;
		cwd[0].name = empty_name;
		cwd_recursion = 0;
	}
	return RESULT_OK;
}

static result_t trn_fs_traverse(const char *path, trn_traverse_t *traverse, int *traverse_recursion_out) {
	memcpy(traverse, cwd, (cwd_recursion + 1) * sizeof(*traverse));
	int traverse_recursion = cwd_recursion;
	if(path[0] == '/') {
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

		if(seglen == 2 && strncmp("..", segment, seglen) == 0) {
			if(traverse_recursion > 0) { // root is its own parent
				traverse_recursion--;
			}
		} else if(seglen == 1 && strncmp(".", segment, seglen) == 0) {
		} else {
			if(traverse_recursion + 1 >= MAX_RECURSION) {
				return LIBTRANSISTOR_ERR_FS_PATH_TOO_DEEP;
			}

			trn_traverse_t *trv = &traverse[traverse_recursion];
			r = trv->inode.ops->lookup(trv[0].inode.data, &trv[1].inode, segment, seglen);
			trv[1].name = malloc(seglen+1);
			if(trv[1].name == NULL) {
				return LIBTRANSISTOR_ERR_OUT_OF_MEMORY;
			}
			memcpy(trv[1].name, segment, seglen);
			trv[1].name[seglen] = 0;
			
			if(r) {
				return r;
			}
			traverse_recursion++;
		}
		
		segment+= seglen;
		seglen = 0;
	}

	if(traverse_recursion_out != NULL) {
		*traverse_recursion_out = traverse_recursion;
	}
	return RESULT_OK;
}

result_t trn_fs_realpath(const char *path, char **resolved_path) {
	result_t r;
	trn_traverse_t traverse[MAX_RECURSION];
	int traverse_recursion;
	if((r = trn_fs_traverse(path, traverse, &traverse_recursion)) != RESULT_OK) {
		return r;
	}
	size_t path_size = 0;
	for(int i = 0; i < traverse_recursion; i++) {
		path_size+= strlen(traverse[i].name) + 1; // name and a trailing slash or terminating zero
	}
	if(path_size > 256) { // TODO: use PATH_MAX
		return LIBTRANSISTOR_ERR_FS_NAME_TOO_LONG;
	}
	if(*resolved_path == NULL) {
		*resolved_path = malloc(path_size);
		if(*resolved_path == NULL) {
			return LIBTRANSISTOR_ERR_OUT_OF_MEMORY;
		}
	}
	off_t copy_offset = 0;
	for(int i = 0; i < traverse_recursion; i++) {
		strcpy(*resolved_path + copy_offset, traverse[i].name);
		copy_offset+= strlen(traverse[i].name);
		(*resolved_path)[copy_offset++] = '/';
	}
	(*resolved_path)[copy_offset-1] = '0';
	return RESULT_OK;
}

result_t trn_fs_open(int *fd, const char *path, int flags) {
	result_t r;
	trn_traverse_t traverse[MAX_RECURSION];
	int traverse_recursion = 0;
	if((r = trn_fs_traverse(path, traverse, &traverse_recursion)) != RESULT_OK) {
		return r;
	}
	
	return traverse[traverse_recursion].inode.ops->open_as_file(traverse[traverse_recursion].inode.data, flags, fd);
}

result_t trn_fs_opendir(trn_dir_t *dir, const char *path) {
	result_t r;
	trn_traverse_t traverse[MAX_RECURSION];
	int traverse_recursion = 0;
	if((r = trn_fs_traverse(path, traverse, &traverse_recursion)) != RESULT_OK) {
		return r;
	}
	
	return traverse[traverse_recursion].inode.ops->open_as_dir(traverse[traverse_recursion].inode.data, dir);
}
