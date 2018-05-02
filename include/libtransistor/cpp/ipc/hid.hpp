/**
 * @file libtransistor/cpp/ipc/hid.hpp
 * @brief Human Interface Device IPC bindings (C++ header)
 */

#pragma once

#include<libtransistor/cpp/types.hpp>
#include<expected.hpp>

namespace trn {
namespace service {

class HID {
 public:
	static Result<HID> Initialize();
	HID(const HID& other);
	HID(HID&& other);
	
	~HID();

	Result<KSharedMemory> GetSharedMemory();
	
 private:
	HID(); // use HID::Initialize
};

}
}
