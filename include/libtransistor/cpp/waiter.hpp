/**
 * @file libtransistor/cpp/waiter.hpp
 * @brief Manager for waiting on synchronizable handles (C++ bindings)
 */

#pragma once

#include<libtransistor/cpp/types.hpp>
#include<libtransistor/waiter.h>

#include<functional>
#include<variant>
#include<memory>

namespace trn {

class Waiter;

class WaitHandle : public std::enable_shared_from_this<WaitHandle> {
 public:
	WaitHandle(Waiter *waiter, std::variant<std::unique_ptr<std::function<bool()>>, std::unique_ptr<std::function<uint64_t()>>> callback);
	~WaitHandle();

	void Signal();
	void ResetSignal();
	void Cancel();
	
	wait_record_t *record;
 private:
	friend class Waiter;
	static bool EventShim(void *data, handle_t handle);
	static uint64_t DeadlineShim(void *data);
	static bool SignalShim(void *data);

	template<typename R>
	R InvokeCallback() {
		// make sure we don't get destroyed before this function returns
		std::shared_ptr<WaitHandle> self = shared_from_this();
		
		if((*std::get<std::unique_ptr<std::function<R()>>>(callback))()) {
			return true;
		} else {
			// this is why we need to extend our lifetime
			is_cancelled = true;
			return false;
		}
	}
	std::variant<std::unique_ptr<std::function<bool()>>, std::unique_ptr<std::function<uint64_t()>>> callback;
	Waiter *waiter;
	bool is_cancelled = false;
};

class Waiter {
 public:
	Waiter();

	/* callback should return true if this handle should be kept in the wait list */
	/* when WaitHandle dies, it will unregister itself */
	std::shared_ptr<WaitHandle> Add(KWaitable &waitable, std::function<bool()> callback);
	std::shared_ptr<WaitHandle> AddDeadline(uint64_t deadline, std::function<uint64_t()> callback);
	std::shared_ptr<WaitHandle> AddSignal(std::function<bool()> callback);
	Result<std::nullopt_t> Wait(uint64_t timeout);

	~Waiter();

	waiter_t *waiter;
};

}
