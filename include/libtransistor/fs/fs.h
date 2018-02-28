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
 * Anyone can create his own filesystem: he simply needs to create a struct of
 * type `trn_inode_t`.
 */

#pragma once

#include<libtransistor/types.h>
#include<libtransistor/fs/inode.h>

#include<sys/stat.h>

// FS are mounted
result_t trn_fs_set_root(trn_inode_t *new_root) __attribute__((deprecated));
result_t trn_fs_mount(const char *name, trn_inode_t *root);
result_t trn_fs_realpath(const char *path, char **resolved_path);
result_t trn_fs_open(int *fd, const char *path, int flags);
result_t trn_fs_opendir(trn_dir_t *dir, const char *path);
result_t trn_fs_mkdir(const char *path);
result_t trn_fs_chdir(const char *path);
result_t trn_fs_stat(const char *path, struct stat *st);
