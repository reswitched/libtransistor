#include<libtransistor/ipc.h>
#include<libtransistor/ipcserver.h>
#include<libtransistor/tls.h>
#include<libtransistor/svc.h>
#include<libtransistor/err.h>
#include<libtransistor/util.h>

#include<string.h>
#include<stdio.h>

int ipc_debug_flag = 0;

ipc_buffer_t null_buffer = {
	.addr = 0,
	.size = 0,
	.type = 0
};

ipc_object_t ipc_null_object = {
	.session = 0,
	.object_id = -1,
	.is_borrowed = false,
};

ipc_request_t ipc_default_request = {
	.type = 4,
	.num_buffers = 0,
	.buffers = NULL,
	.request_id = 0,
	.raw_data = 0,
	.raw_data_size = 0,
	.send_pid = false,
	.num_copy_handles = 0,
	.num_move_handles = 0,
	.num_objects = 0,
	.copy_handles = NULL,
	.move_handles = NULL,
	.objects = NULL,
	.close_object = false
};

ipc_response_t ipc_default_response = {
	.type = 0,
	.num_buffers = 0,
	.buffers = NULL,
	.result_code = 0,
	.raw_data = 0,
	.raw_data_size = 0,
	.send_pid = false,
	.num_copy_handles = 0,
	.num_move_handles = 0,
	.num_objects = 0,
	.copy_handles = NULL,
	.move_handles = NULL,
	.objects = NULL,
};

ipc_request_fmt_t ipc_default_request_fmt = {
	.num_copy_handles = 0,
	.num_move_handles = 0,
	.num_objects = 0,
	.copy_handles = NULL,
	.move_handles = NULL,
	.objects = NULL,
  
	.raw_data_size = 0,
	.raw_data = NULL,

	.send_pid = false,
	.pid = NULL
};

ipc_response_fmt_t ipc_default_response_fmt = {
	.num_copy_handles = 0,
	.num_move_handles = 0,
	.num_objects = 0,
	.copy_handles = NULL,
	.move_handles = NULL,
	.objects = NULL,
  
	.raw_data_size = 0,
	.raw_data = NULL,

	.has_pid = false,
	.pid = NULL
};

typedef struct {
	uint16_t message_type;
	uint32_t data_section_size; // in words, including SFCI/SFCO/domain header, but not padding

	// this should be on a higher level of abstraction, but the u16 length list kinda wrecks that
	uint32_t num_buffers;
	ipc_buffer_t **buffers;
	
	uint32_t num_copy_handles;
	uint32_t num_move_handles;
	handle_t *copy_handles;
	handle_t *move_handles;
	bool send_pid;
	uint32_t *data_section; // not including padding or u16 list
} ipc_pack_message_t;

