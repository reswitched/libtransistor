#pragma once

#include<libtransistor/types.h>
#include<expected.hpp>

#include<stdexcept>
#include<string>
#include<optional>

namespace trn {

struct ResultCode {
 public:
	static tl::expected<std::nullopt_t, ResultCode> ExpectOk(result_t code);
	static void AssertOk(result_t code);
	template<typename T> static T&& AssertOk(tl::expected<T, ResultCode> &&monad);
	
	ResultCode(result_t code);
	inline bool IsOk() {
		return code == RESULT_OK;
	}
	
	result_t code;
};

template<typename T>
using Result = tl::expected<T, ResultCode>;

class ResultError : public std::runtime_error {
 public:
	ResultError(ResultCode code);
	ResultError(result_t code);
	
	virtual const char *what() const noexcept override;

	const ResultCode code;
 private:
	std::string description;
};

template<typename T> T&& ResultCode::AssertOk(tl::expected<T, ResultCode> &&monad) {
	if(monad) {
		return std::move(*monad);
	} else {
		throw ResultError(monad.error());
	}
}

class KObject {
 public:
	KObject() = default;
	KObject(handle_t handle);
	KObject(const KObject &) = delete;
	KObject &operator=(const KObject &) = delete;
	KObject(KObject &&other);
	KObject &operator=(KObject &&other);
	~KObject();

	handle_t Claim();
	
	handle_t handle = 0;
};

class KWaitable : public KObject {
 public:
	KWaitable() = default;
	KWaitable(handle_t handle);
};

class KSharedMemory : public KObject {
 public:
	KSharedMemory() = default;

	// foreign shared memory
	KSharedMemory(shared_memory_h handle, size_t size, uint32_t foreign_permission);

	size_t size;
	uint32_t foreign_permission;
};

class KTransferMemory : public KObject {
 public:
	KTransferMemory() = default;
	
	// foreign transfer memory
	KTransferMemory(transfer_memory_h handle, size_t size, uint32_t permissions);

	// owned transfer memory
	KTransferMemory(transfer_memory_h handle, void *backing_buffer, size_t size, uint32_t permissions);
	KTransferMemory(size_t size, uint32_t permissions);
	KTransferMemory(void *backing_buffer, size_t size, uint32_t permissions, bool owns_buffer=false);

	// misc
	KTransferMemory(KTransferMemory &&other);
	KTransferMemory &operator=(KTransferMemory &&other);
	~KTransferMemory();

	uint8_t *buffer = nullptr;
	size_t size = 0;
	uint32_t permissions = 0;
 private:
	bool owns_buffer = false;
};

class KPort : public KWaitable {
 public:
	KPort() = default;
	KPort(port_h handle);
};

class KProcess : public KWaitable {
 public:
	KProcess() = default;
	KProcess(process_h handle);
	Result<std::nullopt_t> ResetSignal();
	Result<std::nullopt_t> WaitSignal(uint64_t timeout);
};

class KEvent : public KWaitable {
 public:
	KEvent() = default;
	KEvent(revent_h handle);
	Result<std::nullopt_t> ResetSignal();
	Result<std::nullopt_t> WaitSignal(uint64_t timeout);
};

class KDebug : public KObject {
 public:
	KDebug() = default;
	KDebug(debug_h handle);
};

class KResourceLimit : public KObject {
 public:
	KResourceLimit() = default;
	KResourceLimit(resource_limit_h handle);
};

}
