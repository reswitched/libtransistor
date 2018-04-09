#pragma once

#include<libtransistor/cpp/types.hpp>

namespace Transistor {
namespace SVC {

Result<void*> SetHeapSize(uint32_t size);
Result<std::nullopt_t> SetMemoryPermission(void *addr, uint64_t size, uint32_t permission);
// etc., etc.
Result<std::nullopt_t> CloseHandle(handle_t handle);

}
}
