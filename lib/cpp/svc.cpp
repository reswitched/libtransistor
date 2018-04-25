#include<libtransistor/cpp/svc.hpp>
#include<libtransistor/svc.h>
#include<libtransistor/err.h>
#include<libtransistor/address_space.h>

namespace Transistor {
namespace SVC {

class ProcessMemoryMapping : public MemoryMapping {
 public:
	ProcessMemoryMapping(void *local, std::shared_ptr<KProcess> process, uint64_t remote, size_t size) :
		local(local), process(process), remote(remote), size(size) {
	}

	virtual ~ProcessMemoryMapping() {
		ResultCode::AssertOk(svcUnmapProcessMemory(local, process->handle, remote, size));
	}

	virtual void *Base() { return local; }
	virtual size_t Size() { return size; }
	
	void *local;
	std::shared_ptr<KProcess> process;
	uint64_t remote;
	size_t size;
};

MemoryMapping::~MemoryMapping() {
}

Result<std::nullopt_t> CloseHandle(handle_t handle) {
	return ResultCode::ExpectOk(svcCloseHandle(handle));
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
				std::make_shared<ProcessMemoryMapping>(local_addr, process, remote_addr, size));
		});
}

Result<KProcess> CreateProcess(void *process_info, void *caps, uint32_t cap_num) {
	process_h process;
	return ResultCode::ExpectOk(svcCreateProcess(&process, process_info, caps, cap_num)).map([process](auto const &ignored) {
			return KProcess(process);
		});
}

Result<std::nullopt_t> StartProcess(KProcess &process, uint32_t main_thread_prio, uint32_t default_cpuid, uint32_t main_thread_stack_size) {
	return ResultCode::ExpectOk(svcStartProcess(process.handle, main_thread_prio, default_cpuid, main_thread_stack_size));
}

}
}
