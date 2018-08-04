#include<libtransistor/types.h>
#include<libtransistor/svc.h>
#include<libtransistor/ipc.h>
#include<libtransistor/ipc_helpers.h>
#include<libtransistor/err.h>
#include<libtransistor/util.h>
#include<libtransistor/ipc/sm.h>
#include<libtransistor/ipc/fs.h>
#include<string.h>

static ipc_object_t fsp_srv_object;
static int fsp_srv_initializations = 0;

result_t fsp_srv_init(uint64_t in_unk0) {
	if(fsp_srv_initializations++ > 0) {
		return RESULT_OK;
	}

	result_t res;
	res = sm_init();
	if (res != RESULT_OK) {
		goto fail;
	}

	res = sm_get_service(&fsp_srv_object, "fsp-srv");
	if (res != RESULT_OK) {
		goto fail_sm;
	}

	sm_finalize();

	ipc_request_t rq = ipc_default_request;
	rq.request_id = 1;

	uint8_t raw[8];
	rq.raw_data = raw;
	rq.raw_data_size = 8;

	*(uint64_t*)(raw + 0) = in_unk0;
	rq.send_pid = true;


	ipc_response_fmt_t rs = ipc_default_response_fmt;
	res = ipc_send(fsp_srv_object, &rq, &rs);
	if (res != RESULT_OK) {
		goto fail;
	}
	return RESULT_OK;
fail_sm:
	sm_finalize();
fail:
	fsp_srv_initializations--;
	return res;
}
static void fsp_srv_force_finalize() {
	ipc_close(fsp_srv_object);
	fsp_srv_initializations = 0;
}
void fsp_srv_finalize() {
	if(--fsp_srv_initializations == 0) {
		fsp_srv_force_finalize();
	}
}
static __attribute__((destructor)) void fsp_srv_destruct() {
	if(fsp_srv_initializations > 0) {
		fsp_srv_force_finalize();
	}
}

// result_t fsp_srv_mount_content(ifilesystem_t *out_contentFs, applicationid in_tid, uint32_t in_flag, const int8_t * in_path);

result_t fsp_srv_open_data_file_system_by_current_process(ifilesystem_t *out_unk0) {
	result_t res;
	ipc_request_t rq = ipc_default_request;
	rq.request_id = 2;

	ipc_response_fmt_t rs = ipc_default_response_fmt;
	rs.objects = out_unk0;
	rs.num_objects = 1;


	res = ipc_send(fsp_srv_object, &rq, &rs);
	return res;
}

// result_t fsp_srv_mount_content7(ifilesystem_t *out_unk2, applicationid in_tid, uint32_t in_ncaType);

// result_t fsp_srv_mount_content(ifilesystem_t *out_contentFs, applicationid in_tid, uint32_t in_flag, const uint8_t in_path[0x301]);

// result_t fsp_srv_open_data_file_system_by_application_id(ifilesystem_t *out_dataFiles, applicationid in_tid);

result_t fsp_srv_open_bis_filesystem(ifilesystem_t *fs, uint32_t partition_id, const char *in_path) {
	char path[0x301];
	memset(path, 0, sizeof(path));
	strncpy(path, in_path, sizeof(path)-1);
	
	ipc_buffer_t buffers[] = {
		ipc_make_buffer(path, 0x301, 0x19)
	};
	
	ipc_request_t rq = ipc_make_request(11);
	ipc_msg_set_buffers(rq, buffers, buffer_ptrs);
	ipc_msg_raw_data_from_value(rq, partition_id);

	ipc_response_fmt_t rs = ipc_default_response_fmt;
	rs.objects = fs;
	rs.num_objects = 1;

	return ipc_send(fsp_srv_object, &rq, &rs);
}

// result_t fsp_srv_open_bis_partition(ipc_object_t *out_BisPartition, partition in_partitionID);

result_t fsp_srv_invalidate_bis_cache() {
	result_t res;
	ipc_request_t rq = ipc_default_request;
	rq.request_id = 13;

	ipc_response_fmt_t rs = ipc_default_response_fmt;
	res = ipc_send(fsp_srv_object, &rq, &rs);
	return res;
}

