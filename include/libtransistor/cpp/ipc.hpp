/**
 * @file libtransistor/cpp/ipc.hpp
 * @brief IPC (C++ header)
 */

#pragma once

#include<libtransistor/cpp/types.hpp>
#include<libtransistor/ipc.h>

#include<type_traits>

namespace Transistor {
namespace IPC {

class Message {
 public:
	ipc_message_t msg;
};

template<typename T>
struct OutObject {
	T *value;
};

template<typename T>
struct InRaw {
	static_assert(std::is_pod<T>::value, "InRaw types must be POD");
	T value;
};

template<typename T>
struct OutRaw {
	static_assert(std::is_pod<T>::value, "OutRaw types must be POD");
	OutRaw<T> &operator=(T val) {
		*value = val;
	}
	T *value;
};

template<typename T, uint32_t type, size_t expected_size>
struct Buffer {
	T *data;
	size_t size;
};

}
}
