#include<libtransistor/cpp/address_space.hpp>

namespace trn {
namespace as {

Reservation::Reservation(size_t size) :
	size(size),
	base((uint8_t*) as_reserve(size)) {
}

Reservation::~Reservation() {
	as_release((void*) base, size);
}

} // namespace as
} // namespace trn
