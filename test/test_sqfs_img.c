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
#include<string.h>

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

	printf("Creating test directory\n");
	if (mkdir("/sd/test_dir", 0777) == -1 && errno != EEXIST) {
		printf("mkdir failure: %d\n", errno);
		return 1;
	}

	printf("Trying to write file on sd\n");
	char *msg = "This is a cute test\n";
	f = fopen("/sd/test_dir/test.txt", "wb");
	if (f == NULL) {
		printf("fopen failure: %d\n", errno);
		return 1;
	}
	rd = fwrite(msg, 1, strlen(msg), f);
	if(rd == 0) {
		printf("fwrite failure\n");
		return 1;
	}
	fclose(f);

	printf("Opening /sd through Unix\n");
	if (ls("/sd"))
		printf("WTF ERROR\n");
	if (ls("/sd/switch"))
		printf("WTF ERROR2\n");

	printf("Tryng to open file on sd\n");
	f = fopen("/sd/test_dir/test.txt", "rb");
	if(f == NULL) {
		printf("fopen failure: %d\n", errno);
		return 1;
	}
	rd = fread(buf, sizeof(*buf), sizeof(buf)/sizeof(*buf), f);
	if(rd == 0) {
		printf("fread failure\n");
		return 1;
	}
	fclose(f);
	if (strncmp(buf, "This is a cute test\n", sizeof(*buf)) != 0)
		printf("We read something different!\n");

	printf("Attempting to append to file!\n");
	fd = open("/sd/test_dir/test.txt", O_WRONLY | O_APPEND);
	msg = "And this is a cute append\n";
	if (write(fd, msg, sizeof(msg)) <= 0)
		printf("Failed to write! %d\n", errno);
	close(fd);
	f = fopen("/sd/test_dir/test.txt", "rb");
	if(f == NULL) {
		printf("fopen failure: %d\n", errno);
		return 1;
	}
	rd = fread(buf, sizeof(*buf), sizeof(buf)/sizeof(*buf), f);
	if(rd == 0) {
		printf("fread failure\n");
		return 1;
	}
	fclose(f);
	if (strncmp(buf, "This is a cute test\nAnd this is a cute append\n", rd) != 0) {
		printf("We read something different!\n");
		return 1;
	}

	printf("Finally, let's do a truncating open!\n");
	fd = open("/sd/test_dir/test.txt", O_WRONLY | O_TRUNC);
	msg = "A cute truncation now\n";
	if (write(fd, msg, sizeof(msg)) <= 0) {
		printf("Failed to write! %d\n", errno);
		return 1;
	}
	close(fd);
	f = fopen("/sd/test_dir/test.txt", "rb");
	if(f == NULL) {
		printf("fopen failure: %d\n", errno);
		return 1;
	}
	rd = fread(buf, sizeof(*buf), sizeof(buf)/sizeof(*buf), f);
	if(rd == 0) {
		printf("fread failure\n");
		return 1;
	}
	fclose(f);
	if (strncmp(buf, "A cute truncation now\n", rd) != 0) {
		printf("We read something different! %.*s\n", rd, buf);
		return 1;
	}

	printf("Delete a file now\n");
	if (unlink("/sd/test_dir/test.txt") == -1) {
		printf("Error deleting file: %d\n", errno);
		return 1;
	}

	struct stat _stat;

	// Make sure the file is deleted by stating it and making sure it returns
	// ENOENT
	if (stat("/sd/test_dir/test.txt", &_stat) != -1 || errno != ENOENT) {
		printf("File was not *actually* deleted! %d\n", errno);
		return 1;
	}

	printf("Ensure we fail deleting a non-empty directory\n");
	fd = open("/sd/test_dir/empty", O_CREAT | O_RDWR);
	if (fd < 0) {
		printf("Failed to create file! %d\n", errno);
		return 1;
	}
	close(fd);
	if (rmdir("/sd/test_dir") == 0 || errno != ENOTEMPTY) {
		printf("Failed to fail to delete directory!\n");
		return 1;
	}
	if (unlink("/sd/test_dir/empty") < 0) {
		printf("Error deleting file: %d\n", errno);
		return 1;
	}
	printf("Ensure we can delete a directory\n");
	if (rmdir("/sd/test_dir") == -1) {
		printf("Failed to delete directory! %d\n", errno);
		return 1;
	}
	if (stat("/sd/test_dir", &_stat) != -1 || errno != ENOENT) {
		printf("Directory was not *actually* deleted! %d\n", errno);
		return 1;
	}
	return 0;
}
