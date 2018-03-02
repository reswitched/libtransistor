/**
 * @file libtransistor/fs/fspfs.h
 * @brief FSP-SRV based filesystem
 *
 * The Nintendo Switch has a service called `fsp-srv` which is in charge of 
 * providing apps with whatever filesystem they might need. For instance, you
 * might ask fsp-srv to give you a filesystem for the SD Card, or for the Game
 * Cartridge, etc...
 *
 * All those filesystem implement the same IPC interface: IFilesystem. FSPFS is
 * then responsible for wrapping this IPC Interface and providing a
 * libtransistor mountpoint to access it. This is the mechanism used by
 * libtransistor to mount the SDCard filesystem in /sd by default.
 */

#pragma once

#include<libtransistor/types.h>
#include<libtransistor/fs/inode.h>
#include<libtransistor/ipc/fs/ifilesystem.h>

/**
 * @brief Create an FSPFS filesystem
 *
 * This takes an `ifilesystem_t` (that you'll need to have initialized
 * beforehand), and wraps it in a libtransistor filesystem.
 *
 * Note that the ownership of the ifilesystem_t is transfered to the fspfs!
 * When the filesystem is released, it will automatically close the
 * ifilesystem_t handle.
 */
result_t trn_fspfs_create(trn_inode_t *out, ifilesystem_t fs);