static result_t ipc_pack_message(uint32_t *buffer, ipc_pack_message_t *msg) {
	int h = 0; // h is for HEAD
  
	ipc_buffer_t *a_descriptors[16];
	ipc_buffer_t *b_descriptors[16];
	ipc_buffer_t *c_descriptors[16];
	ipc_buffer_t *x_descriptors[16];
  
	int num_a_descriptors = 0, num_b_descriptors = 0,
		num_c_descriptors = 0, num_x_descriptors = 0;

	// group buffers by descriptor type
	for(uint32_t i = 0; i < msg->num_buffers; i++) {
		ipc_buffer_t *ipc_buffer = msg->buffers[i];

		int direction = (ipc_buffer->type & 0b0011) >> 0; // in or out (ax or bc)
		int family    = (ipc_buffer->type & 0b1100) >> 2; // ab or xc
    
		if(!(ipc_buffer->type & 0x20)) {
			ipc_buffer_t **list;
			int *count;
      
			if(direction == 0b01) { // IN (ax)
				if(family == 0b01) { // A
					list = a_descriptors;
					count = &num_a_descriptors;
				} else if(family == 0b10) { // X
					list = x_descriptors;
					count = &num_x_descriptors;
				} else {
					return LIBTRANSISTOR_ERR_UNSUPPORTED_BUFFER_TYPE;
				}
			} else if(direction == 0b10) { // OUT (bc)
				if(family == 0b01) { // B
					list = b_descriptors;
					count = &num_b_descriptors;
				} else if(family == 0b10) { // C
					list = c_descriptors;
					count = &num_c_descriptors;
				} else {
					return LIBTRANSISTOR_ERR_UNSUPPORTED_BUFFER_TYPE;
				}
			} else {
				return LIBTRANSISTOR_ERR_UNSUPPORTED_BUFFER_TYPE;
			}

			// make sure we don't overflow our descriptor count fields
			if(*count >= 16) {
				return LIBTRANSISTOR_ERR_TOO_MANY_BUFFERS;
			}

			// add the buffer to the list
			list[(*count)++] = ipc_buffer;
		} else { // flag 0x20 set
			// this isn't entirely correct. the nintendo code is kinda complicated though
			if(ipc_buffer->type == 0x21) { // IN (ax)
				if(num_a_descriptors >= 16 || num_x_descriptors >= 16) {
					return LIBTRANSISTOR_ERR_TOO_MANY_BUFFERS;
				}
				a_descriptors[num_a_descriptors++] = ipc_buffer;
				x_descriptors[num_x_descriptors++] = &null_buffer;
			} else if(ipc_buffer->type == 0x22) { // OUT (bc)
				if(num_b_descriptors >= 16 || num_c_descriptors >= 16) {
					return LIBTRANSISTOR_ERR_TOO_MANY_BUFFERS;
				}
				b_descriptors[num_b_descriptors++] = ipc_buffer;
				c_descriptors[num_c_descriptors++] = &null_buffer;
			} else {
				return LIBTRANSISTOR_ERR_UNSUPPORTED_BUFFER_TYPE;
			}
		}
	}

	// header field 1
	buffer[h++] = msg->message_type
		| (num_x_descriptors << 16)
		| (num_a_descriptors << 20)
		| (num_b_descriptors << 24)
		| (0 << 28); // "w" descriptors

	int c_descriptor_flags = 0;
	if(num_c_descriptors == 1) {
		c_descriptor_flags = 2;
	} else if(num_c_descriptors > 1) {
		c_descriptor_flags = num_c_descriptors + 2;
	}

	int handle_descriptor_enabled = msg->num_copy_handles || msg->num_move_handles || msg->send_pid;

	int size_field_offset = h;
  
	// header field 2
	buffer[h++] = 0 // size. to be filled in later
		| (c_descriptor_flags << 10)
		| (handle_descriptor_enabled << 31);

	// handle descriptor
	if(handle_descriptor_enabled) {
		if(msg->num_copy_handles >= 16 || msg->num_move_handles >= 16) {
			return LIBTRANSISTOR_ERR_TOO_MANY_HANDLES;
		}
    
		buffer[h++] = (msg->send_pid ? 1 : 0)
			| (msg->num_copy_handles << 1)
			| (msg->num_move_handles << 5);

		h+= (msg->send_pid ? 2 : 0);

		for(uint32_t i = 0; i < msg->num_copy_handles; i++) {
			buffer[h++] = msg->copy_handles[i];
		}
		for(uint32_t i = 0; i < msg->num_move_handles; i++) {
			buffer[h++] = msg->move_handles[i];
		}
	}

	// x descriptors
	for(int i = 0; i < num_x_descriptors; i++) {
		int counter = i;
		ipc_buffer_t *buf = x_descriptors[i];

		if((uint64_t) buf->addr >> 39) {
			return LIBTRANSISTOR_ERR_INVALID_BUFFER_ADDRESS;
		}

		if(buf->size >> 16) {
			return LIBTRANSISTOR_ERR_INVALID_BUFFER_SIZE;
		}
    
		buffer[h++] = (uint32_t) (counter
		                     | (((uint64_t) buf->addr >> 36) & 0b111) << 6
		                     | ((counter >> 9) & 0b111) << 9
		                     | (((uint64_t) buf->addr >> 32) & 0b1111) << 12
		                     | (buf->size << 16));

		buffer[h++] = (uint64_t) buf->addr & 0xFFFFFFFF;
	}

	// a & b descriptors
	for(int i = 0; i < num_a_descriptors + num_b_descriptors; i++) {
		ipc_buffer_t *buf = ((i < num_a_descriptors) ? a_descriptors : (b_descriptors - num_a_descriptors))[i];

		if((uint64_t) buf->addr >> 39) {
			return LIBTRANSISTOR_ERR_INVALID_BUFFER_ADDRESS;
		}

		if(buf->size >> 35) {
			return LIBTRANSISTOR_ERR_INVALID_BUFFER_SIZE;
		}

		buffer[h++] = buf->size & 0xFFFFFFFF;
		buffer[h++] = (uint64_t) buf->addr & 0xFFFFFFFF;

		if(buf->type >> 8) {
			return LIBTRANSISTOR_ERR_INVALID_PROTECTION;
		}
    
		buffer[h++] = (uint32_t) ((buf->type >> 6) // flags/permissions
		                     | (((uint64_t) buf->addr >> 36) & 0b111) << 2
		                     | ((buf->size >> 32) & 0b1111) << 24
		                     | (((uint64_t) buf->addr >> 32) & 0b1111) << 28);
	}
  
	// "w" descriptors would go here

	// raw data
	// align head to 4 words
	int raw_data_start = h;
	h = (h + 3) & ~3;
	int pre_padding = h - raw_data_start; // the padding before this section and after it needs to add up to be 0x10 bytes long

	for(uint32_t i = 0; i < msg->data_section_size; i++) {
		buffer[h++] = msg->data_section[i];
	}
	
	h+= 4 - pre_padding;

	int u16_length_count = 0;
	uint16_t *u16_length_list = (uint16_t*) (buffer + h);
  
	// c descriptor u16 length list
	for(int i = 0; i < num_c_descriptors; i++) {
		ipc_buffer_t *buf = c_descriptors[i];
		if(!(buf->type & 0x10)) { // u16 length list flag
			if(buf->size >> 16) {
				return LIBTRANSISTOR_ERR_INVALID_BUFFER_SIZE;
			}
			u16_length_list[u16_length_count++] = (uint16_t) buf->size;
		}
	}
	h+= (u16_length_count + 1) >> 1;

	buffer[size_field_offset]|= h - raw_data_start; // raw data section size
  
	// c descriptors
	for(int i = 0; i < num_c_descriptors; i++) {
		ipc_buffer_t *buf = c_descriptors[i];

		if((uint64_t) buf->addr >> 48) {
			return LIBTRANSISTOR_ERR_INVALID_BUFFER_ADDRESS;
		}

		if(buf->size >> 16) {
			return LIBTRANSISTOR_ERR_INVALID_BUFFER_SIZE;
		}
    
		buffer[h++] = (uint64_t) buf->addr & 0xFFFFFFFF;
		buffer[h++] = ((uint64_t) buf->addr >> 32)
			| ((uint32_t) buf->size << 16);
	}

	return RESULT_OK;
}

