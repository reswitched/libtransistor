#include<libtransistor/display/parcel.h>

#include<libtransistor/err.h>
#include<libtransistor/types.h>
#include<libtransistor/display/binder.h>

#include<string.h>

void parcel_initialize(parcel_t *parcel) {
	parcel->read_head = 0;
	parcel->write_head = 0;
	parcel->writing_finalized = false;
}

result_t parcel_load(parcel_t *parcel, uint8_t *flattened) {
	memcpy(&(parcel->contents), flattened, 0x10);
	if(parcel->contents.data_size > sizeof(parcel->contents.payload)) {
		return LIBTRANSISTOR_ERR_PARCEL_DATA_TOO_BIG;
	}
	memcpy(parcel->contents.payload, flattened + parcel->contents.data_offset, parcel->contents.data_size);
	parcel->write_head = parcel->contents.data_size;
	parcel->read_head = 0;
	parcel->writing_finalized = true;
	return RESULT_OK;
}

uint8_t *parcel_finalize_writing(parcel_t *parcel, size_t *length) {
	parcel->writing_finalized = true;
	parcel->contents.data_size = parcel->write_head;
	parcel->contents.data_offset = 0x10;
	parcel->contents.objects_size = 0;
	parcel->contents.objects_offset = 0x10 + parcel->write_head;

	*length = 0x10 + parcel->write_head;
	return (uint8_t*) &(parcel->contents);
}

size_t parcel_read_remaining(parcel_t *parcel) {
	return parcel->write_head - parcel->read_head;
}

void *parcel_read_inplace(parcel_t *parcel, size_t length) {
	void *ptr = parcel->contents.payload + parcel->read_head;
	parcel->read_head+= length;
	return ptr;
}

result_t parcel_read_binder(parcel_t *parcel, binder_t *binder) {
	flat_binder_object_t *fbo = parcel_read_inplace(parcel, sizeof(flat_binder_object_t));
	// we really should check type/length, but I'm not sure how at the moment
	binder->handle = fbo->handle;

	// adjust refcount
	result_t r;
	if((r = binder_adjust_refcount(binder, 1, 0)) != RESULT_OK) { return r; }
	if((r = binder_adjust_refcount(binder, 1, 1)) != RESULT_OK) { return r; }
	return RESULT_OK;
}

uint32_t parcel_read_u32(parcel_t *parcel) {
	return *(uint32_t*) parcel_read_inplace(parcel, sizeof(uint32_t));
}

const char *parcel_read_string(parcel_t *parcel) {
	int32_t length = (int32_t) parcel_read_u32(parcel);
	if(length == -1) { return NULL; }
	size_t size = (length+1) * 2;

	// condense the string in place
	uint16_t *str16 = parcel_read_inplace(parcel, size);
	uint8_t *str8 = (uint8_t*) str16;
	for(int i = 0; i <= length; i++) {
		str8[i] = str16[i];
	}

	return (const char*) str8;
}

size_t parcel_write_remaining(parcel_t *parcel) {
	return sizeof(parcel->contents.payload) - parcel->write_head;
}

void *parcel_write_inplace(parcel_t *parcel, size_t length) {
	void *ptr = parcel->contents.payload + parcel->write_head;
	parcel->write_head+= (length + 3) & ~3;
	return ptr;
}

void parcel_write_u32(parcel_t *parcel, uint32_t value) {
	*(uint32_t*) parcel_write_inplace(parcel, sizeof(value)) = value;
}

void parcel_write_string16(parcel_t *parcel, const char *string) {
	int32_t length = strlen(string);
	parcel_write_u32(parcel, length);
	uint16_t *str16 = parcel_write_inplace(parcel, (length+1) * 2);
	for(int i = 0; i <= length; i++) {
		str16[i] = string[i];
	}
}

void parcel_write_interface_token(parcel_t *parcel, const char *token) {
	parcel_write_u32(parcel, 0x100);
	parcel_write_string16(parcel, token);
}
