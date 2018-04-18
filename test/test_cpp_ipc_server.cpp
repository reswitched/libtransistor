#include<libtransistor/cpp/ipcserver.hpp>
#include<libtransistor/cpp/ipc/sm.hpp>
#include<libtransistor/cpp/svc.hpp>

#include<iostream>

int main(int argc, char *argv[]) {
	try {
		Transistor::IPC::SM sm = ResultCode::AssertOk(Transistor::IPC::SM::Initialize());
		Transistor::KPort port = ResultCode::AssertOk(sm.RegisterService("testsrv", 20));
		Transistor::IPCServer server(std::move(port), [] {
				return new RootObject();
			});
	} catch(Transistor::ResultError re) {
		printf("caught ResultError: %s\n", re.what().c_str());
	}
}
