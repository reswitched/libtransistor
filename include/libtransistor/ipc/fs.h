/**
 * @file libtransistor/ipc/fs.h
 * @brief File System
 */

#pragma once

#ifdef __cplusplus
extern "C" {
#endif

#include <libtransistor/types.h>
#include <libtransistor/ipc/fs/ifilesystem.h>
#include <libtransistor/ipc/fs/ifile.h>
#include <libtransistor/ipc/fs/idirectory.h>

// TODO: Codegen structs


result_t fsp_srv_init(uint64_t in_unk0);
void fsp_srv_finalize();
// result_t fsp_srv_mount_content(ifilesystem_t *out_contentFs, applicationid in_tid, uint32_t in_flag, const int8_t * in_path);
result_t fsp_srv_open_data_file_system_by_current_process(ifilesystem_t *out_unk0);
// result_t fsp_srv_mount_content7(ifilesystem_t *out_unk2, applicationid in_tid, uint32_t in_ncaType);
// result_t fsp_srv_mount_content(ifilesystem_t *out_contentFs, applicationid in_tid, uint32_t in_flag, const uint8_t in_path[0x301]);
// result_t fsp_srv_open_data_file_system_by_application_id(ifilesystem_t *out_dataFiles, applicationid in_tid);
result_t fsp_srv_open_bis_filesystem(ifilesystem_t *fs, uint32_t partition_id, const char *path);
// result_t fsp_srv_open_bis_partition(ipc_object_t *out_BisPartition, partition in_partitionID);
result_t fsp_srv_invalidate_bis_cache();
result_t fsp_srv_open_host_file_system_impl(ifilesystem_t *out_unk1, const uint8_t in_path[0x301]);
result_t fsp_srv_mount_sd_card(ifilesystem_t *out_sdCard);
result_t fsp_srv_format_sd_card();
// result_t fsp_srv_delete_save_data(applicationid in_tid);
// result_t fsp_srv_create_save_data(savestruct in_saveStruct, savecreatestruct in_saveCreate, u128 in_input);
// result_t fsp_srv_create_system_save_data(savestruct in_saveStruct, savecreatestruct in_saveCreate);
// result_t fsp_srv_register_save_data_atomic_deletion(unknown in_unk0);
result_t fsp_srv_delete_save_data_with_space_id(uint8_t in_unk0, uint64_t in_unk1);
result_t fsp_srv_format_sd_card_dry_run();
result_t fsp_srv_is_ex_fat_supported(uint8_t *out_isSupported);
// result_t fsp_srv_open_game_card_partition(ipc_object_t *out_gameCardFs, partition in_partitionID, uint32_t in_unk1);
result_t fsp_srv_mount_game_card_partition(ifilesystem_t *out_gameCardPartitionFs, uint32_t in_unk0, uint32_t in_unk1);
result_t fsp_srv_extend_save_data(uint8_t in_unk0, uint64_t in_unk1, uint64_t in_unk2, uint64_t in_unk3);
// result_t fsp_srv_mount_save_data(ifilesystem_t *out_saveDataFs, uint8_t in_input, savestruct in_saveStruct);
// result_t fsp_srv_mount_system_save_data(ifilesystem_t *out_systemSaveDataFs, uint8_t in_input, savestruct in_saveStruct);
// result_t fsp_srv_mount_save_data_read_only(ifilesystem_t *out_saveDataFs, uint8_t in_input, savestruct in_saveStruct);
// result_t fsp_srv_read_save_data_file_system_extra_data_with_space_id(unknown *out_unk2, uint8_t in_unk0, uint64_t in_unk1);
// result_t fsp_srv_read_save_data_file_system_extra_data(unknown *out_unk1, uint64_t in_unk0);
// result_t fsp_srv_write_save_data_file_system_extra_data(uint64_t in_unk0, uint8_t in_unk1, unknown in_unk2);
// result_t fsp_srv_open_save_data_info_reader(ipc_object_t *out_unk0);
// result_t fsp_srv_open_save_data_iterator(ipc_object_t *out_unk1, uint8_t in_unk0);
result_t fsp_srv_open_save_data_thumbnail_file(ifile_t *out_thumbnail, uint8_t in_unk0, const uint8_t in_unk1[0x40], uint32_t in_unk2);
result_t fsp_srv_mount_image_directory(ifilesystem_t *out_imageFs, uint32_t in_unk0);
result_t fsp_srv_mount_content_storage(ifilesystem_t *out_contentFs, uint32_t in_contentStorageID);
// result_t fsp_srv_open_data_storage_by_current_process(ipc_object_t *out_dataStorage);
// result_t fsp_srv_open_data_storage_by_application_id(ipc_object_t *out_dataStorage, applicationid in_tid);
// result_t fsp_srv_open_data_storage_by_data_id(ipc_object_t *out_dataStorage, applicationid in_tid, uint8_t in_storageId);
// result_t fsp_srv_open_rom_storage(ipc_object_t *out_unk0);
// result_t fsp_srv_open_device_operator(ipc_object_t *out_unk0);
// result_t fsp_srv_open_sd_card_detection_event_notifier(ipc_object_t *out_SdEventNotify);
// result_t fsp_srv_open_game_card_detection_event_notifier(ipc_object_t *out_GameCardEventNotify);
result_t fsp_srv_set_current_posix_time(uint64_t in_time);
result_t fsp_srv_query_save_data_total_size(uint64_t *out_saveDataSize, uint64_t in_unk0, uint64_t in_unk1);
// result_t fsp_srv_verify_save_data(unknown *out_unk1, applicationid in_tid);
// result_t fsp_srv_corrupt_save_data_for_debug(applicationid in_tid);
result_t fsp_srv_create_padding_file(uint64_t in_size);
result_t fsp_srv_delete_all_padding_files();
// result_t fsp_srv_get_rights_id(u128 *out_rights, uint64_t in_unk0, uint8_t in_unk1);
// result_t fsp_srv_register_external_key(u128 in_unk0, u128 in_unk1);
result_t fsp_srv_unregister_external_key();
// result_t fsp_srv_get_rights_id_by_path(u128 *out_rights, const uint8_t in_path[0x301]);
// result_t fsp_srv_get_rights_id_by_path2(u128 *out_rights, uint8_t *out_unk2, const uint8_t in_path[0x301]);
// result_t fsp_srv_set_sd_card_encryption_seed(u128 in_seedmaybe);
result_t fsp_srv_get_and_clear_file_system_proxy_error_info(uint8_t out_errorInfo[0x80]);
result_t fsp_srv_set_bis_root_for_host(uint32_t in_unk0, const uint8_t in_path[0x301]);
result_t fsp_srv_set_save_data_size(uint64_t in_unk0, uint64_t in_unk1);
result_t fsp_srv_set_save_data_root_path(const uint8_t in_path[0x301]);
result_t fsp_srv_disable_auto_save_data_creation();
result_t fsp_srv_set_global_access_log_mode(uint32_t in_mode);
result_t fsp_srv_get_global_access_log_mode(uint32_t *out_logMode);
// result_t fsp_srv_output_access_log_to_sd_card(unknown in_logText);

#ifdef __cplusplus
}
#endif
