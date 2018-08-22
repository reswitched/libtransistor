/**
 * @file libtransistor/cpp/address_space.hpp
 * @brief Address space management (C++ header)
 */

#pragma once

#include<libtransistor/address_space.h>

namespace trn {
namespace as {

class Reservation {
 public:
	Reservation(size_t size);
	~Reservation();
	
	const size_t size;
	uint8_t *const base;
};

} // namespace as
} // namespace trn
