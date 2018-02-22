#include<libtransistor/types.h>
#include<libtransistor/svc.h>
#include<libtransistor/ipc.h>
#include<libtransistor/err.h>
#include<libtransistor/util.h>
#include<libtransistor/ipc/sm.h>
#include<libtransistor/ipc/vi.h>
#include<libtransistor/display/parcel.h>
#include<libtransistor/display/graphic_buffer_queue.h>

#include<string.h>
#include<malloc.h>

result_t vi_result;
int vi_errno;

static ipc_domain_t vi_domain;
static ipc_object_t imrs_object; // nn::visrv::sf::IManagerRootService
static ipc_object_t iads_object; // nn::visrv::sf::IApplicationDisplayService
static ipc_object_t imds_object; // nn::visrv::sf::IManagerDisplayService
static ipc_object_t isds_object; // nn::visrv::sf::ISystemDisplayService
static ipc_object_t ihosbd_object; // nn::visrv::sf::IHOSBinderDriver
static int vi_initializations = 0;

static result_t get_object(ipc_object_t iface, int command, ipc_object_t *out) {
	ipc_request_t rq = ipc_default_request;
	rq.request_id = command;

	ipc_response_fmt_t rs = ipc_default_response_fmt;
	rs.num_objects = 1;
	rs.objects = out;

	return ipc_send(iface, &rq, &rs);
}

result_t vi_init() {
	if(vi_initializations++ > 0) {
		return RESULT_OK;
	}
  
	result_t r;
	r = sm_init();
	if(r) {
		goto fail;
	}
	
	r = sm_get_service(&imrs_object, "vi:m");
	if(r) {
		goto fail_sm;
	}

	r = ipc_convert_to_domain(&imrs_object, &vi_domain);
	if(r) {
		goto fail_domain;
	}

	{
		uint32_t raw[] = {1};
		ipc_request_t rq = ipc_default_request;
		rq.request_id = 2;
		rq.raw_data_size = sizeof(raw);
		rq.raw_data = raw;

		ipc_response_fmt_t rs = ipc_default_response_fmt;
		rs.num_objects = 1;
		rs.objects = &iads_object;

		r = ipc_send(imrs_object, &rq, &rs);
		if(r) {
			goto fail_imrs;
		}
	}

	if((r = get_object(iads_object, 100, &ihosbd_object)) != 0) { goto fail_iads; }
	if((r = get_object(iads_object, 101, &isds_object)) != 0) { goto fail_ihosbd; }
	if((r = get_object(iads_object, 102, &imds_object)) != 0) { goto fail_isds; }

	sm_finalize();
	return 0;
  
fail_isds:
	ipc_close(isds_object);
fail_ihosbd:
	ipc_close(ihosbd_object);
fail_iads:
	ipc_close(iads_object);
fail_imrs:
	ipc_close(imrs_object);
fail_domain:
	ipc_close_domain(vi_domain);
fail_sm:
	sm_finalize();
fail:
	vi_initializations--;
	return r;
}

result_t vi_open_display(const char *name, display_t *out) {
	uint8_t raw[0x40];
	memset(raw, 0, sizeof(raw));
	strncpy((char*) raw, name, sizeof(raw)-1);

	ipc_request_t rq = ipc_default_request;
	rq.request_id = 1010; // OpenDisplay
	rq.raw_data_size = sizeof(raw);
	rq.raw_data = (uint32_t*) raw;

	ipc_response_fmt_t rs = ipc_default_response_fmt;
	rs.raw_data_size = sizeof(out->id);
	rs.raw_data = (uint32_t*) &(out->id);

	return ipc_send(iads_object, &rq, &rs);
}

result_t vi_close_display(display_t *display) {
	ipc_request_t rq = ipc_default_request;
	rq.request_id = 1020;
	rq.raw_data_size = sizeof(display->id);
	rq.raw_data = (uint32_t*) &display->id;

	ipc_response_fmt_t rs = ipc_default_response_fmt;

	return ipc_send(iads_object, &rq, &rs);
}

result_t vi_get_display_vsync_event(display_t *display) {
	ipc_request_t rq = ipc_default_request;
	rq.request_id = 5202;
	rq.raw_data_size = sizeof(display->id);
	rq.raw_data = (uint32_t*) &display->id;

	ipc_response_fmt_t rs = ipc_default_response_fmt;
	rs.num_copy_handles = 1;
	rs.copy_handles = &display->vsync;
	
	return ipc_send(iads_object, &rq, &rs);
}

