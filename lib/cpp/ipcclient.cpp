#include<libtransistor/cpp/ipc.hpp>
#include<libtransistor/cpp/ipcclient.hpp>

namespace trn {
namespace ipc {
namespace client {

Object::Object() : is_valid(false) {
}

Object::Object(ipc_object_t object) : object(object), is_valid(true) {
}

Object::Object(Object &&other) {
	this->is_valid = other.is_valid;
	this->object = other.object;
	other.is_valid = false;
}

Object &Object::operator=(Object &&other) {
	this->is_valid = other.is_valid;
	this->object = other.object;
	other.is_valid = false;
	return *this;
}

Object::~Object() {
	if(is_valid) {
		ipc_close(object);
	}
}

TransactionFormat::~TransactionFormat() {
	for(auto i = buffers.begin(); i != buffers.end(); i++) {
		delete (*i);
	}
	if(rq.raw_data)     { delete[] rq.raw_data; }
	if(rq.objects)      { delete[] rq.objects; }
	if(rs.raw_data)     { delete[] rs.raw_data; }
	if(rs.objects)      { delete[] rs.objects; }
	if(rs.copy_handles) { delete[] rs.copy_handles; }
	if(rs.move_handles) { delete[] rs.move_handles; }
}

}
}
}
