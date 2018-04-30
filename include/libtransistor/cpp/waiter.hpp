/**
 * @file libtransistor/cpp/waiter.hpp
 * @brief Manager for waiting on synchronizable handles (C++ bindings)
 */

#pragma once

#include<libtransistor/cpp/types.hpp>
#include<libtransistor/waiter.h>

#include<functional>
#include<memory>

namespace Transistor {

class Waiter;

class WaitHandle {
 public:
	WaitHandle(Waiter *waiter, std::function<bool()> *callback);
	~WaitHandle();
	void Cancel();
	bool InvokeCallback();
	
	wait_record_t *record;
 private:
	std::function<bool()> *callback;
	Waiter *waiter;
	bool is_cancelled = false;
};

class Waiter {
 public:
	Waiter();

	/* callback should return true if this handle should be kept in the wait list */
	/* when WaitHandle dies, it will unregister itself */
	std::shared_ptr<WaitHandle> Add(KWaitable &waitable, std::function<bool()> callback);
	Result<std::nullopt_t> Wait(uint64_t timeout);

	~Waiter();

	waiter_t *waiter;
};

}
