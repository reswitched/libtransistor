#pragma once

#include<libtransistor/types.h>

#include<neither/neither.hpp>

#include<stdexcept>
#include<string>

namespace Transistor {

struct Unit {};

struct ResultCode {
	static neither::Either<ResultCode, Unit> Maybe(result_t code);
	static void AssertOk(result_t code);
	template<typename T> static T AssertOk(neither::Either<ResultCode, T> monad);
	
	ResultCode(result_t code);
	
	const result_t code;
};

class ResultError : std::runtime_error {
 public:
	ResultError(ResultCode code);
	ResultError(result_t code);
	
	const char *what() noexcept;
 private:
	const ResultCode code;
	std::string description;
};

template<typename T> T ResultCode::AssertOk(neither::Either<ResultCode, T> monad) {
	if(monad) {
		return monad.right().unsafeGet();
	} else {
		throw ResultError(monad.left().unsafeGet());
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
