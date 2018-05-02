/**
 * @file libtransistor/cpp/ipcclient.hpp
 * @brief IPC client template library (C++ header)
 */

#pragma once

#include<libtransistor/cpp/types.hpp>
#include<libtransistor/cpp/ipc.hpp>
#include<libtransistor/ipc.h>

#include<tuple>
#include<vector>

namespace Transistor {
namespace IPCClient {

template<typename... T>
struct ArgPack;

struct TransactionFormat {
	ipc_request_t rq = ipc_default_request;
	ipc_response_fmt_t rs = ipc_default_response_fmt;
	std::vector<ipc_buffer_t*> buffers;
	
	~TransactionFormat();
};

template<typename T>
struct AccessorHelper;

template<typename T>
struct AccessorHelper<IPC::InRaw<T>> {
	size_t offset;

	AccessorHelper(size_t offset) : offset(offset) {
	}

	void Pack(TransactionFormat &f, IPC::InRaw<T> &arg) const {
		*((T*) (((uint8_t*) f.rq.raw_data) + offset)) = arg.value;
	}

	void Unpack(TransactionFormat &f, IPC::InRaw<T> &arg) const {
	}
};

template<typename T>
struct AccessorHelper<IPC::OutRaw<T>> {
	size_t offset;

	AccessorHelper(size_t offset) : offset(offset) {
	}

	void Pack(TransactionFormat &f, IPC::OutRaw<T> &arg) const {
	}

	void Unpack(TransactionFormat &f, IPC::OutRaw<T> &arg) const {
		arg = *((T*) (((uint8_t*) f.rs.raw_data) + offset));
	}
};

template<typename T>
struct AccessorHelper<IPC::OutHandle<T, IPC::copy>> {
	size_t index;

	AccessorHelper(size_t index) : index(index) {
	}

	void Pack(TransactionFormat &f, IPC::OutHandle<T, IPC::copy> &arg) const {
	}

	void Unpack(TransactionFormat &f, IPC::OutHandle<T, IPC::copy> &arg) const {
		arg = f.rs.copy_handles[index];
	}
};

template<typename T>
struct AccessorHelper<IPC::OutHandle<T, IPC::move>> {
	size_t index;

	AccessorHelper(size_t index) : index(index) {
	}

	void Pack(TransactionFormat &f, IPC::OutHandle<T, IPC::move> &arg) const {
	}

	void Unpack(TransactionFormat &f, IPC::OutHandle<T, IPC::move> &arg) const {
		arg = f.rs.move_handles[index];
	}
};

template<typename T>
struct AccessorHelper<IPC::OutObject<T>> {
	size_t index;

	AccessorHelper(size_t index) : index(index) {
	}

	void Pack(TransactionFormat &f, IPC::OutObject<T> &arg) const {
	}

	void Unpack(TransactionFormat &f, IPC::OutObject<T> &arg) const {
		*(arg.value) = T(f.rs.objects[index]);
	}
};

template<typename T, uint32_t type>
struct AccessorHelper<IPC::Buffer<T, type>> {
	ipc_buffer_t *buffer;

	AccessorHelper(ipc_buffer_t *buffer) : buffer(buffer) {
	}

	void Pack(TransactionFormat &f, IPC::Buffer<T, type> &arg) const {
		buffer->addr = (void*) arg.data;
		buffer->size = arg.size;
	}

	void Unpack(TransactionFormat &f, IPC::Buffer<T, type> &arg) const {
	}
};

template<>
struct AccessorHelper<IPC::Pid> {
	AccessorHelper() {
	}

	void Pack(TransactionFormat &f, IPC::Pid &arg) const {
	}

	void Unpack(TransactionFormat &f, IPC::Pid &arg) const {
	}
};

template<typename T>
struct FormatMutator;

template<typename T>
struct FormatMutator<IPC::OutObject<T>> {
	static AccessorHelper<IPC::OutObject<T>> MutateFormat(TransactionFormat &fmt) {
		return AccessorHelper<IPC::OutObject<T>>(fmt.rs.num_objects++);
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

template<typename T>
struct FormatMutator<IPC::OutHandle<T, IPC::copy>> {
	static AccessorHelper<IPC::OutHandle<T, IPC::copy>> MutateFormat(TransactionFormat &fmt) {
		return AccessorHelper<IPC::OutHandle<T, IPC::copy>>(fmt.rs.num_copy_handles++);
	}
};

template<typename T>
struct FormatMutator<IPC::OutHandle<T, IPC::move>> {
	static AccessorHelper<IPC::OutHandle<T, IPC::move>> MutateFormat(TransactionFormat &fmt) {
		return AccessorHelper<IPC::OutHandle<T, IPC::move>>(fmt.rs.num_move_handles++);
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

template<>
struct FormatMutator<IPC::Pid> {
	static AccessorHelper<IPC::Pid> MutateFormat(TransactionFormat &fmt) {
		fmt.rq.send_pid = true;
		return AccessorHelper<IPC::Pid>();
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

class ClientObject {
 public:
	ClientObject();
	ClientObject(ipc_object_t object);
	ClientObject(const ClientObject &) = delete;
	ClientObject &operator=(const ClientObject &) = delete;
	ClientObject(ClientObject &&other);
	ClientObject &operator=(ClientObject &&other);
	~ClientObject();

	bool is_valid;
	ipc_object_t object;

	template<uint32_t id, typename... Args>
	Result<std::nullopt_t> SendSyncRequest(Args &&... args) {
		TransactionFormat fmt;
		std::tuple<AccessorHelper<Args>...> accessors = FormatBuilder<ArgPack<Args...>>::Build(fmt);

		fmt.rq.request_id = id;
		fmt.rq.raw_data = new uint8_t[fmt.rq.raw_data_size];
		fmt.rq.num_buffers = fmt.buffers.size();
		fmt.rq.buffers = fmt.buffers.data();
		
		fmt.rs.raw_data = new uint8_t[fmt.rs.raw_data_size];
		fmt.rs.objects = new ipc_object_t[fmt.rs.num_objects];
		fmt.rq.copy_handles = new handle_t[fmt.rq.num_copy_handles];
		fmt.rq.move_handles = new handle_t[fmt.rq.num_move_handles];
		
		ClientObject::HelpPack(fmt, accessors, std::index_sequence_for<Args...>(), args...);
		
		ResultCode r = ipc_send(object, &fmt.rq, &fmt.rs);
		if(!r.IsOk()) {
			return tl::make_unexpected(r);
		}

		ClientObject::HelpUnpack(fmt, accessors, std::index_sequence_for<Args...>(), args...);

		return std::nullopt;
	}
 private:
	template<typename... Args, std::size_t... I>
	static void HelpPack(TransactionFormat &fmt, const std::tuple<AccessorHelper<Args>...> &accessors, std::index_sequence<I...>, Args &... args) {
		((std::get<I>(accessors).Pack(fmt, args)),...);
	}

	template<typename... Args, std::size_t... I>
	static void HelpUnpack(TransactionFormat &fmt, const std::tuple<AccessorHelper<Args>...> &accessors, std::index_sequence<I...>, Args &... args) {
		((std::get<I>(accessors).Unpack(fmt, args)),...);
	}
};

}
}
