/**
 * @file libtransistor/display/binder.h
 * @brief Display binder data structures and functions
 */

#pragma once

#include<libtransistor/types.h>
#include<libtransistor/display/parcel.h>

/**
* @struct binder_t
* @brief Description here...
*/
typedef struct binder_t {
	int32_t handle;
} binder_t;

/**
* @struct flat_binder_object_t
* @brief Description here...
*/
typedef struct {
	uint32_t type;
	uint32_t flags;

	union {
		void *binder;
		int32_t handle;
	};

	void *cookie;
} flat_binder_object_t;

/**
* @brief binder_adjust_refcount
*
* @param binder Description
* @param addval Description
* @param type Description
*/
result_t binder_adjust_refcount(binder_t *binder, int32_t addval, int32_t type);

/**
* @brief binder_transact_parcel
*
* @param binder Description
* @param transaction Description
* @param flags Description
* @param in Description
* @param out Description
*/
result_t binder_transact_parcel(binder_t *binder, uint32_t transaction, uint32_t flags, parcel_t *in, parcel_t *out);
