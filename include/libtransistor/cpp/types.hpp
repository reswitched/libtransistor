#pragma once

#include<libtransistor/types.h>
#include<expected.hpp>

#include<stdexcept>
#include<string>
#include<optional>

namespace Transistor {

struct ResultCode {
	static tl::expected<std::nullopt_t, ResultCode> ExpectOk(result_t code);
	static void AssertOk(result_t code);
	template<typename T> static T AssertOk(neither::Either<ResultCode, T> monad);
	template<typename T> static T AssertOk(tl::expected<T, ResultCode> monad);
	
	ResultCode(result_t code);
	
	const result_t code;
};

template<typename T>
using Result = tl::expected<T, ResultCode>;

class ResultError : std::runtime_error {
 public:
	ResultError(ResultCode code);
	ResultError(result_t code);
	
	const char *what() noexcept;
 private:
	const ResultCode code;
	std::string description;
};

template<typename T> T ResultCode::AssertOk(tl::expected<T, ResultCode> monad) {
	if(monad) {
		return *monad;
	} else {
		throw ResultError(monad.error());
	}
}

class KObject {
 public:
	KObject(handle_t handle);
	~KObject();
	
	handle_t handle;
};

class KSharedMemory : public KObject {
 public:
	KSharedMemory(shared_memory_h handle);
};

}
