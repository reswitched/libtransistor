#include<libtransistor/cpp/ipc.hpp>
#include<libtransistor/cpp/ipcclient.hpp>

namespace trn {
namespace ipc {
namespace client {

Object::Object() : is_valid(false) {
}

Object::Object(ipc_object_t object) : is_valid(true), object(object) {
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
	if(rq.raw_data)     { delete[] (uint8_t*) rq.raw_data; }
	if(rq.objects)      { delete[] rq.objects; }
	if(rq.copy_handles) { delete[] rq.copy_handles; }
	if(rq.move_handles) { delete[] rq.move_handles; }
	
	if(rs.raw_data)     { delete[] (uint8_t*) rs.raw_data; }
	if(rs.objects)      { delete[] rs.objects; }
	if(rs.copy_handles) { delete[] rs.copy_handles; }
	if(rs.move_handles) { delete[] rs.move_handles; }
}

}
}
}
