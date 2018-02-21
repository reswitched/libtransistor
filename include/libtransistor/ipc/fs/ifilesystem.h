/**
 * @file libtransistor/ipc/fs/ifilesystem.h
 * @brief IFileSystem bindings
 */


#pragma once

#include <libtransistor/types.h>
#include <libtransistor/ipc/fs/ifile.h>
#include <libtransistor/ipc/fs/idirectory.h>

typedef ipc_object_t ifilesystem_t;

// TODO: Codegen structs

result_t ifilesystem_create_file(ifilesystem_t obj, uint64_t in_mode, uint32_t in_size, const uint8_t in_path[0x301]);
result_t ifilesystem_delete_file(ifilesystem_t obj, const uint8_t in_path[0x301]);
result_t ifilesystem_create_directory(ifilesystem_t obj, const uint8_t in_path[0x301]);
result_t ifilesystem_delete_directory(ifilesystem_t obj, const uint8_t in_path[0x301]);
result_t ifilesystem_delete_directory_recursively(ifilesystem_t obj, const uint8_t in_path[0x301]);
result_t ifilesystem_rename_file(ifilesystem_t obj, const uint8_t in_oldPath[0x301], const uint8_t in_newPath[0x301]);
result_t ifilesystem_rename_directory(ifilesystem_t obj, const uint8_t in_oldPath[0x301], const uint8_t in_newPath[0x301]);
result_t ifilesystem_get_entry_type(ifilesystem_t obj, uint32_t *out_unk1, const uint8_t in_path[0x301]);
result_t ifilesystem_open_file(ifilesystem_t obj, ifile_t *out_file, uint32_t in_mode, const uint8_t in_path[0x301]);
result_t ifilesystem_open_directory(ifilesystem_t obj, idirectory_t *out_directory, uint32_t in_unk0, const uint8_t in_path[0x301]);
result_t ifilesystem_commit(ifilesystem_t obj);
result_t ifilesystem_get_free_space_size(ifilesystem_t obj, uint64_t *out_totalFreeSpace, const uint8_t in_path[0x301]);
result_t ifilesystem_get_total_space_size(ifilesystem_t obj, uint64_t *out_totalSize, const uint8_t in_path[0x301]);
result_t ifilesystem_clean_directory_recursively(ifilesystem_t obj, const uint8_t in_path[0x301]);
result_t ifilesystem_get_file_time_stamp_raw(ifilesystem_t obj, uint8_t out_timestamp[0x20], const uint8_t in_path[0x301]);
