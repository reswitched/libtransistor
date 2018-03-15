/**
 * @file libtransistor/ipc/fs/idirectory.h
 * @brief Directory
 */

#pragma once

#ifdef __cplusplus
extern "C" {
#endif

#include <libtransistor/types.h>
#include <assert.h>

typedef ipc_object_t idirectory_t;

typedef struct idirectoryentry {
	char path[0x300];
	uint32_t unk1;
	uint8_t entry_type;
	// TODO: Padding
	uint64_t size;
} idirectoryentry_t;
static_assert(sizeof(idirectoryentry_t) == 0x310, "Wrong idirectoryentry_t size");

result_t idirectory_read(idirectory_t obj, uint64_t *out_unk0, idirectoryentry_t * out_unk1, size_t out_unk1_size);
result_t idirectory_get_entry_count(idirectory_t obj, uint64_t *out_unk0);

#ifdef __cplusplus
}
#endif