result_t vi_open_layer(const char *display_name, uint64_t layer_id, uint64_t aruid, igbp_t *igbp) {
	uint8_t parcel_buf[0x210];
	ipc_buffer_t parcel_ipc_buf;
	parcel_ipc_buf.addr = parcel_buf;
	parcel_ipc_buf.size = sizeof(parcel_buf);
	parcel_ipc_buf.type = 6;

	ipc_buffer_t *buffers[] = {&parcel_ipc_buf};
  
	struct {
		char display_name[0x40];
		uint64_t layer_id;
		uint64_t aruid;
	} rq_args;

	memset(rq_args.display_name, 0, sizeof(rq_args.display_name));
	strncpy(rq_args.display_name, display_name, sizeof(rq_args.display_name)-1);
	rq_args.layer_id = layer_id;
	rq_args.aruid = aruid;
  
	ipc_request_t rq = ipc_default_request;
	rq.request_id = 2020;
	rq.num_buffers = 1;
	rq.buffers = buffers;
	rq.raw_data_size = sizeof(rq_args);
	rq.raw_data = (uint32_t*) &rq_args;
	rq.send_pid = true;
  
	struct {
		uint64_t surface_size;
	} rs_vals;

	ipc_response_fmt_t rs = ipc_default_response_fmt;
	rs.raw_data_size = sizeof(rs_vals);
	rs.raw_data = (uint32_t*) &rs_vals;

	result_t r = ipc_send(iads_object, &rq, &rs);
	if(r) {
		return r;
	}

	parcel_t parcel;
	r = parcel_load(&parcel, parcel_buf);
	if(r) {
		return r;
	}

	r = parcel_read_binder(&parcel, &(igbp->igbp_binder));
	if(r) {
		return r;
	}

	return 0;
}

result_t vi_close_layer(uint64_t layer_id) {
	ipc_request_t rq = ipc_default_request;
	rq.request_id = 2021;
	rq.raw_data_size = sizeof(layer_id);
	rq.raw_data = &layer_id;

	return ipc_send(iads_object, &rq, &ipc_default_response_fmt);
}

result_t vi_create_managed_layer(uint32_t unknown, display_t *display, uint64_t aruid, uint64_t *layer_id) {
	struct {
		uint32_t unknown;
		uint32_t padding;
		uint64_t display;
		uint64_t aruid;
	} rq_args;

	rq_args.unknown = unknown;
	rq_args.display = display->id;
	rq_args.aruid = aruid;
  
	ipc_request_t rq = ipc_default_request;
	rq.request_id = 2010;
	rq.raw_data_size = sizeof(rq_args);
	rq.raw_data = (uint32_t*) &rq_args;

	ipc_response_fmt_t rs = ipc_default_response_fmt;
	rs.raw_data_size = sizeof(*layer_id);
	rs.raw_data = (uint32_t*) layer_id;

	return ipc_send(imds_object, &rq, &rs);
}

result_t vi_destroy_managed_layer(uint64_t layer_id) {
	ipc_request_t rq = ipc_default_request;
	rq.request_id = 2011;
	rq.raw_data_size = sizeof(layer_id);
	rq.raw_data = (uint32_t*) &layer_id;

	ipc_response_fmt_t rs = ipc_default_response_fmt;

	return ipc_send(imds_object, &rq, &rs);
}

