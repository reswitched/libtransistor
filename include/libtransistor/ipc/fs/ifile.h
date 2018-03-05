/**
 * @file libtransistor/ipc/fs/ifile.h
 * @brief File
 */

#pragma once

#include <libtransistor/types.h>
#include <libtransistor/ipc.h>

typedef ipc_object_t ifile_t;

// TODO: Codegen structs

result_t ifile_read(ifile_t obj, uint64_t *out_out_size, int8_t * out_out_buf, size_t out_out_buf_size, uint64_t in_unk0, uint64_t in_offset, uint64_t in_size);
result_t ifile_write(ifile_t obj, uint32_t in_unk0, uint64_t in_offset, uint64_t in_size, const int8_t * in_buf, size_t in_buf_size);
result_t ifile_flush(ifile_t obj);
result_t ifile_set_size(ifile_t obj, uint64_t in_size);
result_t ifile_get_size(ifile_t obj, uint64_t *out_fileSize);
