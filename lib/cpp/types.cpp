#include<libtransistor/cpp/types.hpp>

#include<libtransistor/cpp/svc.hpp>
#include<libtransistor/svc.h>
#include<libtransistor/alloc_pages.h>

#include<sstream>

#define UNW_LOCAL_ONLY
#include<libunwind.h>
#include<stdio.h>

namespace trn {

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

	if(true) {
		printf("ResultError 0x%x generated. Backtrace:\n", code.code);
		unw_cursor_t cursor;
		unw_context_t context;
		unw_getcontext(&context);
		unw_init_local(&cursor, &context);

		while(unw_step(&cursor) > 0) {
			unw_word_t offset, pc;
			unw_get_reg(&cursor, UNW_REG_IP, &pc);
			if(pc == 0) {
				break;
			}
			printf("0x%lx: ", pc);

			char sym[256];
			if(unw_get_proc_name(&cursor, sym, sizeof(sym), &offset) == 0) {
				printf("(%s+0x%lx)\n", sym, offset);
			} else {
				printf("<unknown>\n");
			}
		}
		printf("end\n");
	}
}

ResultError::ResultError(result_t code) : ResultError(ResultCode(code)) {
}

const char *ResultError::what() const noexcept {
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
		ResultCode::AssertOk(svc::CloseHandle(handle));
	}
}

handle_t KObject::Claim() {
	handle_t handle = this->handle;
	this->handle = 0;
	return handle;
}

KWaitable::KWaitable(handle_t handle) : KObject(handle) {
}

KSharedMemory::KSharedMemory(shared_memory_h handle, size_t size, uint32_t foreign_permission) : KObject(handle), size(size), foreign_permission(foreign_permission) {
}

KTransferMemory::KTransferMemory(transfer_memory_h handle, size_t size, uint32_t permissions) : KObject(handle), size(size), permissions(permissions) {
}

KTransferMemory::KTransferMemory(transfer_memory_h handle, void *addr, size_t size, uint32_t permissions) : KObject(handle), buffer((uint8_t*) addr), size(size), permissions(permissions) {
}

KTransferMemory::KTransferMemory(size_t size, uint32_t permissions) : KTransferMemory(ResultCode::AssertOk(svc::CreateTransferMemory(alloc_pages(size, size, nullptr), size, permissions))) {
	owns_buffer = true;
}

KTransferMemory::KTransferMemory(void *buffer, size_t size, uint32_t permissions, bool owns_buffer) : KTransferMemory(ResultCode::AssertOk(svc::CreateTransferMemory(buffer, size, permissions))) {
	this->owns_buffer = owns_buffer;
}

KTransferMemory::KTransferMemory(KTransferMemory &&other) : KObject(std::move(other)), buffer(other.buffer), size(other.size), permissions(other.permissions), owns_buffer(other.owns_buffer) {
	other.owns_buffer = false;
}

KTransferMemory &KTransferMemory::operator=(KTransferMemory &&other) {
	buffer = other.buffer;
	size = other.size;
	permissions = other.permissions;
	owns_buffer = other.owns_buffer;
	other.owns_buffer = false;
	KObject::operator=(std::move(other));
	return *this;
}

KTransferMemory::~KTransferMemory() {
	if(owns_buffer && buffer) {
		free_pages(buffer);
	}
}

KPort::KPort(port_h handle) : KWaitable(handle) {
}

KProcess::KProcess(process_h handle) : KWaitable(handle) {
}

KEvent::KEvent(revent_h handle) : KWaitable(handle) {
}

KDebug::KDebug(debug_h handle) : KObject(handle) {
}

KResourceLimit::KResourceLimit(resource_limit_h handle) : KObject(handle) {
}

Result<std::nullopt_t> KProcess::ResetSignal() {
	return ResultCode::ExpectOk(svcResetSignal(handle));
}

Result<std::nullopt_t> KProcess::WaitSignal(uint64_t timeout) {
	uint32_t handle_index;
	return ResultCode::ExpectOk(svcWaitSynchronization(&handle_index, &handle, 1, timeout));
}

Result<std::nullopt_t> KEvent::ResetSignal() {
	return ResultCode::ExpectOk(svcResetSignal(handle));
}

Result<std::nullopt_t> KEvent::WaitSignal(uint64_t timeout) {
	uint32_t handle_index;
	return ResultCode::ExpectOk(svcWaitSynchronization(&handle_index, &handle, 1, timeout));
}

}
