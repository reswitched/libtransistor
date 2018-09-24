#include<libtransistor/display/binder.h>

#include<libtransistor/types.h>
#include<libtransistor/display/parcel.h>
#include<libtransistor/ipc/vi.h>

result_t binder_adjust_refcount(binder_t *binder, int32_t addval, int32_t type) {
	return vi_adjust_refcount(binder->handle, addval, type);
}

result_t binder_transact_parcel(binder_t *binder, uint32_t transaction, uint32_t flags, parcel_t *in, parcel_t *out) {
	size_t in_length;
	void *in_flattened = parcel_finalize_writing(in, &in_length);

	uint8_t out_buffer[0x210];
  
	result_t r = vi_transact_parcel(binder->handle, transaction, flags, in_flattened, in_length, out_buffer, sizeof(out_buffer));
	if(r) {
		return r;
	}

	return parcel_load(out, out_buffer);
}

result_t binder_get_native_handle(binder_t *binder, uint32_t native_id, revent_h *out) {
	return vi_get_native_handle(binder->handle, native_id, out);
}
