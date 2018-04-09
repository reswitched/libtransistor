#include<libtransistor/cpp/svc.hpp>
#include<libtransistor/svc.h>

namespace Transistor {
namespace SVC {

Result<std::nullopt_t> CloseHandle(handle_t handle) {
	return ResultCode::ExpectOk(svcCloseHandle(handle));
}

}
}
