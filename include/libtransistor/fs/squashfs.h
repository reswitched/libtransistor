#pragma once

#include<libtransistor/types.h>
#include<libtransistor/fs/inode.h>
#include<squashfuse.h>

result_t trn_sqfs_open_root(trn_inode_t *out, sqfs *fs);
