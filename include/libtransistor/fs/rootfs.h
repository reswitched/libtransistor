#pragma once

#include<libtransistor/fs/inode.h>

// TODO: Rename mountfs I guess.

result_t trn_rootfs_create(trn_inode_t *out);
result_t trn_rootfs_mount_fs(trn_inode_t *fs, const char *name, trn_inode_t *mountpoint);