result_t vi_create_stray_layer(uint32_t unknown, display_t *display, uint64_t *layer_id, igbp_t *igbp) {
	uint8_t parcel_buf[0x210];
	ipc_buffer_t parcel_ipc_buf;
	parcel_ipc_buf.addr = parcel_buf;
	parcel_ipc_buf.size = sizeof(parcel_buf);
	parcel_ipc_buf.type = 6;

	ipc_buffer_t *buffers[] = {&parcel_ipc_buf};
  
	struct {
		uint32_t unknown;
		uint32_t padding;
		uint64_t display;
	} rq_args;

	rq_args.unknown = unknown;
	rq_args.display = display->id;
  
	ipc_request_t rq = ipc_default_request;
	rq.request_id = 2030;
	rq.num_buffers = 1;
	rq.buffers = buffers;
	rq.raw_data_size = sizeof(rq_args);
	rq.raw_data = (uint32_t*) &rq_args;

	struct {
		uint64_t layer_id;
		uint64_t surface_size;
	} rs_vals;

	ipc_response_fmt_t rs = ipc_default_response_fmt;
	rs.raw_data_size = sizeof(rs_vals);
	rs.raw_data = (uint32_t*) &rs_vals;

	result_t r = ipc_send(iads_object, &rq, &rs);
	if(r) {
		return r;
	}

	*layer_id = rs_vals.layer_id;

	parcel_t parcel;
	r = parcel_load(&parcel, parcel_buf);
	if(r) {
		return r;
	}

	r = parcel_read_binder(&parcel, &(igbp->igbp_binder));
	if(r) {
		return r;
	}

	return 0;
}

result_t vi_adjust_refcount(int32_t handle, int32_t addval, int32_t type) {
	uint32_t raw[] = {handle, addval, type};

	ipc_request_t rq = ipc_default_request;
	rq.request_id = 1;
	rq.raw_data_size = sizeof(raw);
	rq.raw_data = raw;

	return ipc_send(ihosbd_object, &rq, &ipc_default_response_fmt);
}

result_t vi_transact_parcel(int32_t handle, uint32_t transaction, uint32_t flags, void *rq_parcel, size_t rq_parcel_size, void *rs_parcel, size_t rs_parcel_size) {

	ipc_buffer_t rq_buffer;
	rq_buffer.addr = rq_parcel;
	rq_buffer.size = rq_parcel_size;
	rq_buffer.type = 5;

	ipc_buffer_t rs_buffer;
	rs_buffer.addr = rs_parcel;
	rs_buffer.size = rs_parcel_size;
	rs_buffer.type = 6;
  
	ipc_buffer_t *buffers[] = {&rq_buffer, &rs_buffer};

	struct {
		int32_t handle;
		uint32_t transaction;
		uint32_t flags;
	} raw;

	raw.handle = handle;
	raw.transaction = transaction;
	raw.flags = flags;
  
	ipc_request_t rq = ipc_default_request;
	rq.request_id = 0;
	rq.num_buffers = 2;
	rq.buffers = buffers;
	rq.raw_data_size = sizeof(raw);
	rq.raw_data = (uint32_t*) &raw;

	ipc_response_fmt_t rs = ipc_default_response_fmt;

	return ipc_send(ihosbd_object, &rq, &rs);
}

static result_t ipc_simple_helper(ipc_object_t *object, uint32_t rqid, void* in, size_t in_size, void* out, size_t out_size) {
	ipc_request_t rq = ipc_default_request;
	rq.request_id = rqid;
	rq.raw_data_size = in_size;
	rq.raw_data = in;

	ipc_response_fmt_t rs = ipc_default_response_fmt;
	rs.raw_data_size = out_size;
	rs.raw_data = out;

	return ipc_send(*object, &rq, &rs);
}

// imds
result_t vi_imds_set_layer_visibility(bool visible, uint64_t layer_id) {
	struct {
		uint32_t visible;
		uint64_t layer_id;
	} params;
	params.visible = visible;
	params.layer_id = layer_id;
	return ipc_simple_helper(&imds_object, 6002, &params, sizeof(params), NULL, 0);
}

result_t vi_imds_set_display_layer_stack(uint32_t stack, display_t *display) {
	struct {
		uint32_t stack;
		uint64_t display_id;
	} params;
	params.stack = stack;
	params.display_id = display->id;
	return ipc_simple_helper(&imds_object, 4203, &params, sizeof(params), NULL, 0);  
}

result_t vi_imds_add_to_layer_stack(uint32_t stack, uint64_t layer_id) {
	struct {
		uint32_t stack;
		uint64_t layer_id;
	} params;
	params.stack = stack;
	params.layer_id = layer_id;
	return ipc_simple_helper(&imds_object, 6000, &params, sizeof(params), NULL, 0);  
}

result_t vi_imds_set_conductor_layer(bool conductor, uint64_t layer_id) {
	struct {
		uint32_t conductor;
		uint64_t layer_id;
	} params;
	params.conductor = conductor;
	params.layer_id = layer_id;
	return ipc_simple_helper(&imds_object, 8000, &params, sizeof(params), NULL, 0);  
}

