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
#include<sha256.h>

#include"../lib/squashfs/squashfuse.h"

void hash_file(char hash[32], int fd) {
	char buf[4096];
	ssize_t r;
	SHA256_CTX ctx;

	sha256_init(&ctx);
	while ((r = read(fd, buf, 4096)) > 0)
		sha256_update(&ctx, buf, r);
	sha256_final(&ctx, hash);
}


void tohex(unsigned char * in, size_t insz, char * out, size_t outsz)
{
	unsigned char * pin = in;
	const char * hex = "0123456789ABCDEF";
	char * pout = out;
	for(; pin < in+insz; pout +=2, pin++){
		pout[0] = hex[(*pin>>4) & 0xF];
		pout[1] = hex[ *pin     & 0xF];
		if (pout + 2 - out > outsz){
			/* Better to truncate output string than overflow buffer */
			/* it would be still better to either return a status */
			/* or ensure the target buffer is large enough and it never happen */
			break;
		}
	}
	pout[-1] = 0;
}

void print_file(char *name, int indent) {
	char hash[32];
	char hashstr[65];

	int fd = open(name, O_RDONLY);
	if (fd < 0) {
		perror("error: open");
		exit(1);
	}
	hash_file(hash, fd);
	tohex(hash, 32, hashstr, 65);
	printf("%*s- %s: %s\n", indent, "", name, hashstr);
}

int listdir(const char *name, int indent)
{
	DIR *dir;
	struct dirent *entry;
	struct stat file_stat;

	int ret = 0;
	
	if (!(dir = opendir(name)))
		return 1;

	while ((entry = readdir(dir)) != NULL) {
		char path[1024];
		if (strcmp(entry->d_name, ".") == 0 || strcmp(entry->d_name, "..") == 0)
			continue;
		snprintf(path, sizeof(path), "%s/%s", name, entry->d_name);

		// TODO: Implement d_type in dentry
		if (stat(path, &file_stat) == -1) {
			perror("Stat error");
			exit(1);
		}

		if (S_ISDIR(file_stat.st_mode)) {
			printf("%*s[%s]\n", indent, "", entry->d_name);
			ret|= listdir(path, indent + 2);
		} else {
			print_file(path, indent);
		}
	}
	closedir(dir);

	return ret;
}

// Read every file into a buffer.
int main(int argc, char *argv[]) {
	return listdir("/", 0);
}
