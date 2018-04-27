/**
 * @file libtransistor/cpp/waiter.hpp
 * @brief Manager for waiting on synchronizable handles (C++ bindings)
 */

#pragma once

#include<libtransistor/cpp/types.hpp>
#include<libtransistor/waiter.h>

#include<functional>

namespace Transistor {

class Waiter;

class WaitHandle {
 public:
	WaitHandle(Waiter *waiter, wait_record_t *record);
	void Cancel();

	wait_record_t *record;
 private:
	Waiter *waiter;
};

class Waiter {
 public:
	Waiter();

	/* callback should return true if this handle should be kept in the wait list */
	WaitHandle Add(KWaitable &waitable, std::function<bool()> *callback);
	Result<std::nullopt_t> Wait(uint64_t timeout);
	void Cancel(WaitHandle handle);

	~Waiter();

	waiter_t *waiter;
};

}
