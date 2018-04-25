/**
 * @file libtransistor/cpp/ipcserver.hpp
 * @brief IPC server (C++ header)
 */

#pragma once

#include<libtransistor/cpp/types.hpp>
#include<libtransistor/cpp/ipc.hpp>

#include<libtransistor/ipcserver.h>
#include<libtransistor/ipc.h>

#include<expected.hpp>

#include<vector>
#include<forward_list>
#include<tuple>

namespace Transistor {

namespace IPCServer {

class IPCServer;

class Object {
 public:
	Object(IPCServer *server);
	virtual ~Object();
	virtual ResultCode Dispatch(Transistor::IPC::Message msg, uint32_t request_id) = 0;

	IPCServer *server;
	ipc_server_object_t object;
 protected:
 private:
};

class IPCServer {
 public:
	static Result<IPCServer> Create();
	
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
	Result<std::nullopt_t> Process(uint64_t timeout);
	
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

	~TransactionFormat();
};

template<typename T>
struct AccessorHelper;

template<typename T>
struct AccessorHelper<IPC::InRaw<T>> {
	size_t offset;
	
	AccessorHelper(size_t offset) : offset(offset) {
	}
	
	IPC::InRaw<T> Access(TransactionFormat &f) const {
		return {*((T*) (((uint8_t*) f.rq.raw_data) + offset))};
	}
};

template<typename T>
struct AccessorHelper<IPC::OutRaw<T>> {
	size_t offset;
	
	AccessorHelper(size_t offset) : offset(offset) {
	}
	
	IPC::OutRaw<T> Access(TransactionFormat &f) const {
		return {((T*) (((uint8_t*) f.rs.raw_data) + offset))};
	}
};

template<typename T>
struct AccessorHelper<IPC::OutObject<T>&> {
	size_t index;
	
	AccessorHelper(size_t index) : index(index) {
	}

	IPC::OutObject<T> &Access(TransactionFormat &f) const {
		return *((IPC::OutObject<T>*) &f.out_objects[index]);
	}
};

template<typename T, uint32_t type, size_t expected_size>
struct AccessorHelper<IPC::Buffer<T, type, expected_size>> {
	ipc_buffer_t *buffer;

	AccessorHelper(ipc_buffer_t *buffer) : buffer(buffer) {
	}

	IPC::Buffer<T, type, expected_size> Access(TransactionFormat &f) const {
		return {(T*) buffer->addr, buffer->size};
	}
};

template<typename T>
struct FormatMutator;

template<typename T>
struct FormatMutator<IPC::OutObject<T>&> {
	static AccessorHelper<IPC::OutObject<T>&> MutateFormat(TransactionFormat &fmt) {
		return AccessorHelper<IPC::OutObject<T>&>(fmt.rs.num_objects++);
	}
};

template<typename T>
struct FormatMutator<IPC::InRaw<T>> {
	static AccessorHelper<IPC::InRaw<T>> MutateFormat(TransactionFormat &fmt) {
		fmt.rq.raw_data_size+= (alignof(T) - 1);
		fmt.rq.raw_data_size-= fmt.rq.raw_data_size % alignof(T); // align
		size_t offset = fmt.rq.raw_data_size;
		fmt.rq.raw_data_size+= sizeof(T);
		return AccessorHelper<IPC::InRaw<T>>(offset);
	}
};

template<typename T>
struct FormatMutator<IPC::OutRaw<T>> {
	static AccessorHelper<IPC::OutRaw<T>> MutateFormat(TransactionFormat &fmt) {
		fmt.rs.raw_data_size+= (alignof(T) - 1);
		fmt.rs.raw_data_size-= fmt.rs.raw_data_size % alignof(T); // align
		size_t offset = fmt.rs.raw_data_size;
		fmt.rs.raw_data_size+= sizeof(T);
		return AccessorHelper<IPC::OutRaw<T>>(offset);
	}
};

template<typename T, uint32_t type, size_t expected_size>
struct FormatMutator<IPC::Buffer<T, type, expected_size>> {
	static AccessorHelper<IPC::Buffer<T, type, expected_size>> MutateFormat(TransactionFormat &fmt) {
		ipc_buffer_t *buffer = new ipc_buffer_t();
		buffer->type = type;
		buffer->size = expected_size;
		fmt.buffers.push_back(buffer);
		return AccessorHelper<IPC::Buffer<T, type, expected_size>>(buffer);
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
	static ResultCode Handle(T *object, IPC::Message msg) {
		TransactionFormat fmt;
		std::tuple<AccessorHelper<Args>...> accessors = FormatBuilder<ArgPack<Args...>>::Build(fmt);

		fmt.rq.raw_data = new uint8_t[fmt.rq.raw_data_size];
		fmt.rq.num_buffers = fmt.buffers.size();
		fmt.rq.buffers = fmt.buffers.data();
		
		fmt.rs.raw_data = new uint8_t[fmt.rs.raw_data_size];
		fmt.rs.objects = new ipc_server_object_t*[fmt.rs.num_objects];
		fmt.out_objects = new Object*[fmt.rs.num_objects];
		
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

}

}
