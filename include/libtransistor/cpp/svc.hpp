#pragma once

#include<libtransistor/cpp/types.hpp>

namespace Transistor {
namespace SVC {

neither::Either<ResultCode, void*> SetHeapSize(uint32_t size);
neither::Either<ResultCode, Unit> SetMemoryPermission(void *addr, uint64_t size, uint32_t permission);
// etc., etc.
neither::Either<ResultCode, Unit> CloseHandle(handle_t handle);

}
}
