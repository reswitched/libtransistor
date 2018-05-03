#include<libtransistor/cpp/svc.hpp>
#include<libtransistor/svc.h>
#include<libtransistor/err.h>
#include<libtransistor/address_space.h>

namespace trn {
namespace svc {

class ProcessMemoryMapping : public MemoryMapping {
 public:
	ProcessMemoryMapping(uint8_t *local, std::shared_ptr<KProcess> process, uint64_t remote, size_t size) :
		local(local), process(process), remote(remote), size(size) {
	}

	virtual ~ProcessMemoryMapping() {
		ResultCode::AssertOk(svcUnmapProcessMemory(local, process->handle, remote, size));
		as_release(local, size);
	}

	virtual uint8_t *Base() { return local; }
	virtual size_t Size() { return size; }
	
	uint8_t *local;
	std::shared_ptr<KProcess> process;
	uint64_t remote;
	size_t size;
};

MemoryMapping::~MemoryMapping() {
}

Result<std::nullopt_t> CloseHandle(handle_t handle) {
	return ResultCode::ExpectOk(svcCloseHandle(handle));
}

Result<uint64_t> GetProcessId(handle_t handle) {
	uint64_t pid;
	return ResultCode::ExpectOk(svcGetProcessId(&pid, handle)).map([&pid](auto const &ignored) {
			return pid;
		});
}

Result<KDebug> DebugActiveProcess(uint64_t pid) {
	debug_h debug;
	return ResultCode::ExpectOk(svcDebugActiveProcess(&debug, pid)).map([&debug](auto const &ignored) {
			return KDebug(debug);
		});
}

Result<debug_event_info_t> GetDebugEvent(KDebug &debug) {
	debug_event_info_t info;
	return ResultCode::ExpectOk(svcGetDebugEvent(&info, debug.handle)).map([&info](auto const &ignored) {
			return info;
		});
}

Result<std::vector<uint64_t>> GetThreadList(uint32_t max, KDebug &debug) {
	std::vector<uint64_t> tids(max, 0);
	uint32_t num_out;
	return ResultCode::ExpectOk(svcGetThreadList(&num_out, tids.data(), num_out, debug.handle)).map([&tids, &num_out](auto const &ignored) {
			tids.resize(num_out);
			return tids;
		});
}

Result<thread_context_t> GetDebugThreadContext(KDebug &debug, uint64_t thread_id, uint32_t thread_context_flags) {
	thread_context_t thread_context;
	return ResultCode::ExpectOk(svcGetDebugThreadContext(&thread_context, debug.handle, thread_id, thread_context_flags)).map([&thread_context](auto const &ignored) {
			return thread_context;
		});
}

Result<std::tuple<memory_info_t, uint32_t>> QueryDebugProcessMemory(KDebug &debug, uint64_t addr) {
	memory_info_t mem_info;
	uint32_t page_info;
	return ResultCode::ExpectOk(svcQueryDebugProcessMemory(&mem_info, &page_info, debug.handle, addr)).map([&mem_info, &page_info](auto const &ignored) {
			return std::make_tuple(mem_info, page_info);
		});
}

Result<std::nullopt_t> ReadDebugProcessMemory(uint8_t *buffer, KDebug &debug, uint64_t addr, size_t size) {
	return ResultCode::ExpectOk(svcReadDebugProcessMemory(buffer, debug.handle, addr, size));
}

Result<std::nullopt_t> SetProcessMemoryPermission(KProcess &process, uint64_t addr, size_t size, uint32_t perm) {
	return ResultCode::ExpectOk(svcSetProcessMemoryPermission(process.handle, addr, size, perm));
}

Result<std::shared_ptr<MemoryMapping>> MapProcessMemory(std::shared_ptr<KProcess> process, uint64_t remote_addr, size_t size) {
	void *local_addr = as_reserve(size);
	if(local_addr == nullptr) {
		return tl::make_unexpected(ResultCode(LIBTRANSISTOR_ERR_OUT_OF_MEMORY));
	}
	return ResultCode::ExpectOk(svcMapProcessMemory(local_addr, process->handle, remote_addr, size)).map([local_addr, process, remote_addr, size](auto const &ignored) {
			return std::static_pointer_cast<MemoryMapping>(
				std::make_shared<ProcessMemoryMapping>((uint8_t*) local_addr, process, remote_addr, size));
		});
}

Result<KProcess> CreateProcess(void *process_info, void *caps, uint32_t cap_num) {
	process_h process;
	return ResultCode::ExpectOk(svcCreateProcess(&process, process_info, caps, cap_num)).map([&process](auto const &ignored) {
			return KProcess(process);
		});
}

Result<std::nullopt_t> StartProcess(KProcess &process, uint32_t main_thread_prio, uint32_t default_cpuid, uint32_t main_thread_stack_size) {
	return ResultCode::ExpectOk(svcStartProcess(process.handle, main_thread_prio, default_cpuid, main_thread_stack_size));
}

Result<std::nullopt_t> TerminateProcess(KProcess &process) {
	return ResultCode::ExpectOk(svcTerminateProcess(process.handle));
}

Result<uint64_t> GetProcessInfo(KProcess &process, uint32_t type) {
	uint64_t info;
	return ResultCode::ExpectOk(svcGetProcessInfo(&info, process.handle, type)).map([&info](auto const &ignored) {
			return info;
		});
}

Result<KResourceLimit> CreateResourceLimit() {
	resource_limit_h limit;
	return ResultCode::ExpectOk(svcCreateResourceLimit(&limit)).map([&limit](auto const &ignored) {
			return KResourceLimit(limit);
		});
}

Result<std::nullopt_t> SetResourceLimitLimitValue(KResourceLimit &limit, LimitableResource resource, uint64_t value) {
	return ResultCode::ExpectOk(svcSetResourceLimitLimitValue(limit.handle, (uint32_t) resource, value));
}

}
}
