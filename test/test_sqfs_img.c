#include<libtransistor/types.h>
#include<libtransistor/util.h>
#include<libtransistor/fs/inode.h>
#include<libtransistor/fs/squashfs.h>
#include<libtransistor/fs/fs.h>
#include<errno.h>
#include<stdio.h>
#include<dirent.h>
#include<fcntl.h>
#include<unistd.h>

#include"../lib/squashfs/squashfuse.h"

int ls(char *str) {
	DIR *d;
	struct dirent *dent;

	d = opendir(str);
	if(d == NULL) {
		printf("failed to open directory: %d\n", errno);
		return 1;
	}

	printf("Reading sdcard through unix\n");
	while((dent = readdir(d)) != NULL) {
		printf("dent: %.*s\n", dent->d_namlen, dent->d_name);
	}
	closedir(d);
	return 0;
}

int main(int argc, char *argv[]) {
	result_t r;

	printf("Opening / through unix\n");
	DIR *d = opendir("/");
	if(d == NULL) {
		printf("failed to open directory: %d\n", errno);
		return 1;
	}

	struct dirent *dent;
	printf("Reading dir through unix\n");
	while((dent = readdir(d)) != NULL) {
		printf("dent: %.*s\n", dent->d_namlen, dent->d_name);
	}
	closedir(d);
	
	printf("trn_fs_open:\n");
	int fd;
	if((r = trn_fs_open(&fd, "/squashfs/foo.bar", 0)) != RESULT_OK) {
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

	FILE *f = fopen("/./squashfs/testdir/../.././squashfs/testdir/./testfile", "rb");
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

	printf("Opening /sd through Unix\n");
	if (ls("/sd"))
		printf("WTF ERROR\n");
	if (ls("/sd/switch"))
		printf("WTF ERROR2\n");

	printf("Tryng to open file on sd\n");
	f = fopen("/sd/test.txt", "rb");
	if(f == NULL) {
		printf("fopen failure: %d\n", errno);
		return 1;
	}
	rd = fread(buf, sizeof(*buf), sizeof(buf)/sizeof(*buf), f);
	if(rd == 0) {
		printf("fread failure\n");
		return 1;
	}
	return 0;
}