result_t fsp_srv_open_host_file_system_impl(ifilesystem_t *out_unk1, const uint8_t in_path[0x301]) {
	result_t res;
	ipc_request_t rq = ipc_default_request;
	rq.request_id = 17;

	ipc_buffer_t in_path_buf = {
		.addr = (void*) in_path,
		.size = 769,
		.type = 25,
	};


	ipc_response_fmt_t rs = ipc_default_response_fmt;
	rs.objects = out_unk1;
	rs.num_objects = 1;


	ipc_buffer_t *buffers[] = {
		&in_path_buf
	};
	rq.num_buffers = 1;
	rq.buffers = buffers;

	res = ipc_send(fsp_srv_object, &rq, &rs);
	return res;
}

result_t fsp_srv_mount_sd_card(ifilesystem_t *out_sdCard) {
	result_t res;
	ipc_request_t rq = ipc_default_request;
	rq.request_id = 18;

	ipc_response_fmt_t rs = ipc_default_response_fmt;
	rs.objects = out_sdCard;
	rs.num_objects = 1;


	res = ipc_send(fsp_srv_object, &rq, &rs);
	return res;
}

result_t fsp_srv_format_sd_card() {
	result_t res;
	ipc_request_t rq = ipc_default_request;
	rq.request_id = 19;

	ipc_response_fmt_t rs = ipc_default_response_fmt;
	res = ipc_send(fsp_srv_object, &rq, &rs);
	return res;
}

// result_t fsp_srv_delete_save_data(applicationid in_tid);

// result_t fsp_srv_create_save_data(savestruct in_saveStruct, savecreatestruct in_saveCreate, u128 in_input);

// result_t fsp_srv_create_system_save_data(savestruct in_saveStruct, savecreatestruct in_saveCreate);

// result_t fsp_srv_register_save_data_atomic_deletion(unknown in_unk0);

result_t fsp_srv_delete_save_data_with_space_id(uint8_t in_unk0, uint64_t in_unk1) {
	result_t res;
	ipc_request_t rq = ipc_default_request;
	rq.request_id = 25;

	uint8_t raw[9];
	rq.raw_data = raw;
	rq.raw_data_size = 9;

	*(uint8_t*)(raw + 0) = in_unk0;
	*(uint64_t*)(raw + 1) = in_unk1;


	ipc_response_fmt_t rs = ipc_default_response_fmt;
	res = ipc_send(fsp_srv_object, &rq, &rs);
	return res;
}

result_t fsp_srv_format_sd_card_dry_run() {
	result_t res;
	ipc_request_t rq = ipc_default_request;
	rq.request_id = 26;

	ipc_response_fmt_t rs = ipc_default_response_fmt;
	res = ipc_send(fsp_srv_object, &rq, &rs);
	return res;
}

result_t fsp_srv_is_ex_fat_supported(uint8_t *out_isSupported) {
	result_t res;
	ipc_request_t rq = ipc_default_request;
	rq.request_id = 27;

	ipc_response_fmt_t rs = ipc_default_response_fmt;
	uint8_t output_raw[1];
	rs.raw_data = output_raw;
	rs.raw_data_size = 1;

	res = ipc_send(fsp_srv_object, &rq, &rs);
	*out_isSupported = *(uint8_t*)(output_raw + 0);

	return res;
}

// result_t fsp_srv_open_game_card_partition(ipc_object_t *out_gameCardFs, partition in_partitionID, uint32_t in_unk1);

result_t fsp_srv_mount_game_card_partition(ifilesystem_t *out_gameCardPartitionFs, uint32_t in_unk0, uint32_t in_unk1) {
	result_t res;
	ipc_request_t rq = ipc_default_request;
	rq.request_id = 31;

	uint8_t raw[8];
	rq.raw_data = raw;
	rq.raw_data_size = 8;

	*(uint32_t*)(raw + 0) = in_unk0;
	*(uint32_t*)(raw + 4) = in_unk1;


	ipc_response_fmt_t rs = ipc_default_response_fmt;
	rs.objects = out_gameCardPartitionFs;
	rs.num_objects = 1;


	res = ipc_send(fsp_srv_object, &rq, &rs);
	return res;
}

