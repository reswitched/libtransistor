#pragma once

#include<libtransistor/cpp/types.hpp>

#include<memory>

namespace Transistor {
namespace SVC {

class MemoryMapping {
 public:
	virtual ~MemoryMapping();

	virtual void *Base() = 0;
	virtual size_t Size() = 0;
};

Result<void*> SetHeapSize(uint32_t size);
Result<std::nullopt_t> SetMemoryPermission(void *addr, uint64_t size, uint32_t permission);
// etc., etc.
Result<std::nullopt_t> CloseHandle(handle_t handle);
// etc., etc.
Result<std::nullopt_t> SetProcessMemoryPermission(KProcess &process, uint64_t addr, size_t size, uint32_t perm);
Result<std::shared_ptr<MemoryMapping>> MapProcessMemory(std::shared_ptr<KProcess> process, uint64_t remote_addr, size_t size);
Result<KProcess> CreateProcess(void *process_info, void *caps, uint32_t cap_num);
Result<std::nullopt_t> StartProcess(KProcess &process, uint32_t main_thread_prio, uint32_t default_cpuid, uint32_t main_thread_stack_size);

}
}
