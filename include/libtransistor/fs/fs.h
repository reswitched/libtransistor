/**
 * @file libtransistor/fs/fs.h
 * @brief Functions to setup filesystem
 *
 * Libtransistor sports a virtual filesystem allowing to mount multiple kinds of
 * filesystem (such as a squashfs, a networked filesystem, or an fsp-srv
 * filesystem).
 *
 * The filesystem root is purely virtual: you may not create
 * files or directories directly under `/`. Instead, filesystems are mounted as
 * direct descendants to it (through the `trn_fs_mount_fs` function). For
 * instance, the canonical place to mount the SD card is `/sd`, which is done
 * by calling `trn_fs_mount_fs("/sd", sdcardfs)`.
 *
 * Anyone can create his own filesystem: they simply needs to create a struct of
 * type `trn_inode_t`. Libtransistor sports various filesystem implementations,
 * mainly one backed by the FSP-SRV server of the switch, allowing mounting the
 * sdcard, among other things.
 *
 * Note that while functions like `trn_fs_open` are defined, those should
 * probably *not* be used. Users should prefer instead to use the POSIX
 * functions of the same name. This is because the error values, result_t,
 * are not guaranteed to stay the same across filesystems.
 */

#pragma once

#ifdef __cplusplus
extern "C" {
#endif

#include<libtransistor/types.h>
#include<libtransistor/fs/inode.h>

#include<sys/stat.h>

/**
 * @brief Change filesystem root.
 *
 * In libtransistor, the default root filesystem is mountfs. That filesystem is
 * not very special: it's a filesystem containing only directories, each being
 * a mountpoint. However, this behavior might not fit what all application's
 * needs. For instance, when porting software, you might need to place some
 * files in certain locations, or just need more leeway in how the root fs
 * works. In these cases, you can use `trn_fs_set_root` to change what the root
 * filesystem implementation is.
 *
 * For instance, the following code will mount the sdcard at the root:
 *
 * @code{.c}
 * ifilesystem_t sdcard_ifs;
 * trn_inode_t sdcard_inode;
 *
 * fsp_srv_mount_sd_card(&sdcard_ifs);
 * trn_fspfs_create(&sdcard_inode, sdcard_ifs);
 * trn_fs_set_root(&sdcard_inode);
 * @endcode
 */
result_t trn_fs_set_root(trn_inode_t *new_root);

/**
 * @brief Mount a filesystem.
 *
 * Allows a user to mount a filesystem to the specified location. The location
 * should be a full path.
 *
 * Note that the current implementation is relatively simple: it forwards the
 * call to mount to the root filesystem - if it is a mountfs. If you have swapped
 * out the root filesystem with `trn_fs_set_root`, this will not work.
 *
 * You could mount the game card partition (assuming correct privilege) like so:
 *
 * @code{.c}
 * ifilesystem_t gamecard_ifs;
 * trn_inode_t gamecard_inode;
 *
 * fsp_srv_mount_game_card_partition(&gamecard_inode, 0, 0);
 * trn_fspfs_create(&gamecard_inode, gamecard_ifs);
 * trn_fs_mount("/gamecard", &gamecard_inode);
 * @endcode
 */
result_t trn_fs_mount(const char *name, trn_inode_t *root);

// The rest of those functions should probably not be directly used. Instead,
// use the standard posix calls of the same name...
// Maybe we should still document them
result_t trn_fs_realpath(const char *path, char **resolved_path);
result_t trn_fs_open(int *fd, const char *path, int flags);
result_t trn_fs_opendir(trn_dir_t *dir, const char *path);
result_t trn_fs_mkdir(const char *path);
result_t trn_fs_rename(const char *oldpath, const char *newpath);
result_t trn_fs_unlink(const char *path);
result_t trn_fs_rmdir(const char *path);
result_t trn_fs_chdir(const char *path);
result_t trn_fs_stat(const char *path, struct stat *st);

#ifdef __cplusplus
}
#endif
