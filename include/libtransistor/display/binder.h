#pragma once

#include<libtransistor/types.h>
#include<libtransistor/display/parcel.h>

typedef struct binder_t {
	int32_t handle;
} binder_t;

typedef struct {
	uint32_t type;
	uint32_t flags;

	union {
		void *binder;
		int32_t handle;
	};

	void *cookie;
} flat_binder_object_t;

result_t binder_transact_parcel(binder_t *binder, uint32_t transaction, uint32_t flags, parcel_t *in, parcel_t *out);
