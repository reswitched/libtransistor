#include<libtransistor/cpp/waiter.hpp>
#include<libtransistor/waiter.h>
#include<libtransistor/err.h>

namespace trn {

WaitHandle::WaitHandle(Waiter *waiter, std::function<bool()> *callback) : callback(callback), waiter(waiter) {
}

WaitHandle::~WaitHandle() {
	if(!is_cancelled) {
		Cancel();
	}
	delete callback;
}

void WaitHandle::Cancel() {
	is_cancelled = true;
	waiter_cancel(waiter->waiter, record);
}

bool WaitHandle::InvokeCallback() {
	if((*callback)()) {
		return true;
	} else {
		is_cancelled = true;
		return false;
	}
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
	WaitHandle *wh = (WaitHandle*) data;
	return wh->InvokeCallback();
}

std::shared_ptr<WaitHandle> Waiter::Add(KWaitable &waitable, std::function<bool()> callback) {
	std::function<bool()> *callback_copy = new std::function<bool()>(callback);
	std::shared_ptr<WaitHandle> wh = std::make_shared<WaitHandle>(this, callback_copy);
	wh->record = waiter_add(waiter, waitable.handle, signal_shim, (void*) wh.get());
	return wh;
}

Result<std::nullopt_t> Waiter::Wait(uint64_t timeout) {
	return ResultCode::ExpectOk(waiter_wait(waiter, timeout));
}

}
