#include<stdio.h>
#include<libtransistor/types.h>
#include<libtransistor/util.h>
#include<libtransistor/fs/inode.h>
#include<libtransistor/fs/squashfs.h>
#include<libtransistor/fs/fs.h>
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

	trn_inode_t root_inode;
	result_t r;
	r = trn_sqfs_open_root(&root_inode, &fs);
	if(r) {
		printf("failed to open root: 0x%x\n", r);
		return 1;
	}
	if((r = trn_fs_set_root(&root_inode)) != RESULT_OK) {
		printf("failed to set root: 0x%x\n", r);
		return 1;
	}

	printf("trn_fs_open:\n");
	int fd;
	if((r = trn_fs_open(&fd, "/foo.bar", 0)) != RESULT_OK) {
		printf("failed to open: 0x%x\n", r);
		return 1;
	}
	printf("opened: %d\n", fd);

	char buf[256];
	ssize_t rd = read(fd, buf, sizeof(buf));
	if(rd < 0) {
		printf("err\n");
		return 1;
	}
	printf("read: %s\n", buf);

	FILE *f = fopen("/./testdir/../.././testdir/./testfile", "rb");
	if(f == NULL) {
		printf("fopen failure\n");
		return 1;
	}
	rd = fread(buf, sizeof(*buf), sizeof(buf)/sizeof(*buf), f);
	if(rd == 0) {
		printf("fread failure\n");
		return 1;
	}
	printf("fread: %d: %.*s\n", rd, rd, buf);
	
	return 0;
}
