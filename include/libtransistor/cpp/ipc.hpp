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

template<typename T, typename Transfer>
struct OutHandle {
	OutHandle(handle_t &handle) : handle(&handle) {}

	OutHandle<T, Transfer> &operator=(T &val) {
		*handle = val.handle;
		return *this;
	}

	handle_t *handle;
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
