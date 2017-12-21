#include<stdio.h>
#include<libtransistor/types.h>
#include<libtransistor/util.h>
#include<errno.h>

#include"../lib/squashfs/squashfuse.h"

extern int sqfs_img_fd;

int main(int argc, char *argv[]) {
	sqfs_err err = SQFS_OK;
	sqfs_traverse trv;
	sqfs fs;

	err = sqfs_init(&fs, sqfs_img_fd, 0);
	printf("sqfs init returned %d\n", err);

	if(err != SQFS_OK) {
		return 1;
	}

	err = sqfs_traverse_open(&trv, &fs, sqfs_inode_root(&fs));
	if(err != SQFS_OK) {
		printf("failed to open traverse: %d\n", err);
		return 1;
	}

	while(sqfs_traverse_next(&trv, &err)) {
		if(!trv.dir_end) {
			printf("%s\n", trv.path);
		}
	}
	if(err) {
		printf("traverse error: %d\n", err);
	}
	sqfs_traverse_close(&trv);
	
	return 0;
}
