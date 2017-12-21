#include<stdio.h>
#include<libtransistor/types.h>
#include<libtransistor/util.h>
#include<libtransistor/fs/inode.h>
#include<libtransistor/fs/squashfs.h>
#include<libtransistor/fs/fs.h>
#include<errno.h>

#include"../lib/squashfs/squashfuse.h"

int main(int argc, char *argv[]) {
	result_t r;
	
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
		printf("fopen failure: %d\n", errno);
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
