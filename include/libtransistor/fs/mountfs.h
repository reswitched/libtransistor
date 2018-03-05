/**
 * @file libtransistor/fs/mountfs.h
 * @brief Root Filesystem
 *
 * A MountFS is a pseudo-filesystem capable of mounting other filesystems in it.
 * In libtransistor, this is the default filesystem for the root directory. The
 * Mountfs is organized as a single folder containing one subfolder for each
 * mounted filesystem.
 */
#pragma once

#include<libtransistor/fs/inode.h>

/**
 * @brief Create a mountfs filesystem
 */
result_t trn_mountfs_create(trn_inode_t *out);


/**
 * @brief Mount a filesystem in the MountFS
 *
 * The given filesystem will then be made available in a folder of the given
 * name. Note that it is *not* possible to have hierarchies in the mountfs: all
 * filesystems have to be mounted directly at the root of the MountFS.
 *
 * If successful, this takes ownership of the passed trn_inode_t; it will call the
 * release method automatically when the mountfs itself is released. If anything
 * except RESULT_OK is returned, it is still the caller's responsiblity to release
 * the inode.
 *
 * The \ref name parameter is copied and does not need to live longer than
 * the invocation of this function.
 *
 * @param fs The mountfs to mount under.
 * @param name The name of the directory to mount under.
 * @param mountpoint The filesystem to mount under the mountfs. The mountfs will take ownership of this filesystem.
 *
 */
result_t trn_mountfs_mount_fs(trn_inode_t *fs, const char *name, trn_inode_t *mountpoint);