result_t ipc_pack_request(uint32_t *marshal_buffer, ipc_request_t *rq, ipc_object_t object) {
	ipc_pack_message_t msg;

	bool to_domain = object.object_id >= 0;
	
	msg.num_buffers = rq->num_buffers;
	msg.buffers = rq->buffers;
	
	if(rq->type & ~0xFFFF) {
		return LIBTRANSISTOR_ERR_INVALID_REQUEST_TYPE;
	}
	msg.message_type = rq->type;

	if(rq->raw_data_size & 3) {
		return LIBTRANSISTOR_ERR_INVALID_RAW_DATA_SIZE;
	}
	int raw_data_words = rq->raw_data_size / sizeof(uint32_t);

	int num_move_handles = rq->num_move_handles;
	if(!to_domain) {
		num_move_handles+= rq->num_objects;
	}

	handle_t move_handles[16];
	if(!to_domain) {
		for(uint32_t i = 0; i < rq->num_objects; i++) {
			ipc_object_t *tobject = rq->objects + i;
			if(tobject->object_id >= 0) {
				return LIBTRANSISTOR_ERR_CANT_SEND_DOMAIN_OBJECT_TO_SESSION;
			}
			move_handles[i] = tobject->session;
		}
		for(uint32_t i = 0; i < rq->num_move_handles; i++) {
			move_handles[rq->num_objects + i] = rq->move_handles[i];
		}
	} else {
		for(uint32_t i = 0; i < rq->num_move_handles; i++) {
			move_handles[i] = rq->move_handles[i];
		}
	}

	msg.num_move_handles = num_move_handles;
	msg.move_handles = move_handles;

	msg.num_copy_handles = rq->num_copy_handles;
	msg.copy_handles = rq->copy_handles;

	msg.send_pid = rq->send_pid;

	uint32_t buffer[0x220 >> 2];
	size_t h = 0;
	
	if(to_domain) {
		if(rq->num_objects > 8) { // server code responds with result code 0x1d60a
			return LIBTRANSISTOR_ERR_TOO_MANY_OBJECTS;
		}
		buffer[h++] = (rq->close_object ? 2 : 1)
			| (rq->num_objects << 8); // we OR in the data payload size later;
		buffer[h++] = object.object_id;
		h+= 2; // alignment
	}

	size_t payload_start = h;
	
	if(!rq->close_object) {
		buffer[h++] = *((uint32_t*) "SFCI");
		buffer[h++] = 0;
		buffer[h++] = rq->request_id;
		buffer[h++] = 0;

		if(rq->raw_data_size > 0x200) {
			return LIBTRANSISTOR_ERR_INVALID_RAW_DATA_SIZE;
		}
		for(int i = 0; i < raw_data_words; i++) {
			buffer[h++] = rq->raw_data[i];
		}
	} else {
		if(!to_domain) {
			return LIBTRANSISTOR_ERR_CANT_CLOSE_SESSIONS_LIKE_DOMAIN_OBJECTS;
		}
		if(
			(rq->type != 4) ||
			(rq->num_buffers != 0) ||
			(rq->raw_data_size != 0) ||
			(rq->send_pid != false) ||
			(rq->num_copy_handles != 0) ||
			(rq->num_move_handles != 0) ||
			(rq->num_objects != 0)) {
			return LIBTRANSISTOR_ERR_MALFORMED_CLOSE_REQUEST;
		}
	}

	if(to_domain) {
		buffer[0]|= ((h - payload_start) * sizeof(*buffer)) << 16;
		for(int i = 0; i < rq->num_objects; i++) {
			if(rq->objects[i].domain != object.domain) {
				return LIBTRANSISTOR_ERR_CANT_SEND_OBJECT_ACROSS_DOMAINS;
			}
			buffer[h++] = rq->objects[i].object_id;
		}
	}
	
	msg.data_section_size = h;
	msg.data_section = buffer;
	
	return ipc_pack_message(marshal_buffer, &msg);
}