result_t fsp_srv_extend_save_data(uint8_t in_unk0, uint64_t in_unk1, uint64_t in_unk2, uint64_t in_unk3) {
	result_t res;
	ipc_request_t rq = ipc_default_request;
	rq.request_id = 32;

	uint8_t raw[25];
	rq.raw_data = raw;
	rq.raw_data_size = 25;

	*(uint8_t*)(raw + 0) = in_unk0;
	*(uint64_t*)(raw + 1) = in_unk1;
	*(uint64_t*)(raw + 9) = in_unk2;
	*(uint64_t*)(raw + 17) = in_unk3;


	ipc_response_fmt_t rs = ipc_default_response_fmt;
	res = ipc_send(fsp_srv_object, &rq, &rs);
	return res;
}

// result_t fsp_srv_mount_save_data(ifilesystem_t *out_saveDataFs, uint8_t in_input, savestruct in_saveStruct);

// result_t fsp_srv_mount_system_save_data(ifilesystem_t *out_systemSaveDataFs, uint8_t in_input, savestruct in_saveStruct);

// result_t fsp_srv_mount_save_data_read_only(ifilesystem_t *out_saveDataFs, uint8_t in_input, savestruct in_saveStruct);

// result_t fsp_srv_read_save_data_file_system_extra_data_with_space_id(unknown *out_unk2, uint8_t in_unk0, uint64_t in_unk1);

// result_t fsp_srv_read_save_data_file_system_extra_data(unknown *out_unk1, uint64_t in_unk0);

// result_t fsp_srv_write_save_data_file_system_extra_data(uint64_t in_unk0, uint8_t in_unk1, unknown in_unk2);

// result_t fsp_srv_open_save_data_info_reader(ipc_object_t *out_unk0);

// result_t fsp_srv_open_save_data_iterator(ipc_object_t *out_unk1, uint8_t in_unk0);

result_t fsp_srv_open_save_data_thumbnail_file(ifile_t *out_thumbnail, uint8_t in_unk0, const uint8_t in_unk1[0x40], uint32_t in_unk2) {
	result_t res;
	ipc_request_t rq = ipc_default_request;
	rq.request_id = 80;

	uint8_t raw[69];
	rq.raw_data = raw;
	rq.raw_data_size = 69;

	*(uint8_t*)(raw + 0) = in_unk0;
	memcpy(raw + 1, in_unk1, 64);
	*(uint32_t*)(raw + 65) = in_unk2;


	ipc_response_fmt_t rs = ipc_default_response_fmt;
	rs.objects = out_thumbnail;
	rs.num_objects = 1;


	res = ipc_send(fsp_srv_object, &rq, &rs);
	return res;
}

result_t fsp_srv_mount_image_directory(ifilesystem_t *out_imageFs, uint32_t in_unk0) {
	result_t res;
	ipc_request_t rq = ipc_default_request;
	rq.request_id = 100;

	uint8_t raw[4];
	rq.raw_data = raw;
	rq.raw_data_size = 4;

	*(uint32_t*)(raw + 0) = in_unk0;


	ipc_response_fmt_t rs = ipc_default_response_fmt;
	rs.objects = out_imageFs;
	rs.num_objects = 1;


	res = ipc_send(fsp_srv_object, &rq, &rs);
	return res;
}

result_t fsp_srv_mount_content_storage(ifilesystem_t *out_contentFs, uint32_t in_contentStorageID) {
	result_t res;
	ipc_request_t rq = ipc_default_request;
	rq.request_id = 110;

	uint8_t raw[4];
	rq.raw_data = raw;
	rq.raw_data_size = 4;

	*(uint32_t*)(raw + 0) = in_contentStorageID;


	ipc_response_fmt_t rs = ipc_default_response_fmt;
	rs.objects = out_contentFs;
	rs.num_objects = 1;


	res = ipc_send(fsp_srv_object, &rq, &rs);
	return res;
}

