#include<libtransistor/cpp/ipc/hid.hpp>
#include<libtransistor/cpp/svc.hpp>

#include<iostream>

using Transistor::ResultCode;

int main(int argc, char *argv[]) {
	try {
		Transistor::IPC::HID hid = ResultCode::AssertOk(Transistor::IPC::HID::Initialize());
		Transistor::KSharedMemory shmem = ResultCode::AssertOk(hid.GetSharedMemory());
		ResultCode::AssertOk(ResultCode::ExpectOk(0x1337));
		
		std::cout << "got shared memory: 0x" << std::hex << shmem.handle << std::endl;
		
		return 0;
	} catch(Transistor::ResultError re) {
		std::cout << "caught ResultError: " << re.what() << std::endl;
		return 1;
	}
}