result_t ipc_pack_response(uint32_t *marshal_buffer, ipc_response_t *rs, ipc_server_object_t *object) {
	ipc_pack_message_t msg;

	bool from_domain = object->is_domain_object;
	
	msg.num_buffers = rs->num_buffers;
	msg.buffers = rs->buffers;
	
	if(rs->type & ~0xFFFF) {
		return LIBTRANSISTOR_ERR_INVALID_REQUEST_TYPE;
	}
	msg.message_type = rs->type;

	if(rs->raw_data_size & 3) {
		return LIBTRANSISTOR_ERR_INVALID_RAW_DATA_SIZE;
	}
	int raw_data_words = rs->raw_data_size / sizeof(uint32_t);

	int num_move_handles = rs->num_move_handles;
	if(!from_domain) {
		num_move_handles+= rs->num_objects;
	}

	handle_t move_handles[16];
	if(!from_domain) {
		for(uint32_t i = 0; i < rs->num_objects; i++) {
			ipc_server_object_t *tobject = rs->objects[i];
			if(tobject->is_domain_object) {
				return LIBTRANSISTOR_ERR_CANT_SEND_DOMAIN_OBJECT_FROM_SESSION;
			}
			if(tobject->owning_session->client_handle == 0) {
				return LIBTRANSISTOR_ERR_IPCSERVER_CANT_SEND_ROOT_OBJECT;
			}
			move_handles[i] = tobject->owning_session->client_handle;
		}
		for(uint32_t i = 0; i < rs->num_move_handles; i++) {
			move_handles[rs->num_objects + i] = rs->move_handles[i];
		}
	} else {
		for(uint32_t i = 0; i < rs->num_move_handles; i++) {
			move_handles[i] = rs->move_handles[i];
		}
	}

	msg.num_move_handles = num_move_handles;
	msg.move_handles = move_handles;

	msg.num_copy_handles = rs->num_copy_handles;
	msg.copy_handles = rs->copy_handles;

	msg.send_pid = rs->send_pid;

	uint32_t buffer[0x220 >> 2];
	size_t h = 0;
	
	if(from_domain) {
		if(rs->num_objects > 8) {
			return LIBTRANSISTOR_ERR_TOO_MANY_OBJECTS;
		}
		buffer[h++] = rs->num_objects;
		buffer[h++] = 0;
		buffer[h++] = 0;
		buffer[h++] = 0;
		for(uint32_t i = 0; i < rs->num_objects; i++) {
			ipc_server_object_t *tobject = rs->objects[i];
			if(!tobject->is_domain_object) {
				return LIBTRANSISTOR_ERR_CANT_SEND_SESSION_OBJECT_FROM_DOMAIN;
			}
			if(tobject->owning_domain != object->owning_domain) {
				return LIBTRANSISTOR_ERR_CANT_SEND_OBJECT_ACROSS_DOMAINS;
			}
			buffer[h++] = tobject->domain_id;
		}
	}

	buffer[h++] = *((uint32_t*) "SFCO");
	buffer[h++] = 0;
	buffer[h++] = rs->result_code;
	buffer[h++] = 0;
	
	if(rs->raw_data_size > 0x200) {
		return LIBTRANSISTOR_ERR_INVALID_RAW_DATA_SIZE;
	}
	for(int i = 0; i < raw_data_words; i++) {
		buffer[h++] = rs->raw_data[i];
	}
	
	msg.data_section_size = h;
	msg.data_section = buffer;
	
	return ipc_pack_message(marshal_buffer, &msg);
}

result_t ipc_unpack(uint32_t *buffer, ipc_message_t *msg) {
	int h = 0; // h for HEAD

	uint32_t header0 = buffer[h++];
	uint32_t header1 = buffer[h++];
	msg->message_type = header0 & 0xFFFF;

	msg->num_x_descriptors = (header0 >> 16) & 0xF;
	msg->num_a_descriptors = (header0 >> 20) & 0xF;
	msg->num_b_descriptors = (header0 >> 24) & 0xF;
	msg->num_w_descriptors = (header0 >> 28) & 0xF;

	msg->raw_data_section_size = header1 & 0b1111111111;
  
	msg->c_descriptor_flags = (header1 >> 10) & 0xF;
	bool has_handle_descriptor = header1 >> 31;

	msg->num_copy_handles = 0;
	msg->num_move_handles = 0;
	msg->copy_handles = NULL;
	msg->move_handles = NULL;

	msg->has_pid = false;
	msg->pid = 0;
  
	if(has_handle_descriptor) {
		int handle_descriptor = buffer[h++];
		if(handle_descriptor & 1) {
			msg->has_pid = true;
			msg->pid = *(uint64_t*)(buffer + h);
			h+= 2;
		}
		msg->num_copy_handles = (handle_descriptor >> 1) & 0xF;
		msg->num_move_handles = (handle_descriptor >> 5) & 0xF;
		msg->copy_handles = buffer + h; h+= msg->num_copy_handles;
		msg->move_handles = buffer + h; h+= msg->num_move_handles;
	}

	// descriptors
	msg->x_descriptors = buffer + h;
	h+= msg->num_x_descriptors * 2;
	msg->a_descriptors = buffer + h;
	h+= msg->num_a_descriptors * 3;
	msg->b_descriptors = buffer + h;
	h+= msg->num_b_descriptors * 3;
	msg->w_descriptors = buffer + h;
	h+= msg->num_w_descriptors * 3;

	int before = h;
	
	// align head to 4 words
	h = (h + 3) & ~3;
	
	msg->pre_padding = (h - before);
	msg->post_padding = 4 - (h - before);
	msg->data_section = buffer + h;

	h = before + msg->raw_data_section_size;

	msg->c_descriptors = buffer + h;
	
	return RESULT_OK;
}

