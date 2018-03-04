#include<libtransistor/cpp/svc.hpp>
#include<libtransistor/svc.h>

namespace Transistor {
namespace SVC {

neither::Either<ResultCode, Unit> CloseHandle(handle_t handle) {
	return ResultCode::Maybe(svcCloseHandle(handle));
}

}
}
