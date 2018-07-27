/**
 * @file libtransistor/cpp/ipcserver.hpp
 * @brief IPC server (C++ header)
 */

#pragma once

#include<libtransistor/cpp/types.hpp>
#include<libtransistor/cpp/ipc.hpp>
#include<libtransistor/cpp/waiter.hpp>

#include<libtransistor/ipcserver.h>
#include<libtransistor/ipc.h>

#include<expected.hpp>

#include<vector>
#include<forward_list>
#include<tuple>

namespace trn {
namespace ipc {
namespace server {

class IPCServer;

class Object {
 public:
	Object(IPCServer *server);
	virtual ~Object();
	virtual ResultCode Dispatch(trn::ipc::Message msg, uint32_t request_id) = 0;

	IPCServer *server;
	ipc_server_object_t object;
 protected:
 private:
};

class IPCServer {
 public:
	static Result<IPCServer> Create(Waiter *waiter);
	
	IPCServer() = delete;
	IPCServer(const IPCServer &) = delete;
	IPCServer &operator=(const IPCServer &) = delete;
	IPCServer(IPCServer &&other);
	IPCServer &operator=(IPCServer &&other);
	~IPCServer();

	template<typename T, class... Args>
	Result<T*> CreateObject(Object *existing, Args &&... args) {
		T *obj = new T(this, args...);
		return ResultCode::ExpectOk(ipc_server_object_register(&existing->object, &obj->object)).map([obj](auto const &ignored) {
				return obj;
			});
	}

	template<typename T>
	Result<std::nullopt_t> CreateService(const char *name) {
		return CreateService(name, [](IPCServer *server) {
				return new T(server);
			});
	}
	Result<std::nullopt_t> CreateService(const char *name, std::function<Result<Object*>(IPCServer *server)> factory);
	
 private:
	IPCServer(ipc_server_t *server);
	std::forward_list<std::function<Result<Object*>()>*> factories;
	ipc_server_t *server;
};

template<typename... T>
struct ArgPack;

struct TransactionFormat {
	ipc_request_fmt_t rq = ipc_default_request_fmt;
	ipc_response_t rs = ipc_default_response;
	std::vector<ipc_buffer_t*> buffers;
	Object **out_objects;
	uint64_t pid;

	void Prepare();
	~TransactionFormat();
};

template<typename T>
struct AccessorHelper;

template<typename T>
struct AccessorHelper<ipc::InRaw<T>> {
	size_t offset;
	
	AccessorHelper(size_t offset) : offset(offset) {
	}
	
	ipc::InRaw<T> Access(TransactionFormat &f) const {
		return ipc::InRaw<T>(*((T*) (((uint8_t*) f.rq.raw_data) + offset)));
	}
};

template<typename T>
struct AccessorHelper<ipc::OutRaw<T>> {
	size_t offset;
	
	AccessorHelper(size_t offset) : offset(offset) {
	}
	
	ipc::OutRaw<T> Access(TransactionFormat &f) const {
		return ipc::OutRaw<T>(*(T*) (((uint8_t*) f.rs.raw_data) + offset));
	}
};

template<typename T>
struct AccessorHelper<ipc::OutHandle<T, ipc::copy>> {
	size_t index;

	AccessorHelper(size_t index) : index(index) {
	}

	ipc::OutHandle<T, ipc::copy> Access(TransactionFormat &f) const {
		return ipc::OutHandle<T, ipc::copy>(f.rs.copy_handles[index]);
	}
};

template<typename T>
struct AccessorHelper<ipc::OutHandle<T, ipc::move>> {
	size_t index;

	AccessorHelper(size_t index) : index(index) {
	}

	ipc::OutHandle<T, ipc::move> Access(TransactionFormat &f) const {
		return ipc::OutHandle<T, ipc::move>(f.rs.move_handles[index]);
	}
};

template<typename T>
struct AccessorHelper<ipc::OutObject<T>&> {
	size_t index;
	
	AccessorHelper(size_t index) : index(index) {
	}

