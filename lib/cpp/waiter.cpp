#include<libtransistor/cpp/waiter.hpp>

#include<libtransistor/waiter.h>
#include<libtransistor/err.h>

namespace trn {

WaitHandle::WaitHandle(Waiter *waiter, std::variant<std::unique_ptr<std::function<bool()>>, std::unique_ptr<std::function<uint64_t()>>> callback) : callback(std::move(callback)), waiter(waiter) {
}

WaitHandle::~WaitHandle() {
	if(!is_cancelled) {
		Cancel();
	}
}

void WaitHandle::Signal() {
	waiter_signal(waiter->waiter, record);
}

void WaitHandle::ResetSignal() {
	waiter_reset_signal(waiter->waiter, record);
}

void WaitHandle::Cancel() {
	is_cancelled = true;
	waiter_cancel(waiter->waiter, record);
}

bool WaitHandle::EventShim(void *data, handle_t handle) {
	return ((WaitHandle*) data)->InvokeCallback<bool>();
}

uint64_t WaitHandle::DeadlineShim(void *data) {
	return ((WaitHandle*) data)->InvokeCallback<uint64_t>();
}

bool WaitHandle::SignalShim(void *data) {
	return ((WaitHandle*) data)->InvokeCallback<bool>();
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

std::shared_ptr<WaitHandle> Waiter::Add(KWaitable &waitable, std::function<bool()> callback) {
	std::shared_ptr<WaitHandle> wh = std::make_shared<WaitHandle>(this, std::make_unique<std::function<bool()>>(callback));
	wh->record = waiter_add(waiter, waitable.handle, &WaitHandle::EventShim, (void*) wh.get());
	return wh;
}

std::shared_ptr<WaitHandle> Waiter::AddDeadline(uint64_t deadline, std::function<uint64_t()> callback) {
	std::shared_ptr<WaitHandle> wh = std::make_shared<WaitHandle>(this, std::make_unique<std::function<uint64_t()>>(callback));
	wh->record = waiter_add_deadline(waiter, deadline, &WaitHandle::DeadlineShim, (void*) wh.get());
	return wh;
}

std::shared_ptr<WaitHandle> Waiter::AddSignal(std::function<bool()> callback) {
	std::shared_ptr<WaitHandle> wh = std::make_shared<WaitHandle>(this, std::make_unique<std::function<bool()>>(callback));
	wh->record = waiter_add_signal(waiter, &WaitHandle::SignalShim, (void*) wh.get());
	return wh;
}

Result<std::nullopt_t> Waiter::Wait(uint64_t timeout) {
	return ResultCode::ExpectOk(waiter_wait(waiter, timeout));
}

}
