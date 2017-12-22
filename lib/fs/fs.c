#include<libtransistor/types.h>
#include<libtransistor/fs/fs.h>
#include<libtransistor/fs/inode.h>
#include<libtransistor/err.h>

#include<stdio.h>
#include<string.h>

#define MAX_RECURSION 256

static trn_inode_t *root = NULL;
static trn_inode_t cwd[MAX_RECURSION];
static int cwd_recursion = -1;

result_t trn_fs_set_root(trn_inode_t *new_root) {
	root = new_root;
	if(cwd_recursion == -1) {
		cwd[0] = *new_root;
		cwd_recursion = 0;
	}
	return RESULT_OK;
}

result_t trn_fs_open(int *fd, const char *path, int flags) {
	trn_inode_t traverse[MAX_RECURSION];
	memcpy(traverse, cwd, (cwd_recursion + 1) * sizeof(trn_inode_t));
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
			return LIBTRANSISTOR_ERR_FS_INVALID_PATH;
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
			r = traverse[traverse_recursion].ops->lookup(traverse[traverse_recursion].data, &traverse[traverse_recursion+1], segment, seglen);
			if(r) {
				return r;
			}
			traverse_recursion++;
		}
		
		segment+= seglen;
		seglen = 0;
	}

	return traverse[traverse_recursion].ops->open_as_file(traverse[traverse_recursion].data, flags, fd);
}
