#include<libtransistor/err.h>
#include<libtransistor/fs/inode.h>
#include<libtransistor/fs/fs.h>

#include<stdio.h>
#include<string.h>

#define ASSERT_OK(label, expr) if((r = expr) != RESULT_OK) {            \
		printf("assertion failed at %s:%d: result 0x%x is not OK\n", __FILE__, __LINE__, r); \
		goto label; \
	}

static result_t dir_is_dir(void *inode, bool *out) {
	*out = true;
	return RESULT_OK;
}

static result_t unsupp_open_as_dir(void *inode, trn_dir_t *out) {
	return LIBTRANSISTOR_ERR_UNIMPLEMENTED;
}

static result_t unsupp_open_as_file(void *inode, int mode, int *fd) {
	return LIBTRANSISTOR_ERR_UNIMPLEMENTED;
}

typedef struct {
	char path[256];
} dummy_inode_t;

static result_t dummy_inode_release(void *data) {
	dummy_inode_t *inode = data;
	printf("releasing %s (%p)\n", inode->path, inode);
	free(inode);
	return RESULT_OK;
}

static result_t dummy_inode_lookup(void *data, trn_inode_t *out, const char *name, size_t name_length) {
	dummy_inode_t *inode = data;

	printf("attempt to open %.*s under %s (%p)\n", name_length, name, inode->path, inode);
	
	dummy_inode_t *child_data = malloc(sizeof(*child_data));
	if(child_data == NULL) {
		return LIBTRANSISTOR_ERR_OUT_OF_MEMORY;
	}

	static trn_inode_ops_t dummy_ops = {
		.is_dir = dir_is_dir,
		.lookup = dummy_inode_lookup,
		.release = dummy_inode_release,
		.open_as_file = unsupp_open_as_file,
		.open_as_dir = unsupp_open_as_dir,
	};
	
	out->data = child_data;
	out->ops = &dummy_ops;

	strncpy(child_data->path, inode->path, sizeof(child_data->path));
	int l = strlen(child_data->path);
	// I know this could be OOB but I don't really care
	child_data->path[l] = '/';
	strncpy(child_data->path + l + 1, name, name_length);

	printf("opened %s -> %p\n", child_data->path, child_data);
	
	return RESULT_OK;
}

static result_t root_inode_release(void *inode) {
	printf("root inode released!?\n");
	exit(1);
	return LIBTRANSISTOR_ERR_UNSPECIFIED;
}

int main(int argc, char *argv[]) {
	result_t r;
	
	trn_inode_ops_t root_inode_ops = {
		.is_dir = dir_is_dir,
		.lookup = dummy_inode_lookup,
		.release = root_inode_release,
		.open_as_file = unsupp_open_as_file,
		.open_as_dir = unsupp_open_as_dir,
	};

	dummy_inode_t root_data;
	strcpy(root_data.path, "");
	
	trn_inode_t root_inode = {
		.data = &root_data,
		.ops = &root_inode_ops
	};
	
	ASSERT_OK(fail, trn_fs_set_root(&root_inode));

	char *resolved_path = NULL;
	ASSERT_OK(fail, trn_fs_realpath("/foo/bar/../baz", &resolved_path));
	printf("realpath -> %s\n", resolved_path);

	ASSERT_OK(fail, trn_fs_chdir("/a/b/c/"));
	printf("chdir'd\n");
	ASSERT_OK(fail, trn_fs_realpath("../c/foo/bar/../baz", &resolved_path));
	printf("realpath -> %s\n", resolved_path);
	
	return 0;
fail:
	return 1;
}