// result_t fsp_srv_open_data_storage_by_current_process(ipc_object_t *out_dataStorage);

// result_t fsp_srv_open_data_storage_by_application_id(ipc_object_t *out_dataStorage, applicationid in_tid);

// result_t fsp_srv_open_data_storage_by_data_id(ipc_object_t *out_dataStorage, applicationid in_tid, uint8_t in_storageId);

// result_t fsp_srv_open_rom_storage(ipc_object_t *out_unk0);

// result_t fsp_srv_open_device_operator(ipc_object_t *out_unk0);

// result_t fsp_srv_open_sd_card_detection_event_notifier(ipc_object_t *out_SdEventNotify);

// result_t fsp_srv_open_game_card_detection_event_notifier(ipc_object_t *out_GameCardEventNotify);

result_t fsp_srv_set_current_posix_time(uint64_t in_time) {
	result_t res;
	ipc_request_t rq = ipc_default_request;
	rq.request_id = 600;

	uint8_t raw[8];
	rq.raw_data = raw;
	rq.raw_data_size = 8;

	*(uint64_t*)(raw + 0) = in_time;


	ipc_response_fmt_t rs = ipc_default_response_fmt;
	res = ipc_send(fsp_srv_object, &rq, &rs);
	return res;
}

result_t fsp_srv_query_save_data_total_size(uint64_t *out_saveDataSize, uint64_t in_unk0, uint64_t in_unk1) {
	result_t res;
	ipc_request_t rq = ipc_default_request;
	rq.request_id = 601;

	uint8_t raw[16];
	rq.raw_data = raw;
	rq.raw_data_size = 16;

	*(uint64_t*)(raw + 0) = in_unk0;
	*(uint64_t*)(raw + 8) = in_unk1;


	ipc_response_fmt_t rs = ipc_default_response_fmt;
	uint8_t output_raw[8];
	rs.raw_data = output_raw;
	rs.raw_data_size = 8;

	res = ipc_send(fsp_srv_object, &rq, &rs);
	*out_saveDataSize = *(uint64_t*)(output_raw + 0);

	return res;
}

// result_t fsp_srv_verify_save_data(unknown *out_unk1, applicationid in_tid);

// result_t fsp_srv_corrupt_save_data_for_debug(applicationid in_tid);

result_t fsp_srv_create_padding_file(uint64_t in_size) {
	result_t res;
	ipc_request_t rq = ipc_default_request;
	rq.request_id = 604;

	uint8_t raw[8];
	rq.raw_data = raw;
	rq.raw_data_size = 8;

	*(uint64_t*)(raw + 0) = in_size;


	ipc_response_fmt_t rs = ipc_default_response_fmt;
	res = ipc_send(fsp_srv_object, &rq, &rs);
	return res;
}

result_t fsp_srv_delete_all_padding_files() {
	result_t res;
	ipc_request_t rq = ipc_default_request;
	rq.request_id = 605;

	ipc_response_fmt_t rs = ipc_default_response_fmt;
	res = ipc_send(fsp_srv_object, &rq, &rs);
	return res;
}

// result_t fsp_srv_get_rights_id(u128 *out_rights, uint64_t in_unk0, uint8_t in_unk1);

// result_t fsp_srv_register_external_key(u128 in_unk0, u128 in_unk1);

result_t fsp_srv_unregister_external_key() {
	result_t res;
	ipc_request_t rq = ipc_default_request;
	rq.request_id = 608;

	ipc_response_fmt_t rs = ipc_default_response_fmt;
	res = ipc_send(fsp_srv_object, &rq, &rs);
	return res;
}

// result_t fsp_srv_get_rights_id_by_path(u128 *out_rights, const uint8_t in_path[0x301]);

// result_t fsp_srv_get_rights_id_by_path2(u128 *out_rights, uint8_t *out_unk2, const uint8_t in_path[0x301]);

// result_t fsp_srv_set_sd_card_encryption_seed(u128 in_seedmaybe);

