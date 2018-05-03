/**
 * @file libtransistor/cpp/ipc/usb.hpp
 * @brief USB definitions (C++ header)
 */

#pragma once

#include<libtransistor/cpp/types.hpp>
#include<libtransistor/ipc/usb.h>

namespace trn {
namespace service {
namespace usb {

enum class DescriptorType {
	INTERFACE = 0x4,
	ENDPOINT = 0x5,
};

enum class EndpointDirection {
	OUT = 0x00,
	IN = 0x80,
};

enum class TransferType {
	CONTROL = 0x0,
	ISOCHRONOUS = 0x1,
	BULK = 0x2,
	INTERRUPT = 0x3,
};

}
}
}
