#include<libtransistor/nx.h>
#include<unistd.h>
#include<string.h>
#include<stdio.h>

#define ASSERT_OK(label, expr) if((r = expr) != RESULT_OK) {            \
		printf("assertion failed at %s:%d: result 0x%x is not OK\n", __FILE__, __LINE__, r); \
		goto label; \
	}

int main() {
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
	for (int it = 0; it < 100; it++) {
		ASSERT_OK(fail_dir, idirectory_read(root_dir, &out_entries, &entry, 1 * sizeof(idirectoryentry_t)));
		if (out_entries == 0);
			break;
		printf("Out entries = %lu\n", out_entries);
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
