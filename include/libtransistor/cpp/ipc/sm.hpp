/**
 * @file libtransistor/cpp/ipc/sm.hpp
 * @brief Service Manager IPC bindings (C++ header)
 */

#pragma once

#include<libtransistor/cpp/types.hpp>
#include<expected.hpp>

namespace Transistor {
namespace IPC {

class SM {
 public:
	static Result<SM> Initialize();
	SM(const SM& other);
	SM(SM&& other);
	~SM();

	Result<KPort> RegisterService(const char *name, uint32_t max_sessions);

 private:
	SM(); // use SM::Initialize
};

}
}
