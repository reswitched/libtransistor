#include<libtransistor/cpp/types.hpp>
#include<libtransistor/cpp/svc.hpp>

#include<libtransistor/svc.h>

#include<sstream>

namespace Transistor {

tl::expected<std::nullopt_t, ResultCode> ResultCode::ExpectOk(result_t code) {
	if(code == RESULT_OK) {
		return std::nullopt;
	} else {
		return tl::make_unexpected(ResultCode(code));
	}
}

ResultCode::ResultCode(result_t code) : code(code) {
}

void ResultCode::AssertOk(result_t code) {
	if(code == RESULT_OK) {
		return;
	}
	throw ResultError(code);
}

ResultError::ResultError(ResultCode code) : std::runtime_error("failed to format result code"), code(code) {
	std::ostringstream ss;
	ss << "0x" << std::hex << code.code;
	description = ss.str();
}

ResultError::ResultError(result_t code) : ResultError(ResultCode(code)) {
}

const char *ResultError::what() noexcept {
	return description.c_str();
}

KObject::KObject(handle_t handle) : handle(handle) {
}

KObject::KObject(KObject &&other) {
	this->handle = other.handle;
	other.handle = 0;
}

KObject &KObject::operator=(KObject &&other) {
	this->handle = other.handle;
	other.handle = 0;
	return *this;
}

KObject::~KObject() {
	if(handle > 0) {
		ResultCode::AssertOk(SVC::CloseHandle(handle));
	}
}

handle_t KObject::Claim() {
	handle_t handle = this->handle;
	this->handle = 0;
	return handle;
}

KSharedMemory::KSharedMemory(shared_memory_h handle) : KObject(handle) {
}

KPort::KPort(port_h handle) : KObject(handle) {
}

KProcess::KProcess(process_h handle) : KObject(handle) {
}

}
