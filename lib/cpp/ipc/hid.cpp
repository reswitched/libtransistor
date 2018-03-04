#include<libtransistor/cpp/types.hpp>
#include<libtransistor/cpp/ipc/hid.hpp>
#include<libtransistor/types.h>
#include<libtransistor/ipc/hid.h>

#include<neither/neither.hpp>

namespace Transistor {
namespace IPC {

neither::Either<ResultCode, HID> HID::Initialize() {
	HID obj;
	return ResultCode::Maybe(hid_ipc_init()).rightMap([obj](auto const &v) -> HID { return obj; } );
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

neither::Either<ResultCode, std::shared_ptr<KSharedMemory>> HID::GetSharedMemory() {
	shared_memory_h handle;
	return ResultCode::Maybe(hid_ipc_get_shared_memory_handle(&handle)).rightMap([&handle](auto const &v) -> std::shared_ptr<KSharedMemory> {
			return std::make_shared<KSharedMemory>(handle);
		});
}

}
}