result_t ipc_unflatten_request(ipc_message_t *msg, ipc_request_fmt_t *rq, struct ipc_server_object_t *object) {
	if(rq->raw_data_size & 3) {
		return LIBTRANSISTOR_ERR_INVALID_RAW_DATA_SIZE;
	}

	bool to_domain = object->is_domain_object;
	size_t raw_data_words = rq->raw_data_size / sizeof(uint32_t);

	struct {
		uint8_t command;
		uint8_t num_objects;
		uint16_t payload_size;
		uint32_t object_id;
	} domain_header;
	
	int h = 0;
	if(to_domain) {
		uint32_t dhead = msg->data_section[h++];
		domain_header.command = dhead & 0xFF; // used in dispatch, assumed to be correct
		domain_header.num_objects = (dhead >> 8) & 0xFF;
		domain_header.payload_size = (dhead >> 16) & 0xFFFF;
		domain_header.object_id = msg->data_section[h++]; // used for dispatch, assumed to be correct
		h+= 2;
	}
	
	if(msg->data_section[h++] != *((uint32_t*) "SFCI")) {
		return LIBTRANSISTOR_ERR_INVALID_IPC_REQUEST_MAGIC;
	}
	h++;
	h++;
	h++;
	
	uint32_t *raw_data = msg->data_section + h;
	  
	if(msg->has_pid != rq->send_pid) {
		return LIBTRANSISTOR_ERR_UNEXPECTED_PID;
	}

	if(msg->num_copy_handles != rq->num_copy_handles) {
		return LIBTRANSISTOR_ERR_UNEXPECTED_COPY_HANDLES;
	}

	if(msg->num_move_handles != rq->num_move_handles + (to_domain ? 0 : rq->num_objects)) {
		return LIBTRANSISTOR_ERR_UNEXPECTED_MOVE_HANDLES;
	}

	if(to_domain && domain_header.num_objects != rq->num_objects) {
		return LIBTRANSISTOR_ERR_UNEXPECTED_OBJECTS;
	}

	if(to_domain && domain_header.payload_size - 4 != rq->raw_data_size) {
		return LIBTRANSISTOR_ERR_UNEXPECTED_RAW_DATA_SIZE;
	}
	
	ipc_buffer_t a_descriptors[16];
	ipc_buffer_t b_descriptors[16];
	ipc_buffer_t c_descriptors[16];
	ipc_buffer_t x_descriptors[16];
  
	 // unpack x descriptors
	h = 0;
	for(uint32_t i = 0; i < msg->num_x_descriptors; i++) {
		uint32_t field = msg->x_descriptors[h++];
		uint64_t addr = 0;
		addr|= (((uint64_t) field >> 6) & 0b111) << 36;
		addr|= (((uint64_t) field >> 12) & 0b1111) << 32;
		addr|= msg->x_descriptors[h++]; // lower 32 bits
		x_descriptors[i].addr = (void*) addr;
		x_descriptors[i].size = field >> 16;
	}

	// unpack a & b descriptors
	h = 0;
	for(uint32_t i = 0; i < msg->num_a_descriptors + msg->num_b_descriptors; i++) {
		ipc_buffer_t *buf = &((i < msg->num_a_descriptors) ? a_descriptors : (b_descriptors - msg->num_a_descriptors))[i];
		uint64_t addr = 0;
		
		buf->size = 0;
		buf->size|= msg->a_descriptors[h++];
		addr|= msg->a_descriptors[h++];

		uint32_t field = msg->a_descriptors[h++];
		uint32_t prot = field & 0b11;
		addr|= (((uint64_t) field >> 2) & 0b111) << 36;
		buf->size|= (((uint64_t) field >> 24) & 0b1111) << 32;
		addr|= (((uint64_t) field >> 28) & 0b1111) << 32;

		buf->addr = (void*) addr;

		uint32_t typemap[] = {0, 1, 0, 2};
		buf->type = typemap[prot] << 6;
	}

	// unpack c descriptors
	//uint16_t *u16_length_list = (uint16_t*) (msg->data_section + msg->raw_data_section_size + 4 + 4 + (to_domain ? 4 + rq->num_objects : 0));
	h = 0;
	uint32_t num_c_descriptors;
	if(msg->c_descriptor_flags == 0) {
		num_c_descriptors = 0;
	} else if(msg->c_descriptor_flags == 1) {
		return LIBTRANSISTOR_ERR_UNIMPLEMENTED;
	} else if(msg->c_descriptor_flags == 2) {
		num_c_descriptors = 1;
	} else {
		num_c_descriptors = msg->c_descriptor_flags - 2;
	}
	for(uint32_t i = 0; i < num_c_descriptors; i++) {
		ipc_buffer_t *buf = &c_descriptors[i];
		uint64_t addr = 0;
		buf->size = 0;

		addr|= msg->c_descriptors[h++];
		uint32_t field = msg->c_descriptors[h++];
		addr|= field & 0xFFFF;
		buf->size|= field >> 16;

		buf->addr = (void*) addr;
	}

	for(uint32_t i = 0; i < rq->num_buffers; i++) {
		rq->buffers[i]->addr = 0;
		rq->buffers[i]->size = 0;
	}
		
	// assign descriptors to buffers
	int c_descriptor_u16_lengths_count = 0;
	uint32_t a_descriptors_assigned = 0; // keep track of how many descriptors we've used already
	uint32_t b_descriptors_assigned = 0;
	uint32_t x_descriptors_assigned = 0;
	uint32_t c_descriptors_assigned = 0;

	for(uint32_t i = 0; i < rq->num_buffers; i++) {
		ipc_buffer_t *ipc_buffer = rq->buffers[i]; // buffer to fill out

		int direction = (ipc_buffer->type & 0b0011) >> 0; // in or out (ax or bc)
		int family    = (ipc_buffer->type & 0b1100) >> 2; // ab or xc

		ipc_buffer_t *desc;
		
		if(!(ipc_buffer->type & 0x20)) {
			ipc_buffer_t *list; // unpacked descriptors
			uint32_t *assigned; // how many descriptors we've used
			uint32_t count; // how many descriptors the message came with
			
			if(direction == 0b01) { // IN (ax)
				if(family == 0b01) { // A
					list = a_descriptors;
					assigned = &a_descriptors_assigned;
					count = msg->num_a_descriptors;
				} else if(family == 0b10) { // X
					list = x_descriptors;
					assigned = &x_descriptors_assigned;
					count = msg->num_a_descriptors;
				} else {
					return LIBTRANSISTOR_ERR_UNSUPPORTED_BUFFER_TYPE;
				}
			} else if(direction == 0b10) { // OUT (bc)
				if(family == 0b01) { // B
					list = b_descriptors;
					assigned = &b_descriptors_assigned;
					count = msg->num_b_descriptors;
				} else if(family == 0b10) { // C
					list = c_descriptors;
					assigned = &c_descriptors_assigned;
					count = num_c_descriptors;
				} else {
					return LIBTRANSISTOR_ERR_UNSUPPORTED_BUFFER_TYPE;
				}
			} else {
				return LIBTRANSISTOR_ERR_UNSUPPORTED_BUFFER_TYPE;
			}

			// make sure we don't run out of descriptors
			if(*assigned >= count) {
				return LIBTRANSISTOR_ERR_TOO_MANY_BUFFERS;
			}

			desc = &list[(*assigned)++];

			// c descriptor u16 list
			if(list == c_descriptors) {
				if(!(ipc_buffer->type & 0x10)) {
					c_descriptor_u16_lengths_count++;
				}
			}
		} else { // flag 0x20 set
			// this may not be entirely correct
			ipc_buffer_t *d1, *d2;
			if(ipc_buffer->type == 0x21) { // IN (ax)
				if(a_descriptors_assigned >= msg->num_a_descriptors || x_descriptors_assigned >= msg->num_x_descriptors) {
					return LIBTRANSISTOR_ERR_TOO_MANY_BUFFERS;
				}
				d1 = &a_descriptors[a_descriptors_assigned++];
				d2 = &x_descriptors[x_descriptors_assigned++];
			} else if(ipc_buffer->type == 0x22) { // OUT (bc)
				if(b_descriptors_assigned >= msg->num_b_descriptors || c_descriptors_assigned >= num_c_descriptors) {
					return LIBTRANSISTOR_ERR_TOO_MANY_BUFFERS;
				}
				d1 = &b_descriptors[b_descriptors_assigned++];
				d2 = &c_descriptors[c_descriptors_assigned++];

				if(!(ipc_buffer->type & 0x10)) {
					c_descriptor_u16_lengths_count++;
				}
			} else {
				return LIBTRANSISTOR_ERR_UNSUPPORTED_BUFFER_TYPE;
			}

			// use the non-NULL descriptor, if there is one
			if(d1->addr != NULL) {
				if(d2->addr != NULL) {
					// not sure what to do in this case
					return LIBTRANSISTOR_ERR_UNIMPLEMENTED;
				}
				desc = d1;
			} else if(d2->addr != NULL) {
				desc = d2;
			} else {
				desc = &null_buffer;
			}
		}

		// copy addr and size
		ipc_buffer->addr = desc->addr;
		ipc_buffer->size = desc->size;
		
		// check the flags for A and B descriptors
		if(ipc_buffer->type & 4) {
			if((ipc_buffer->type & 0xC0) != (desc->type & 0xC0)) {
				printf("protection check failed: 0x%x !~= 0x%x\n", ipc_buffer->type, desc->type);
				return LIBTRANSISTOR_ERR_UNEXPECTED_BUFFER_PROTECTION;
			}
		}
	}

	if((msg->raw_data_section_size
	    - 4 // SFCI, command id
	    - 4 // padding
	    - (to_domain ? 4 + rq->num_objects : 0) // domain header + in objects
	    - ((c_descriptor_u16_lengths_count + 1) >> 1)
		   ) != raw_data_words) {
		return LIBTRANSISTOR_ERR_UNEXPECTED_RAW_DATA_SIZE;
	}
	
	ipc_server_object_t **in_objects = rq->objects;
	if(rq->num_objects > 8) {
		return LIBTRANSISTOR_ERR_TOO_MANY_OBJECTS;
	}
	
	for(uint32_t i = 0; i < rq->num_copy_handles; i++) { rq->copy_handles[i] = msg->copy_handles[i]; }
	int mhi = 0; // move handle index
	if(!to_domain) {
		for(uint32_t i = 0; i < rq->num_objects; i++) {
			session_h handle = msg->move_handles[mhi++];

			ipc_server_session_t *found = NULL;
			
			for(int i = 0; i < MAX_SERVICE_SESSIONS; i++) {
				ipc_server_session_t *s = &(object->owning_session->owning_server->sessions[i]);
				if(s->state != IPC_SESSION_STATE_INVALID && s->handle == handle) {
					found = s;
					break;
				}
			}

			if(found == NULL) {
				return LIBTRANSISTOR_ERR_IPCSERVER_NO_SUCH_OBJECT;
			}

			if(found->is_domain) {
				return LIBTRANSISTOR_ERR_IPCSERVER_SESSION_OBJECT_WAS_DOMAIN;
			}

			if(found->object == NULL) {
				return LIBTRANSISTOR_ERR_IPCSERVER_NO_SUCH_OBJECT;
			}
			
			in_objects[i] = found->object;
		}
	}
	for(uint32_t i = 0; i < rq->num_move_handles; i++) { rq->move_handles[i] = msg->move_handles[mhi++]; }
	
	for(uint32_t i = 0; i < raw_data_words; i++) {
		rq->raw_data[i] = raw_data[h++];
	}

	if(to_domain) {
		result_t r;
		for(uint32_t i = 0; i < rq->num_objects; i++) {
			if((r = ipc_server_domain_get_object(object->owning_domain, msg->data_section[h++], &in_objects[i])) != RESULT_OK) {
				return r;
			}
		}
	}
	
	return RESULT_OK;
}

