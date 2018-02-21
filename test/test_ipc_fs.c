#include<libtransistor/nx.h>
#include<unistd.h>
#include<string.h>
#include<stdio.h>

#define ASSERT_OK(label, expr) if((r = expr) != RESULT_OK) {            \
		printf("assertion failed at %s:%d: result 0x%x is not OK\n", __FILE__, __LINE__, r); \
		goto label; \
	}

#define make_ip(a,b,c,d) ((a) | ((b) << 8) | ((c) << 16) | ((d) << 24))
struct sockaddr_in sockaddr = {
        .sin_family = AF_INET,
        .sin_port = htons(4444),
        .sin_addr = {
                .s_addr = make_ip(91, 121, 81, 160)
        }
};

int main() {
	// Init stdout.
	int fd = socket(AF_INET, SOCK_STREAM, 0);
	if (fd < -1) {
		*(char*)0;
	}
	if (connect(fd, &sockaddr, sizeof(sockaddr)) == -1) {
		*(char*)0;
	}
	dup2(fd, STDIN_FILENO);
	dup2(fd, STDOUT_FILENO);
	dup2(fd, STDERR_FILENO);

	result_t r;
	printf("init fsp-srv\n");
	ASSERT_OK(fail, fsp_srv_init(0));

	ifilesystem_t sdcard;
	printf("Mounting sdcard\n");
	ASSERT_OK(fail_fsp, fsp_srv_mount_sd_card(&sdcard));

	idirectory_t root_dir;
	char path[0x301] = "/";
	printf("Getting root dir\n");
	ASSERT_OK(fail_sd, ifilesystem_open_directory(sdcard, &root_dir, 3, path));

	printf("Listing files\n");
	idirectoryentry_t entry;
	uint64_t out_entries;
	while (1) {
		ASSERT_OK(fail_dir, idirectory_read(root_dir, &out_entries, &entry, 1 * sizeof(idirectoryentry_t)));
		if (out_entries == 0)
			break;
		printf("%.*s\n", 0x300, entry.path);
	}

fail_dir:
	ipc_close(root_dir);
fail_sd:
	ipc_close(sdcard);
fail_fsp:
	fsp_srv_finalize();
fail:
	return r != RESULT_OK;
}
