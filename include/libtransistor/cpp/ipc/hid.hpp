/**
 * @file libtransistor/cpp/ipc/hid.hpp
 * @brief Human Interface Device IPC bindings (C++ header)
 */

#pragma once

#include<libtransistor/cpp/types.hpp>
#include<neither/neither.hpp>

#include<memory>

namespace Transistor {
namespace IPC {

class HID {
 public:
	static neither::Either<ResultCode, HID> Initialize();
	HID(const HID& other);
	HID(HID&& other);
	
	~HID();

	neither::Either<ResultCode, std::shared_ptr<KSharedMemory>> GetSharedMemory();
	
 private:
	HID(); // use HID::Initialize
};

}
}