result_t ipc_unflatten_response(ipc_message_t *msg, ipc_response_fmt_t *rs, ipc_object_t object) {
	if(rs->raw_data_size & 3) {
		return LIBTRANSISTOR_ERR_INVALID_RAW_DATA_SIZE;
	}

	bool from_domain = object.object_id >= 0;  
	size_t raw_data_words = rs->raw_data_size / sizeof(uint32_t);

	if(msg->message_type != 0) {
		return LIBTRANSISTOR_ERR_INVALID_IPC_RESPONSE_TYPE;
	}
	
	int h = 0;
	if(from_domain) {
		h+= 4; // skip domain header for now
	}
	
	if(msg->data_section[h++] != *((uint32_t*) "SFCO")) {
		return LIBTRANSISTOR_ERR_INVALID_IPC_RESPONSE_MAGIC;
	}
	h++;

	// if this isn't ok, none of our other expectations will make
	// sense, so this is the most meaningful result to return.
	result_t response_code = msg->data_section[h++];
	if(response_code != RESULT_OK) {
		return response_code;
	}
	h++;

	uint32_t *raw_data = msg->data_section + h;
  
	if((msg->raw_data_section_size
	    - 4 // SFCI, command id
	    - 4 // padding
	    - (from_domain ? 4 + rs->num_objects : 0) // domain header + out objects
		   ) != raw_data_words) {
		return LIBTRANSISTOR_ERR_UNEXPECTED_RAW_DATA_SIZE;
	}
  
	if(msg->has_pid != rs->has_pid) {
		return LIBTRANSISTOR_ERR_UNEXPECTED_PID;
	}

	if(msg->num_copy_handles != rs->num_copy_handles) {
		return LIBTRANSISTOR_ERR_UNEXPECTED_COPY_HANDLES;
	}

	if(msg->num_move_handles != rs->num_move_handles + (from_domain ? 0 : rs->num_objects)) {
		return LIBTRANSISTOR_ERR_UNEXPECTED_MOVE_HANDLES;
	}

	if(from_domain) {
		struct response_domain_header_t {
			uint32_t num_objects;
			uint32_t unknown1[2]; // supposedly an unaligned uint64_t
			uint32_t unknown2;
		};
		struct response_domain_header_t *domain_header = (struct response_domain_header_t*) msg->data_section;

		if(domain_header->num_objects != rs->num_objects) {
			return LIBTRANSISTOR_ERR_UNEXPECTED_OBJECTS;
		}

		uint32_t *domain_ids = (uint32_t*) (((uint8_t*) domain_header) + 16 + 16 + rs->raw_data_size);
		for(uint32_t i = 0; i < rs->num_objects; i++) {
			rs->objects[i].domain = object.domain;
			rs->objects[i].object_id = domain_ids[i];
			rs->objects[i].is_borrowed = false;
		}
	}
  
	for(uint32_t i = 0; i < rs->num_copy_handles; i++) { rs->copy_handles[i] = msg->copy_handles[i]; }
	int mhi = 0; // move handle index
	if(!from_domain) {
		for(uint32_t i = 0; i < rs->num_objects; i++) {
			rs->objects[i].session = msg->move_handles[mhi++];
			rs->objects[i].object_id = -1;
			rs->objects[i].is_borrowed = false;
		}
	}
	for(uint32_t i = 0; i < rs->num_move_handles; i++) { rs->move_handles[i] = msg->move_handles[mhi++]; }
	for(uint32_t i = 0; i < raw_data_words; i++) {
		rs->raw_data[i] = raw_data[i];
	}
  
	return RESULT_OK;
}

