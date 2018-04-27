#include<libtransistor/cpp/waiter.hpp>
#include<libtransistor/waiter.h>
#include<libtransistor/err.h>

namespace Transistor {

WaitHandle::WaitHandle(Waiter *waiter, wait_record_t *record) : waiter(waiter), record(record) {
}

void WaitHandle::Cancel() {
	waiter->Cancel(*this);
}

Waiter::Waiter() {
	waiter = waiter_create();
	if(waiter == NULL) {
		throw new ResultError(LIBTRANSISTOR_ERR_OUT_OF_MEMORY);
	}
}

Waiter::~Waiter() {
	waiter_destroy(waiter);
}

static bool signal_shim(void *data, handle_t handle) {
	std::function<bool()> *func = (std::function<bool()>*) data;
	return (*func)();
}

WaitHandle Waiter::Add(KWaitable &waitable, std::function<bool()> *callback) {
	return WaitHandle(this, waiter_add(waiter, waitable.handle, signal_shim, callback));
}

Result<std::nullopt_t> Waiter::Wait(uint64_t timeout) {
	return ResultCode::ExpectOk(waiter_wait(waiter, timeout));
}

void Waiter::Cancel(WaitHandle wh) {
	waiter_cancel(waiter, wh.record);
}

}
