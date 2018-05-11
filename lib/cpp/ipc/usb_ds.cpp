#include<libtransistor/cpp/types.hpp>
#include<libtransistor/cpp/ipc/usb_ds.hpp>
#include<libtransistor/ipc/usb.h>

namespace trn {
namespace service {
namespace usb {
namespace ds {

Result<DS> DS::Initialize(uint32_t complex_id) {
	DS obj(complex_id);
	return ResultCode::ExpectOk(usb_ds_init(complex_id)).map([obj](auto const &v) -> DS { return obj; } );
}

DS::DS(const DS& other) : complex_id(other.complex_id) {
	ResultCode::AssertOk(usb_ds_init(other.complex_id));
}

DS::DS(DS&& other) : complex_id(other.complex_id) {
	ResultCode::AssertOk(usb_ds_init(other.complex_id));
}

DS::DS(uint32_t complex_id) : complex_id(complex_id) {
}

DS::~DS() {
	usb_ds_finalize();
}

Result<KEvent> DS::GetStateChangeEvent() {
	revent_h handle;
	return ResultCode::ExpectOk(usb_ds_get_state_change_event(&handle)).map([&handle](auto const &v) -> KEvent {
			return KEvent(handle);
		});
}

Result<State> DS::GetState() {
	State state;
	return ResultCode::ExpectOk(usb_ds_get_state((usb_ds_state_t*) &state)).map([&state](auto const &v) -> State {
			return State(state);
		});
}

Result<std::nullopt_t> DS::SetVidPidBcd(usb_descriptor_data_t &data) {
	return ResultCode::ExpectOk(usb_ds_set_vid_pid_bcd(&data));
}

Result<std::shared_ptr<Interface>> DS::GetInterface(usb_interface_descriptor_t &descriptor, const char *name) {
	usb_ds_interface_t ifa;
	return ResultCode::ExpectOk(usb_ds_get_interface(&descriptor, name, &ifa)).map([&ifa](auto const &v) -> std::shared_ptr<Interface> {
			return std::make_shared<Interface>(ifa);
		});
}

Interface::Interface(usb_ds_interface_t intf) : intf(intf) {
}

Result<std::nullopt_t> Interface::Enable() {
	return ResultCode::ExpectOk(usb_ds_interface_enable(&intf));
}

Result<std::nullopt_t> Interface::Disable() {
	return ResultCode::ExpectOk(usb_ds_interface_disable(&intf));
}

class RegularEndpoint : public Endpoint {
 public:
	RegularEndpoint(usb_ds_endpoint_t endp, KEvent &&completion_event) : Endpoint(std::move(completion_event)), endp(endp) {
	}

	virtual Result<uint32_t> PostBufferAsync(void *buffer, size_t size) {
		uint32_t urb_id;
		return ResultCode::ExpectOk(usb_ds_post_buffer_async(&endp, buffer, size, &urb_id))
			.map([&urb_id](auto const &v) {
					return urb_id;
				});
	}

	virtual Result<usb_ds_report_t> GetReportData() {
		usb_ds_report_t report;
		return ResultCode::ExpectOk(usb_ds_get_report_data(&endp, &report))
			.map([&report](auto const &ignored) {
					return report;
				});
	}

	virtual Result<std::nullopt_t> Stall() {
		return ResultCode::ExpectOk(usb_ds_stall(&endp));
	}

	virtual ~RegularEndpoint() {
		ResultCode::AssertOk(usb_ds_close_endpoint(&endp));
	}
 private:
	usb_ds_endpoint_t endp;
};

Result<std::shared_ptr<Endpoint>> Interface::GetEndpoint(usb_endpoint_descriptor_t &descriptor) {
	usb_ds_endpoint_t endp;
	return ResultCode::ExpectOk(usb_ds_interface_get_endpoint(&intf, &descriptor, &endp))
		.and_then([&endp](auto const &ignored) {
				revent_h event;
				return ResultCode::ExpectOk(usb_ds_get_completion_event(&endp, &event))
					.map([&endp, &event](auto const &also_ignored) {
							return std::shared_ptr<Endpoint>(std::make_shared<RegularEndpoint>(endp, KEvent(event)));
					});
			});
}

class CtrlInEndpoint : public Endpoint {
 public:
	CtrlInEndpoint(usb_ds_interface_t *intf, KEvent &&completion_event) : Endpoint(std::move(completion_event)), intf(intf) {
	}

	virtual Result<uint32_t> PostBufferAsync(void *buffer, size_t size) {
		uint32_t urb_id;
		return ResultCode::ExpectOk(usb_ds_ctrl_in_post_buffer_async(intf, buffer, size, &urb_id))
			.map([&urb_id](auto const &v) {
					return urb_id;
				});
	}

	virtual Result<usb_ds_report_t> GetReportData() {
		usb_ds_report_t report;
		return ResultCode::ExpectOk(usb_ds_get_ctrl_in_report_data(intf, &report))
			.map([&report](auto const &ignored) {
					return report;
				});
	}

	virtual Result<std::nullopt_t> Stall() {
		return ResultCode::ExpectOk(usb_ds_stall_ctrl(intf));
	}
	
	virtual ~CtrlInEndpoint() {
	}
 private:
	usb_ds_interface_t *intf;
};

Result<std::shared_ptr<Endpoint>> Interface::GetCtrlInEndpoint() {
	revent_h event;
	return ResultCode::ExpectOk(usb_ds_get_ctrl_in_completion_event(&intf, &event))
		.map([this, &event](auto const &ignored) {
				return std::shared_ptr<Endpoint>(std::make_shared<CtrlInEndpoint>(&intf, KEvent(event)));
			});
}

class CtrlOutEndpoint : public Endpoint {
 public:
	CtrlOutEndpoint(usb_ds_interface_t *intf, KEvent &&completion_event) : Endpoint(std::move(completion_event)), intf(intf) {
	}

	virtual Result<uint32_t> PostBufferAsync(void *buffer, size_t size) {
		uint32_t urb_id;
		return ResultCode::ExpectOk(usb_ds_ctrl_out_post_buffer_async(intf, buffer, size, &urb_id))
			.map([&urb_id](auto const &v) {
					return urb_id;
				});
	}

	virtual Result<usb_ds_report_t> GetReportData() {
		usb_ds_report_t report;
		return ResultCode::ExpectOk(usb_ds_get_ctrl_out_report_data(intf, &report))
			.map([&report](auto const &ignored) {
					return report;
				});
	}

	virtual Result<std::nullopt_t> Stall() {
		return ResultCode::ExpectOk(usb_ds_stall_ctrl(intf));
	}
	
	virtual ~CtrlOutEndpoint() {
	}
 private:
	usb_ds_interface_t *intf;
};

Result<std::shared_ptr<Endpoint>> Interface::GetCtrlOutEndpoint() {
	revent_h event;
	return ResultCode::ExpectOk(usb_ds_get_ctrl_out_completion_event(&intf, &event))
		.map([this, &event](auto const &ignored) {
				return std::shared_ptr<Endpoint>(std::make_shared<CtrlOutEndpoint>(&intf, KEvent(event)));
			});
}

Interface::~Interface() {
	ResultCode::AssertOk(usb_ds_close_interface(&intf));
}

Endpoint::Endpoint(KEvent &&completion_event) : completion_event(std::move(completion_event)) {
}

Endpoint::~Endpoint() {
}

}
}
}
}