result_t ipc_convert_to_domain(ipc_object_t *object, ipc_domain_t *domain) {
	if(object->is_borrowed) {
		return LIBTRANSISTOR_ERR_REFUSAL_TO_CONVERT_BORROWED_OBJECT;
	}
	
	ipc_object_t session = *object;  
	domain->session = session.session;

	if(object->object_id != -1) {
		return LIBTRANSISTOR_ERR_ALREADY_A_DOMAIN;
	}

	object->domain = domain;
  
	ipc_request_t rq = ipc_default_request;
	rq.type = 5;
	rq.request_id = 0;

	ipc_response_fmt_t rs = ipc_default_response_fmt;
	rs.raw_data_size = sizeof(object->object_id);
	rs.raw_data = (uint32_t*) &(object->object_id);

	return ipc_send(session, &rq, &rs);
}

result_t ipc_send(ipc_object_t object, ipc_request_t *rq, ipc_response_fmt_t *rs) {
	result_t r;
	uint32_t *tls = get_tls()->ipc_buffer;
	memset(tls, 0, 0x1f8);
	r = ipc_pack_request(tls, rq, object); if(r) { return r; }
	if(ipc_debug_flag) {
		char buf[0x1f8];
		memcpy(buf, tls, sizeof(buf));
		ipc_debug_flag = 0;
		printf("out request:\n");
		hexdump(buf, 0x50);
		memcpy(tls, buf, sizeof(buf));
		ipc_debug_flag = 1;
	}
	r = svcSendSyncRequest(object.object_id >= 0 ? object.domain->session : object.session);
	if(r) {
		return r;
	}
	if(ipc_debug_flag) {
		char buf[0x1f8];
		memcpy(buf, tls, sizeof(buf));
		ipc_debug_flag = 0;
		printf("in response:\n");
		hexdump(buf, 0x50);
		memcpy(tls, buf, sizeof(buf));
		ipc_debug_flag = 1;
	}
	ipc_message_t msg;
	r = ipc_unpack(tls, &msg); if(r) { return r; }
	r = ipc_unflatten_response(&msg, rs, object); if(r) { return r; }

	return RESULT_OK;
}

result_t ipc_close(ipc_object_t object) {
	if(object.is_borrowed) {
		return RESULT_OK; // we're not allowed to close borrowed objects, and we would also like to handle this transparently
	}
	
	if(object.object_id < 0) {
		return svcCloseHandle(object.session);
	}
  
	ipc_request_t rq = ipc_default_request;
	rq.close_object = true;

	uint32_t *tls = get_tls()->ipc_buffer;
  
	result_t r;
	r = ipc_pack_request(tls, &rq, object); if(r) { return r; }
	r = svcSendSyncRequest(object.domain->session); if (r) { return r; }

	// remote end doesn't seem to actually write a response
  
	return RESULT_OK;
}

result_t ipc_close_domain(ipc_domain_t domain) {
	return svcCloseHandle(domain.session);
}