result_t vi_imds_set_content_visibility(bool visible) {
	uint32_t u = visible;
	return ipc_simple_helper(&imds_object, 7000, &u, sizeof(u), NULL, 0);
}

// isds
result_t vi_isds_get_z_order_count_min(uint64_t layer_id, int64_t *z_count_min) {
	return ipc_simple_helper(&isds_object, 1200,
	                         &layer_id, sizeof(layer_id),
	                         z_count_min, sizeof(*z_count_min));
}

result_t vi_isds_get_z_order_count_max(uint64_t layer_id, int64_t *z_count_max) {
	return ipc_simple_helper(&isds_object, 1202,
	                         &layer_id, sizeof(layer_id),
	                         z_count_max, sizeof(*z_count_max));
}

result_t vi_isds_get_display_logical_resolution(display_t *display, int32_t *width, int32_t *height) {
	struct {
		int32_t width;
		int32_t height;
	} out;
	result_t r = ipc_simple_helper(&isds_object, 1203,
	                               &display->id, sizeof(display->id),
	                               &out, sizeof(out));
	*width = out.width;
	*height = out.height;
	return r;
}

result_t vi_isds_set_layer_position(float x, float y, uint64_t layer_id) {
	struct {
		float x;
		float y;
		uint64_t layer_id;
	} params;
	params.x = x;
	params.y = y;
	params.layer_id = layer_id;
	return ipc_simple_helper(&isds_object, 2201,
	                         &params, sizeof(params),
	                         NULL, 0);
}

result_t vi_isds_set_layer_size(uint64_t layer_id, int64_t width, int64_t height) {
	struct {
		uint64_t layer_id;
		int64_t width;
		int64_t height;
	} params;
	params.layer_id = layer_id;
	params.width = width;
	params.height = height;
	return ipc_simple_helper(&isds_object, 2203,
	                         &params, sizeof(params),
	                         NULL, 0);  
}

result_t vi_isds_get_layer_z(uint64_t layer_id, int64_t *z) {
	return ipc_simple_helper(&isds_object, 2204,
	                         &layer_id, sizeof(layer_id),
	                         z, sizeof(*z));
}

result_t vi_isds_set_layer_z(uint64_t layer_id, int64_t z) {
	struct {
		uint64_t layer_id;
		int64_t z;
	} params;
	params.layer_id = layer_id;
	params.z = z;
	return ipc_simple_helper(&isds_object, 2205,
	                         &params, sizeof(params),
	                         NULL, 0);
}

result_t vi_isds_set_layer_visibility(bool visible, uint64_t layer_id) {
	struct {
		uint32_t visible;
		uint64_t layer_id;
	} params;
	params.visible = visible;
	params.layer_id = layer_id;
	return ipc_simple_helper(&isds_object, 2207,
	                         &params, sizeof(params),
	                         NULL, 0);
}

result_t vi_iads_set_display_enabled(bool enabled, display_t *display) {
	struct {
		uint32_t enabled;
		uint64_t display_id;
	} params;
	params.enabled = enabled;
	params.display_id = display->id;
	return ipc_simple_helper(&iads_object, 1101,
	                         &params, sizeof(params),
	                         NULL, 0);
}

result_t vi_iads_set_layer_scaling_mode(uint32_t scaling_mode, uint64_t layer_id) {
	struct {
		uint32_t scaling_mode;
		uint64_t layer_id;
	} params;
	params.scaling_mode = scaling_mode;
	params.layer_id = layer_id;
	return ipc_simple_helper(&iads_object, 2101,
	                         &params, sizeof(params),
	                         NULL, 0);
}

static void vi_force_finalize() {
	ipc_close(isds_object);
	ipc_close(ihosbd_object);
	ipc_close(iads_object);
	ipc_close(imrs_object);
	ipc_close_domain(vi_domain);
	vi_initializations = 0;
}

void vi_finalize() {
	if(--vi_initializations == 0) {
		vi_force_finalize();
	}
}

static __attribute__((destructor)) void vi_destruct() {
	if(vi_initializations > 0) {
		vi_force_finalize();
	}
}
