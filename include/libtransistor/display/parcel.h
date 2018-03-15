/**
 * @file libtransistor/display/parcel.h
 * @brief Data structures and functions for packing/unpacking Android Parcels
 */

#pragma once

#ifdef __cplusplus
extern "C" {
#endif

#include<libtransistor/types.h>

/**
* @struct parcel_t
* @brief Represents a parcel
*
*        Bounds checking is the caller's responsibility.
*        Objects aren't currently supported very well.
*/
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

/**
* @brief Initialize an empty Parcel
*
* @param parcel Description
*/
void parcel_initialize(parcel_t *parcel);

/**
* @brief Load a Parcel
*
* @param parcel Description
* @param flattened Description
*/
result_t parcel_load(parcel_t *parcel, uint8_t *flattened);

/**
* @brief Finalize writing a Parcel
*
* @param parcel Description
* @param length Description
*/
uint8_t *parcel_finalize_writing(parcel_t *parcel, size_t *length);

/**
* @brief Query how much data is left that can be read
*
* @param parcel Description
*/
size_t parcel_read_remaining(parcel_t *parcel);

/**
* @brief Returns a pointer to the read head, then bumps it `length` bytes
*
* @param parcel Description
* @param length Description
*/
void *parcel_read_inplace(parcel_t *parcel, size_t length);

/**
* @brief Read a \ref binder_t from the Parcel
*
* @param parcel Description
* @param binder Description
*/
result_t parcel_read_binder(parcel_t *parcel, struct binder_t *binder);

/**
* @brief Read a uint32 from the Parcel
*
* @param parcel Description
*/
uint32_t parcel_read_u32(parcel_t *parcel);

/**
* @brief Read a string16 from the Parcel
*
* @param parcel Description
*/
const char *parcel_read_string16(parcel_t *parcel); // proper char16 support isn't worth my time

/**
* @brief Query how much space is left for writing
*
* @param parcel Description
*/
size_t parcel_write_remaining(parcel_t *parcel);

/**
* @brief Returns a pointer to the write head, them bumps it `length` bytes
*
* @param parcel Description
* @param length Description
*/
void *parcel_write_inplace(parcel_t *parcel, size_t length);

/**
* @brief Write a uint32 to the Parcel
*
* @param parcel Description
* @param value Description
*/
void parcel_write_u32(parcel_t *parcel, uint32_t value);

/**
* @brief Write a string16 to the Parcel
*
* @param parcel Description
* @param string Description
*/
void parcel_write_string16(parcel_t *parcel, const char *string);

/**
* @brief Write an interface token to the Parcel
*
* @param parcel Description
* @param token Description
*/
void parcel_write_interface_token(parcel_t *parcel, const char *token);

#ifdef __cplusplus
}
#endif
