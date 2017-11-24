#pragma once

#include<libtransistor/types.h>

// bounds checking is the caller's responsibility
// objects aren't currently supported very well
typedef struct {
	struct {
		uint32_t data_size;
		uint32_t data_offset;
		uint32_t objects_size;
		uint32_t objects_offset;
		uint8_t payload[0x200];
	} contents;
	size_t read_head;
	size_t write_head;

	bool writing_finalized;
} parcel_t;

struct binder_t;

void parcel_initialize(parcel_t *parcel);
result_t parcel_load(parcel_t *parcel, uint8_t *flattened);
uint8_t *parcel_finalize_writing(parcel_t *parcel, size_t *length);

size_t parcel_read_remaining(parcel_t *parcel);
void *parcel_read_inplace(parcel_t *parcel, size_t length);
result_t parcel_read_binder(parcel_t *parcel, struct binder_t *binder);
uint32_t parcel_read_u32(parcel_t *parcel);
const char *parcel_read_string16(parcel_t *parcel); // proper char16 support isn't worth my time

size_t parcel_write_remaining(parcel_t *parcel);
void *parcel_write_inplace(parcel_t *parcel, size_t length);
void parcel_write_u32(parcel_t *parcel, uint32_t value);
void parcel_write_string16(parcel_t *parcel, const char *string);
void parcel_write_interface_token(parcel_t *parcel, const char *token);
