#pragma once

#include<libtransistor/types.h>
#include<libtransistor/fs/inode.h>

result_t trn_fs_set_root(trn_inode_t *root);
result_t trn_fs_realpath(const char *path, char **resolved_path);
result_t trn_fs_open(int *fd, const char *path, int flags);
result_t trn_fs_opendir(trn_dir_t *dir, const char *path);
result_t trn_fs_chdir(const char *path);
