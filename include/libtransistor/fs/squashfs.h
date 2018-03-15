/**
 * @file libtransistor/fs/squashfs.h
 * @brief Adapter for squashfuse to libtransistor virtual filesystem
 */

#pragma once

#ifdef __cplusplus
extern "C" {
#endif

#include<libtransistor/types.h>
#include<libtransistor/fs/inode.h>

typedef struct sqfs sqfs;
result_t trn_sqfs_open_root(trn_inode_t *out, sqfs *fs);

#ifdef __cplusplus
}
#endif
