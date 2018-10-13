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

namespace trn {
namespace ipc {
namespace client {

class Object;

template<typename... T>
struct ArgPack;

struct TransactionFormat {
	ipc_request_t rq = ipc_default_request;
	ipc_response_fmt_t rs = ipc_default_response_fmt;
	std::vector<ipc_buffer_t*> buffers;
	uint64_t pid;
	
	~TransactionFormat();
};

template<typename T, typename... Extra>
struct AccessorHelper;

template<typename T>
struct AccessorHelper<ipc::InRaw<T>> {
	size_t offset;

	AccessorHelper(size_t offset) : offset(offset) {
	}

	void Pack(TransactionFormat &f, ipc::InRaw<T> &arg) const {
		*((T*) (((uint8_t*) f.rq.raw_data) + offset)) = arg.value;
	}

	void Unpack(TransactionFormat &f, ipc::InRaw<T> &arg) const {
	}
};

template<typename T>
struct AccessorHelper<ipc::OutRaw<T>> {
	size_t offset;

	AccessorHelper(size_t offset) : offset(offset) {
	}

	void Pack(TransactionFormat &f, ipc::OutRaw<T> &arg) const {
	}

	void Unpack(TransactionFormat &f, ipc::OutRaw<T> &arg) const {
		arg = *((T*) (((uint8_t*) f.rs.raw_data) + offset));
	}
};

template<typename T>
struct AccessorHelper<ipc::InHandle<T, ipc::copy>> {
	size_t index;

	AccessorHelper(size_t index) : index(index) {
	}

	void Pack(TransactionFormat &f, ipc::InHandle<T, ipc::copy> &arg) const {
		f.rq.copy_handles[index] = arg.handle;
	}

	void Unpack(TransactionFormat &f, ipc::InHandle<T, ipc::copy> &arg) const {
	}
};

template<typename T>
struct AccessorHelper<ipc::InHandle<T, ipc::move>> {
	size_t index;

	AccessorHelper(size_t index) : index(index) {
	}

	void Pack(TransactionFormat &f, ipc::InHandle<T, ipc::move> &arg) const {
		f.rq.move_handles[index] = arg.handle;
	}

	void Unpack(TransactionFormat &f, ipc::InHandle<T, ipc::move> &arg) const {
	}
};

template<typename T, typename... Extra>
struct AccessorHelper<ipc::OutHandle<T, ipc::copy, Extra...>> {
	size_t index;

	AccessorHelper(size_t index) : index(index) {
	}

	void Pack(TransactionFormat &f, ipc::OutHandle<T, ipc::copy, Extra...> &arg) const {
	}

	void Unpack(TransactionFormat &f, ipc::OutHandle<T, ipc::copy, Extra...> &arg) const {
		arg = f.rs.copy_handles[index];
	}
};

template<typename T, typename... Extra>
struct AccessorHelper<ipc::OutHandle<T, ipc::move, Extra...>> {
	size_t index;

	AccessorHelper(size_t index) : index(index) {
	}

	void Pack(TransactionFormat &f, ipc::OutHandle<T, ipc::move, Extra...> &arg) const {
	}

	void Unpack(TransactionFormat &f, ipc::OutHandle<T, ipc::move, Extra...> &arg) const {
		arg = f.rs.move_handles[index];
	}
};

template<typename T>
struct AccessorHelper<ipc::InObject<T>> {
	size_t index;

	AccessorHelper(size_t index) : index(index) {
	}

	void Pack(TransactionFormat &f, ipc::InObject<T> &arg) const {
		f.rq.objects[index] = arg.value->object.object;
	}

	void Unpack(TransactionFormat &f, ipc::InObject<T> &arg) const {
	}
};

template<typename T>
struct AccessorHelper<ipc::OutObject<T>> {
	size_t index;

	AccessorHelper(size_t index) : index(index) {
	}

	void Pack(TransactionFormat &f, ipc::OutObject<T> &arg) const {
	}

	void Unpack(TransactionFormat &f, ipc::OutObject<T> &arg) const {
		*(arg.value) = T(f.rs.objects[index]);
	}
};

template<typename T, uint32_t type>
struct AccessorHelper<ipc::Buffer<T, type>> {
	ipc_buffer_t *buffer;

	AccessorHelper(ipc_buffer_t *buffer) : buffer(buffer) {
	}