	ipc::OutObject<T> &Access(TransactionFormat &f) const {
		return *((ipc::OutObject<T>*) &f.out_objects[index]);
	}
};

template<typename T, uint32_t type, size_t expected_size>
struct AccessorHelper<ipc::Buffer<T, type, expected_size>> {
	ipc_buffer_t *buffer;

	AccessorHelper(ipc_buffer_t *buffer) : buffer(buffer) {
	}

	ipc::Buffer<T, type, expected_size> Access(TransactionFormat &f) const {
		return {(T*) buffer->addr, buffer->size};
	}
};

template<>
struct AccessorHelper<ipc::InPid> {
	AccessorHelper() {
	}

	ipc::InPid Access(TransactionFormat &f) const {
		return {f.pid};
	}
};

template<>
struct AccessorHelper<ipc::OutPid> {
	AccessorHelper() {
	}

	ipc::OutPid Access(TransactionFormat &f) const {
		return OutPid(f.pid);
	}
};

template<typename T>
struct FormatMutator;

template<typename T>
struct FormatMutator<ipc::OutObject<T>&> {
	static AccessorHelper<ipc::OutObject<T>&> MutateFormat(TransactionFormat &fmt) {
		return AccessorHelper<ipc::OutObject<T>&>(fmt.rs.num_objects++);
	}
};

template<typename T>
struct FormatMutator<ipc::InRaw<T>> {
	static AccessorHelper<ipc::InRaw<T>> MutateFormat(TransactionFormat &fmt) {
		fmt.rq.raw_data_size+= (alignof(T) - 1);
		fmt.rq.raw_data_size-= fmt.rq.raw_data_size % alignof(T); // align
		size_t offset = fmt.rq.raw_data_size;
		fmt.rq.raw_data_size+= sizeof(T);
		return AccessorHelper<ipc::InRaw<T>>(offset);
	}
};

template<typename T>
struct FormatMutator<ipc::OutRaw<T>> {
	static AccessorHelper<ipc::OutRaw<T>> MutateFormat(TransactionFormat &fmt) {
		fmt.rs.raw_data_size+= (alignof(T) - 1);
		fmt.rs.raw_data_size-= fmt.rs.raw_data_size % alignof(T); // align
		size_t offset = fmt.rs.raw_data_size;
		fmt.rs.raw_data_size+= sizeof(T);
		return AccessorHelper<ipc::OutRaw<T>>(offset);
	}
};

template<typename T>
struct FormatMutator<ipc::OutHandle<T, ipc::copy>> {
	static AccessorHelper<ipc::OutHandle<T, ipc::copy>> MutateFormat(TransactionFormat &fmt) {
		return AccessorHelper<ipc::OutHandle<T, ipc::copy>>(fmt.rs.num_copy_handles++);
	}
};

template<typename T>
struct FormatMutator<ipc::OutHandle<T, ipc::move>> {
	static AccessorHelper<ipc::OutHandle<T, ipc::move>> MutateFormat(TransactionFormat &fmt) {
		return AccessorHelper<ipc::OutHandle<T, ipc::move>>(fmt.rs.num_move_handles++);
	}
};

template<typename T, uint32_t type, size_t expected_size>
struct FormatMutator<ipc::Buffer<T, type, expected_size>> {
	static AccessorHelper<ipc::Buffer<T, type, expected_size>> MutateFormat(TransactionFormat &fmt) {
		ipc_buffer_t *buffer = new ipc_buffer_t();
		buffer->type = type;
		buffer->size = expected_size;
		fmt.buffers.push_back(buffer);
		return AccessorHelper<ipc::Buffer<T, type, expected_size>>(buffer);
	}
};

template<>
struct FormatMutator<ipc::InPid> {
	static AccessorHelper<ipc::InPid> MutateFormat(TransactionFormat &fmt) {
		fmt.rq.send_pid = true;
		return AccessorHelper<ipc::InPid>();
	}
};

template<>
struct FormatMutator<ipc::OutPid> {
	static AccessorHelper<ipc::OutPid> MutateFormat(TransactionFormat &fmt) {
		fmt.rs.send_pid = true;
		return AccessorHelper<ipc::OutPid>();
	}
};

template<typename T>
struct FormatBuilder;

template<typename Arg0, typename... Args>
struct FormatBuilder<ArgPack<Arg0, Args...>> {
	static std::tuple<AccessorHelper<Arg0>, AccessorHelper<Args>...> Build(TransactionFormat &fmt) {
		AccessorHelper<Arg0> helper = FormatMutator<Arg0>::MutateFormat(fmt);
		return std::tuple_cat(std::make_tuple(helper), FormatBuilder<ArgPack<Args...>>::Build(fmt));
	}
};

template<>
struct FormatBuilder<ArgPack<>> {
	static std::tuple<> Build(TransactionFormat &fmt) {
		// nothing to do
		return std::make_tuple();
	}
};


template<auto>
struct RequestHandler;

template<typename T, typename... Args, ResultCode (T::*Func)(Args...)>
struct RequestHandler<Func> {
	static ResultCode Handle(T *object, ipc::Message msg) {
		TransactionFormat fmt;
		std::tuple<AccessorHelper<Args>...> accessors = FormatBuilder<ArgPack<Args...>>::Build(fmt);
		fmt.Prepare();
		
		ResultCode r = ipc_unflatten_request(&msg.msg, &fmt.rq, &object->object);
		if(!r.IsOk()) {
			// this gets forwarded to dispatch_shim, which will close the session for us
			return r;
		}

		r = RequestHandler<Func>::Helper(object, fmt, accessors, std::index_sequence_for<Args...>());
		if(!r.IsOk()) {
			ipc_response_t rs = ipc_default_response;
			rs.result_code = r.code;
			return ipc_server_object_reply(&object->object, &rs);
		}

		for(size_t i = 0; i < fmt.rs.num_objects; i++) {
			fmt.rs.objects[i] = &fmt.out_objects[i]->object;
		}

		return ipc_server_object_reply(&object->object, &fmt.rs);
	}
 private:
	template<std::size_t... I>
	static ResultCode Helper(T *object, TransactionFormat &fmt, const std::tuple<AccessorHelper<Args>...> &accessors, std::index_sequence<I...>) {
		return std::invoke(Func, object, (std::get<I>(accessors).Access(fmt))...);
	}
};

template<typename T, typename... Args, ResultCode (T::*Func)(std::function<void(ResultCode)>, Args...)>
struct RequestHandler<Func> {
	static ResultCode Handle(T *object, ipc::Message msg) {
		std::shared_ptr<TransactionFormat> fmt = std::make_shared<TransactionFormat>();
		std::tuple<AccessorHelper<Args>...> accessors = FormatBuilder<ArgPack<Args...>>::Build(*fmt);
		fmt->Prepare();
		
		ResultCode r = ipc_unflatten_request(&msg.msg, &fmt->rq, &object->object);
		if(!r.IsOk()) {
			// this gets forwarded to dispatch_shim, which will close the session for us
			return r;
		}

		RequestHandler<Func>::Helper(object, fmt, accessors, std::index_sequence_for<Args...>());
	}
 private:
	template<std::size_t... I>
	static ResultCode Helper(T *object, std::shared_ptr<TransactionFormat> fmt, const std::tuple<AccessorHelper<Args>...> &accessors, std::index_sequence<I...>) {
		return std::invoke(
			Func, object,
			[object, fmt](ResultCode r) -> void {
				if(!r.IsOk()) {
					ipc_response_t rs = ipc_default_response;
					rs.result_code = r.code;
					ipc_server_object_reply(&object->object, &rs);
					return;
				}
				
				for(size_t i = 0; i < fmt->rs.num_objects; i++) {
					fmt->rs.objects[i] = &fmt->out_objects[i]->object;
				}

				if(ipc_server_object_reply(&object->object, &fmt->rs) != RESULT_OK) {
					ipc_server_session_close(object->object.owning_session);
				}
			}, (std::get<I>(accessors).Access(*fmt))...);
	}
};

}
}
}