result_t fsp_srv_get_and_clear_file_system_proxy_error_info(uint8_t out_errorInfo[0x80]) {
	result_t res;
	ipc_request_t rq = ipc_default_request;
	rq.request_id = 800;

	ipc_response_fmt_t rs = ipc_default_response_fmt;
	uint8_t output_raw[128];
	rs.raw_data = output_raw;
	rs.raw_data_size = 128;

	res = ipc_send(fsp_srv_object, &rq, &rs);
	memcpy(out_errorInfo, output_raw + 0, 128);

	return res;
}

result_t fsp_srv_set_bis_root_for_host(uint32_t in_unk0, const uint8_t in_path[0x301]) {
	result_t res;
	ipc_request_t rq = ipc_default_request;
	rq.request_id = 1000;

	uint8_t raw[4];
	rq.raw_data = raw;
	rq.raw_data_size = 4;

	*(uint32_t*)(raw + 0) = in_unk0;
	ipc_buffer_t in_path_buf = {
		.addr = (void*) in_path,
		.size = 769,
		.type = 25,
	};


	ipc_response_fmt_t rs = ipc_default_response_fmt;
	ipc_buffer_t *buffers[] = {
		&in_path_buf
	};
	rq.num_buffers = 1;
	rq.buffers = buffers;

	res = ipc_send(fsp_srv_object, &rq, &rs);
	return res;
}

result_t fsp_srv_set_save_data_size(uint64_t in_unk0, uint64_t in_unk1) {
	result_t res;
	ipc_request_t rq = ipc_default_request;
	rq.request_id = 1001;

	uint8_t raw[16];
	rq.raw_data = raw;
	rq.raw_data_size = 16;

	*(uint64_t*)(raw + 0) = in_unk0;
	*(uint64_t*)(raw + 8) = in_unk1;


	ipc_response_fmt_t rs = ipc_default_response_fmt;
	res = ipc_send(fsp_srv_object, &rq, &rs);
	return res;
}

result_t fsp_srv_set_save_data_root_path(const uint8_t in_path[0x301]) {
	result_t res;
	ipc_request_t rq = ipc_default_request;
	rq.request_id = 1002;

	ipc_buffer_t in_path_buf = {
		.addr = (void*) in_path,
		.size = 769,
		.type = 25,
	};


	ipc_response_fmt_t rs = ipc_default_response_fmt;
	ipc_buffer_t *buffers[] = {
		&in_path_buf
	};
	rq.num_buffers = 1;
	rq.buffers = buffers;

	res = ipc_send(fsp_srv_object, &rq, &rs);
	return res;
}

result_t fsp_srv_disable_auto_save_data_creation() {
	result_t res;
	ipc_request_t rq = ipc_default_request;
	rq.request_id = 1003;

	ipc_response_fmt_t rs = ipc_default_response_fmt;
	res = ipc_send(fsp_srv_object, &rq, &rs);
	return res;
}

result_t fsp_srv_set_global_access_log_mode(uint32_t in_mode) {
	result_t res;
	ipc_request_t rq = ipc_default_request;
	rq.request_id = 1004;

	uint8_t raw[4];
	rq.raw_data = raw;
	rq.raw_data_size = 4;

	*(uint32_t*)(raw + 0) = in_mode;


	ipc_response_fmt_t rs = ipc_default_response_fmt;
	res = ipc_send(fsp_srv_object, &rq, &rs);
	return res;
}

result_t fsp_srv_get_global_access_log_mode(uint32_t *out_logMode) {
	result_t res;
	ipc_request_t rq = ipc_default_request;
	rq.request_id = 1005;

	ipc_response_fmt_t rs = ipc_default_response_fmt;
	uint8_t output_raw[4];
	rs.raw_data = output_raw;
	rs.raw_data_size = 4;

	res = ipc_send(fsp_srv_object, &rq, &rs);
	*out_logMode = *(uint32_t*)(output_raw + 0);

	return res;
}

// result_t fsp_srv_output_access_log_to_sd_card(unknown in_logText);
