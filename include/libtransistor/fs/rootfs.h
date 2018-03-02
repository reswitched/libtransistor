/**
 * @file libtransistor/fs/rootfs.h
 * @brief Root Filesystem
 *
 * A RootFS is a pseudo-filesystem capable of mounting other filesystems in it.
 * In libtransistor, this is the default filesystem for the root directory. The
 * RootFS is organized as a single folder containing one subfolder for each
 * mounted filesystem.
 */
#pragma once

#include<libtransistor/fs/inode.h>

// TODO: Rename mountfs I guess.

/**
 * @brief Create a rootfs filesystem
 */
result_t trn_rootfs_create(trn_inode_t *out);


/**
 * @brief Mount a filesystem in the RootFS
 *
 * The given filesystem will then be made available in a folder of the given
 * name. Note that it is *not* possible to have hierarchies in the rootfs: all
 * filesystems have to be mounted directly at the root of the RootFS.
 *
 * This takes ownership of the passed trn_inode_t: it will call the close
 * release method automatically when the rootfs itself is released.
 */
result_t trn_rootfs_mount_fs(trn_inode_t *fs, const char *name, trn_inode_t *mountpoint);
