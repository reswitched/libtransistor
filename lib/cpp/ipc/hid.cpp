#include<libtransistor/cpp/types.hpp>
#include<libtransistor/cpp/ipc/hid.hpp>
#include<libtransistor/types.h>
#include<libtransistor/ipc/hid.h>

namespace trn {
namespace service {

Result<HID> HID::Initialize() {
	HID obj;
	return ResultCode::ExpectOk(hid_ipc_init()).map([obj](auto const &v) -> HID { return obj; } );
}

HID::HID(const HID& other) {
	// add another reference
	ResultCode::AssertOk(hid_ipc_init());
}

HID::HID(HID&& other) {
	// add another reference
	ResultCode::AssertOk(hid_ipc_init());
}

HID::HID() { // should only be called from HID::Initialize()
}

HID::~HID() {
	hid_ipc_finalize();
}

Result<KSharedMemory> HID::GetSharedMemory() {
	shared_memory_h handle;
	return ResultCode::ExpectOk(hid_ipc_get_shared_memory_handle(&handle)).map([&handle](auto const &v) -> KSharedMemory {
			return KSharedMemory(handle, 0x40000, 1);
		});
}

}
}
