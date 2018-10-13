/**
 * @file libtransistor/cpp/ipc.hpp
 * @brief IPC (C++ header)
 */

#pragma once

#include<libtransistor/cpp/types.hpp>
#include<libtransistor/ipc.h>

#include<type_traits>

namespace trn {
namespace ipc {

class Message {
 public:
	ipc_message_t msg;
};

template<typename T>
struct InObject {
	InObject(T &ref) : value(&ref) { }
	T *value;
};

template<typename T>
struct OutObject {
	OutObject(T &ref) : value(&ref) { }
	T *value;
};

template<typename T>
struct InRaw {
	InRaw(T value) : value(value) { }
	static_assert(std::is_pod<T>::value, "InRaw types must be POD");
	T value;

	T &operator*() {
		return value;
	}
};

template<typename T>
struct OutRaw {
	OutRaw(T &ref) : value(&ref) { }
	static_assert(std::is_pod<T>::value, "OutRaw types must be POD");
	
	OutRaw<T> &operator=(T val) {
		*value = val;
		return *this;
	}

	T &operator*() {
		return *value;
	}
	
	T *value;
};

struct copy {};
struct move {};

template<typename T, typename Transfer>
struct InHandle {
	InHandle(handle_t handle) : object(handle) {}

	InHandle<T, Transfer> &operator=(handle_t val) {
		object = val;
		return *this;
	}

	T object;
};

template<typename Transfer>
struct InHandle<handle_t, Transfer> {
	InHandle(handle_t handle) : handle(handle) {}

	InHandle<handle_t, Transfer> &operator=(handle_t val) {
		handle = val;
		return *this;
	}

	handle_t handle;
};

template<typename T, typename Transfer, typename... Args>
struct OutHandle;

template<typename Transfer>
struct OutHandle<handle_t, Transfer> {
	OutHandle(handle_t &handle) : handle(&handle) {}

	OutHandle<handle_t, Transfer> &operator=(handle_t val) {
		*handle = val;
		return *this;
	}

	handle_t *handle;
};

template<typename T, typename Transfer, typename... Args>
struct OutHandle {
	OutHandle(T &handle, Args... args) : handle(&handle), args(std::make_tuple(args...)) {}

	OutHandle<T, Transfer, Args...> &operator=(T &val) {
		*handle = T(val.handle);
		return *this;
	}

	OutHandle<T, Transfer, Args...> &operator=(handle_t &val) {
		HelpConstruct(val, std::index_sequence_for<Args...>());
		return *this;
	}

	T *handle;
	std::tuple<Args...> args;
 private:
	template<std::size_t... I>
	void HelpConstruct(handle_t &val, std::index_sequence<I...>) {
		*handle = T(val, std::get<I>(args)...);
	}
};

template<typename T, uint32_t type, size_t expected_size = 0>
struct Buffer {
	Buffer(std::vector<T> &vec) : Buffer(vec.data(), vec.size() * sizeof(T)) { }
	Buffer(T *data, size_t size) : data(data), size(size) { }
	
	T *data;
	size_t size;
};

struct InPid {
	uint64_t value;
};

struct OutPid {
	OutPid(uint64_t &ref) : value(&ref) { }
	uint64_t *value;
};

}
}