	void Pack(TransactionFormat &f, ipc::Buffer<T, type> &arg) const {
		buffer->addr = (void*) arg.data;
		buffer->size = arg.size;
	}

	void Unpack(TransactionFormat &f, ipc::Buffer<T, type> &arg) const {
	}
};

template<>
struct AccessorHelper<ipc::InPid> {
	AccessorHelper() {
	}

	void Pack(TransactionFormat &f, ipc::InPid &arg) const {
	}

	void Unpack(TransactionFormat &f, ipc::InPid &arg) const {
	}
};

template<>
struct AccessorHelper<ipc::OutPid> {
	AccessorHelper() {
	}

	void Pack(TransactionFormat &f, ipc::OutPid &arg) const {
	}

	void Unpack(TransactionFormat &f, ipc::OutPid &arg) const {
		*arg.value = f.pid;
	}
};

template<typename T, typename... Extra>
struct FormatMutator;

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
struct FormatMutator<ipc::InHandle<T, ipc::copy>> {
	static AccessorHelper<ipc::InHandle<T, ipc::copy>> MutateFormat(TransactionFormat &fmt) {
		return AccessorHelper<ipc::InHandle<T, ipc::copy>>(fmt.rq.num_copy_handles++);
	}
};

template<typename T>
struct FormatMutator<ipc::InHandle<T, ipc::move>> {
	static AccessorHelper<ipc::InHandle<T, ipc::move>> MutateFormat(TransactionFormat &fmt) {
		return AccessorHelper<ipc::InHandle<T, ipc::move>>(fmt.rq.num_move_handles++);
	}
};

template<typename T, typename... Extra>
struct FormatMutator<ipc::OutHandle<T, ipc::copy, Extra...>> {
	static AccessorHelper<ipc::OutHandle<T, ipc::copy, Extra...>> MutateFormat(TransactionFormat &fmt) {
		return AccessorHelper<ipc::OutHandle<T, ipc::copy, Extra...>>(fmt.rs.num_copy_handles++);
	}
};

template<typename T, typename... Extra>
struct FormatMutator<ipc::OutHandle<T, ipc::move, Extra...>> {
	static AccessorHelper<ipc::OutHandle<T, ipc::move, Extra...>> MutateFormat(TransactionFormat &fmt) {
		return AccessorHelper<ipc::OutHandle<T, ipc::move, Extra...>>(fmt.rs.num_move_handles++);
	}
};

template<typename T>
struct FormatMutator<ipc::InObject<T>> {
	static AccessorHelper<ipc::InObject<T>> MutateFormat(TransactionFormat &fmt) {
		return AccessorHelper<ipc::InObject<T>>(fmt.rq.num_objects++);
	}
};

template<typename T>
struct FormatMutator<ipc::OutObject<T>> {
	static AccessorHelper<ipc::OutObject<T>> MutateFormat(TransactionFormat &fmt) {
		return AccessorHelper<ipc::OutObject<T>>(fmt.rs.num_objects++);
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
		fmt.rs.has_pid = true;
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

class Object {
 public:
	Object();
	Object(ipc_object_t object);
	Object(const Object &) = delete;
	Object &operator=(const Object &) = delete;
	Object(Object &&other);
	Object &operator=(Object &&other);
	~Object();

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
		fmt.rq.objects = new ipc_object_t[fmt.rq.num_objects];
		fmt.rq.copy_handles = new handle_t[fmt.rq.num_copy_handles];
		fmt.rq.move_handles = new handle_t[fmt.rq.num_move_handles];
		
		fmt.rs.raw_data = new uint8_t[fmt.rs.raw_data_size];
		fmt.rs.objects = new ipc_object_t[fmt.rs.num_objects];
		fmt.rs.copy_handles = new handle_t[fmt.rs.num_copy_handles];
		fmt.rs.move_handles = new handle_t[fmt.rs.num_move_handles];
		fmt.rs.pid = &fmt.pid;
		
		Object::HelpPack(fmt, accessors, std::index_sequence_for<Args...>(), args...);
		
		ResultCode r = ipc_send(object, &fmt.rq, &fmt.rs);
		if(!r.IsOk()) {
			return tl::make_unexpected(r);
		}

		Object::HelpUnpack(fmt, accessors, std::index_sequence_for<Args...>(), args...);

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
}
