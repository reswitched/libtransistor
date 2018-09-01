#pragma once

#include<libtransistor/cpp/types.hpp>
#include<libtransistor/svc.h>

#include<memory>
#include<vector>
#include<tuple>

namespace trn {
namespace svc {

class MemoryMapping {
 public:
	virtual ~MemoryMapping();

	virtual uint8_t *Base() = 0;
	virtual size_t Size() = 0;
};

enum class ProcessState : uint64_t {
	CREATED = 0,
	DEBUG_ATTACHED = 1,
	DEBUG_DETACHED = 2,
	CRASHED = 3,
	RUNNING = 4,
	EXITING = 5,
	EXITED = 6,
	DEBUG_SUSPENDED = 7,
};

enum class LimitableResource : uint32_t {
	Memory = 0,
	Threads = 1,
	Events = 2,
	TransferMemories = 3,
	Sessions = 4,
};

using ThreadId = uint64_t;

Result<void*> SetHeapSize(uint32_t size);
Result<std::nullopt_t> SetMemoryPermission(void *addr, uint64_t size, uint32_t permission);
// etc., etc.
Result<std::tuple<memory_info_t, uint32_t>> QueryMemory(void *addr);
// etc., etc.
Result<std::shared_ptr<MemoryMapping>> MapSharedMemory(KSharedMemory &mem); // takes ownership of mem
Result<std::shared_ptr<MemoryMapping>> MapSharedMemory(std::shared_ptr<KSharedMemory> mem); // extends mem
Result<KTransferMemory> CreateTransferMemory(void *addr, uint64_t size, uint32_t permission);
Result<std::nullopt_t> CloseHandle(handle_t handle);

// etc., etc.

Result<uint64_t> GetProcessId(handle_t handle); // thread, process, or debug handle

// etc., etc.

Result<std::shared_ptr<MemoryMapping>> MapTransferMemory(KTransferMemory &mem); // takes ownership of mem
Result<std::shared_ptr<MemoryMapping>> MapTransferMemory(std::shared_ptr<KTransferMemory> mem); // extends mem

// etc., etc.

Result<KDebug> DebugActiveProcess(uint64_t pid);
Result<std::nullopt_t> BreakDebugProcess(KDebug &debug); // requires IsDebugMode
Result<std::nullopt_t> TerminateDebugProcess(KDebug &debug); // requires IsDebugMode
Result<debug_event_info_t> GetDebugEvent(KDebug &debug);
Result<std::nullopt_t> ContinueDebugEvent(KDebug &debug, uint32_t continue_debug_flags, ThreadId *thread_ids, uint32_t num_threads); // requires IsDebugMode
Result<std::vector<ThreadId>> GetThreadList(uint32_t max, KDebug &debug);
Result<thread_context_t> GetDebugThreadContext(KDebug &debug, uint64_t thread_id, uint32_t thread_context_flags);
Result<std::nullopt_t> SetDebugThreadContext(KDebug &debug, uint32_t flags, thread_context_t *context, ThreadId thread_id); // requires IsDebugMode
Result<std::tuple<memory_info_t, uint32_t>> QueryDebugProcessMemory(KDebug &debug, uint64_t addr);
Result<std::nullopt_t> ReadDebugProcessMemory(uint8_t *buffer, KDebug &debug, uint64_t addr, size_t size);
Result<std::nullopt_t> WriteDebugProcessMemory(KDebug &debug, uint8_t *buffer, uint64_t addr, size_t size); // requires IsDebugMode
// GetDebugThreadParam


Result<std::nullopt_t> SetProcessMemoryPermission(KProcess &process, uint64_t addr, size_t size, uint32_t perm);
Result<std::shared_ptr<MemoryMapping>> MapProcessMemory(std::shared_ptr<KProcess> process, uint64_t remote_addr, size_t size);
Result<KProcess> CreateProcess(void *process_info, void *caps, uint32_t cap_num);
Result<std::nullopt_t> StartProcess(KProcess &process, uint32_t main_thread_prio, uint32_t default_cpuid, uint32_t main_thread_stack_size);
Result<std::nullopt_t> TerminateProcess(KProcess &process);
Result<uint64_t> GetProcessInfo(KProcess &process, uint32_t type);
Result<KResourceLimit> CreateResourceLimit();
Result<std::nullopt_t> SetResourceLimitLimitValue(KResourceLimit &limit, LimitableResource resource, uint64_t value);

}
}
