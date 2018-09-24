/**
 * @file libtransistor/display/binder.h
 * @brief Data structures and functions for interacting with the Android Binder IPC interface used in vi services.
 */

#pragma once

#ifdef __cplusplus
extern "C" {
#endif

#include<libtransistor/types.h>
#include<libtransistor/display/parcel.h>

/**
* @struct binder_t
* @brief Represents a remote interface
*/
typedef struct binder_t {
	int32_t handle;
} binder_t;

/**
* @struct flat_binder_object_t
* @brief Binder object as included in a Parcel
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
* @brief Adjusts the binder's reference count
*
* @param binder Binder object to adjust reference count for
* @param addval Description
* @param type Description
*/
result_t binder_adjust_refcount(binder_t *binder, int32_t addval, int32_t type);

/**
* @brief Perform a transaction on the given binder
*
* @param binder Binder object to transact with
* @param transaction Transaction ID
* @param flags Transaction flags
* @param in Parcel to read request parameters from
* @param out Parcel to write response values to
*/
result_t binder_transact_parcel(binder_t *binder, uint32_t transaction, uint32_t flags, parcel_t *in, parcel_t *out);

/**
 * @brief Gets a native handle from a binder
 */
result_t binder_get_native_handle(binder_t *binder, uint32_t id, revent_h *out);

#ifdef __cplusplus
}
#endif
