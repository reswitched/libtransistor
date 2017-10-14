#include<libtransistor/ipc.h>
#include<libtransistor/tls.h>
#include<libtransistor/svc.h>
#include<libtransistor/err.h>
#include<libtransistor/util.h>

ipc_buffer_t null_buffer = {
  .addr = 0,
  .size = 0,
  .type = 0
};

ipc_object_t ipc_null_object = {
  .session = 0,
  .object_id = -1
};

ipc_request_t ipc_default_request = {
  .type = 4,
  .num_buffers = 0,
  .buffers = NULL,
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

result_t ipc_marshal(u32 *buffer, ipc_request_t *rq, ipc_object_t object) {
  int h = 0; // h is for HEAD
  
  ipc_buffer_t *a_descriptors[16];
  ipc_buffer_t *b_descriptors[16];
  ipc_buffer_t *c_descriptors[16];
  ipc_buffer_t *x_descriptors[16];
  
  int num_a_descriptors = 0, num_b_descriptors = 0,
    num_c_descriptors = 0, num_x_descriptors = 0;

  bool to_domain = object.object_id >= 0;
  
  // group buffers by descriptor type
  for(int i = 0; i < rq->num_buffers; i++) {
    ipc_buffer_t *buffer = rq->buffers[i];

    int direction = (buffer->type & 0b0011) >> 0; // in or out (ax or bc)
    int family    = (buffer->type & 0b1100) >> 2; // ab or xc
    
    if(!(buffer->type & 0x20)) {
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
      list[(*count)++] = buffer;
    } else { // flag 0x20 set
      // this isn't entirely correct. the nintendo code is kinda complicated though
      if(buffer->type == 0x21) { // IN (ax)
        if(num_a_descriptors >= 16 || num_x_descriptors >= 16) {
          return LIBTRANSISTOR_ERR_TOO_MANY_BUFFERS;
        }
        a_descriptors[num_a_descriptors++] = buffer;
        x_descriptors[num_x_descriptors++] = &null_buffer;
      } else if(buffer->type == 0x22) { // OUT (bc)
        if(num_b_descriptors >= 16 || num_c_descriptors >= 16) {
          return LIBTRANSISTOR_ERR_TOO_MANY_BUFFERS;
        }
        b_descriptors[num_b_descriptors++] = buffer;
        c_descriptors[num_c_descriptors++] = &null_buffer;
      } else {
        return LIBTRANSISTOR_ERR_UNSUPPORTED_BUFFER_TYPE;
      }
    }
  }

  // type must fit within 16 bits
  if(rq->type & ~0xFFFF) {
    return LIBTRANSISTOR_ERR_INVALID_REQUEST_TYPE;
  }

  // header field 1
  buffer[h++] = rq->type
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

  if(rq->raw_data_size & 3) {
    return LIBTRANSISTOR_ERR_INVALID_RAW_DATA_SIZE;
  }
  
  int raw_data_words = rq->raw_data_size / sizeof(uint32_t);
  int raw_data_section_size = raw_data_words
    + 4 // SFCI + command ID
    + 4 // padding
    + (to_domain ? 4 + rq->num_objects : 0); // domain header and in objects

  int num_move_handles = rq->num_move_handles;
  if(!to_domain) { // not sure if this is actually legit or not
    num_move_handles+= rq->num_objects;
  }
  
  int handle_descriptor_enabled = rq->num_copy_handles || num_move_handles || rq->send_pid;

  // header field 2
  buffer[h++] = raw_data_section_size
    | (c_descriptor_flags << 10)
    | (handle_descriptor_enabled << 31);

  // handle descriptor
  if(handle_descriptor_enabled) {
    if(rq->num_copy_handles >= 16 || num_move_handles >= 16) {
      return LIBTRANSISTOR_ERR_TOO_MANY_HANDLES;
    }
    
    buffer[h++] = (rq->send_pid ? 1 : 0)
      | (rq->num_copy_handles << 1)
      | (rq->num_move_handles << 5);

    h+= (rq->send_pid ? 2 : 0);

    for(int i = 0; i < rq->num_copy_handles; i++) {
      buffer[h++] = rq->copy_handles[i];
    }
    if(!to_domain) {
      for(int i = 0; i < rq->num_objects; i++) {
        ipc_object_t *tobject = rq->objects + i;
        if(tobject->object_id >= 0) {
          return LIBTRANSISTOR_ERR_CANT_SEND_DOMAIN_OBJECT_TO_SESSION;
        }
        buffer[h++] = tobject->session;
      }
    }
    for(int i = 0; i < rq->num_move_handles; i++) {
      buffer[h++] = rq->move_handles[i];
    }
  }

  // x descriptors
  for(int i = 0; i < num_x_descriptors; i++) {
    int counter = i;
    ipc_buffer_t *buf = x_descriptors[i];

    if((u64) buf->addr >> 39) {
      return LIBTRANSISTOR_ERR_INVALID_BUFFER_ADDRESS;
    }

    if(buf->size >> 16) {
      return LIBTRANSISTOR_ERR_INVALID_BUFFER_SIZE;
    }
    
    buffer[h++] = counter
      | (((u64) buf->addr >> 36) & 0b111) << 6
      | ((counter >> 9) & 0b111) << 9
      | (((u64) buf->addr >> 32) & 0b1111) << 12
      | (buf->size << 16);

    buffer[h++] = (u64) buf->addr & 0xFFFFFFFF;
  }

  // a & b descriptors
  for(int i = 0; i < num_a_descriptors + num_b_descriptors; i++) {
    ipc_buffer_t *buf = ((i < num_a_descriptors) ? a_descriptors : (b_descriptors - num_a_descriptors))[i];

    if((u64) buf->addr >> 39) {
      dbg_printf("a descriptor addr too long: %p", buf->addr);
      return LIBTRANSISTOR_ERR_INVALID_BUFFER_ADDRESS;
    }

    if(buf->size >> 35) {
      return LIBTRANSISTOR_ERR_INVALID_BUFFER_SIZE;
    }

    buffer[h++] = buf->size & 0xFFFFFFFF;
    buffer[h++] = (u64) buf->addr & 0xFFFFFFFF;

    if(buf->type >> 8) {
      return LIBTRANSISTOR_ERR_INVALID_PROTECTION;
    }
    
    buffer[h++] = (buf->type >> 6) // flags/permissions
      | (((u64) buf->addr >> 36) & 0b111) << 2
      | ((buf->size >> 32) & 0b1111) << 24
      | (((u64) buf->addr >> 32) & 0b1111) << 28;
  }
  
  // "w" descriptors would go here

  // raw data
  // align head to 4 words
  int raw_data_start = h;
  h = (h + 3) & ~3;
  int pre_padding = h - raw_data_start; // the padding before this section and after it needs to add up to be 0x10 bytes long

  int domain_header_location = h;
  
  if(to_domain) {
    if(rq->num_objects > 8) { // server code responds with result code 0x1d60a
      return LIBTRANSISTOR_ERR_TOO_MANY_OBJECTS;
    }
    buffer[h++] = (rq->close_object ? 2 : 1)
      | (rq->num_objects << 8); // we OR in the data payload size later;
    buffer[h++] = object.object_id;
    h+= 2; // alignment
  }

  int payload_start = h;

  if(!rq->close_object) {
    buffer[h++] = *((uint32_t*) "SFCI");
    buffer[h++] = 0;
    buffer[h++] = rq->request_id;
    buffer[h++] = 0;
    
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
    buffer[domain_header_location]|= ((h - payload_start) * sizeof(*buffer)) << 16;
    for(int i = 0; i < rq->num_objects; i++) {
      if(rq->objects[i].domain != object.domain) {
        return LIBTRANSISTOR_ERR_CANT_SEND_OBJECT_ACROSS_DOMAINS;
      }
      buffer[h++] = rq->objects[i].object_id;
    }
  }

  h+= 0x10 - pre_padding;

  int u16_length_count;
  uint16_t *u16_length_list = (uint16_t*) (buffer + h);
  
  // c descriptor u16 length list
  for(int i = 0; i < num_c_descriptors; i++) {
    ipc_buffer_t *buf = c_descriptors[i];
    if(!(buf->type & 0x10)) { // u16 length list flag
      if(buf->size >> 16) {
        return LIBTRANSISTOR_ERR_INVALID_BUFFER_SIZE;
      }
      u16_length_list[u16_length_count++] = buf->size;
    }
  }
  h+= (u16_length_count + 1) >> 1;
  
  // c descriptors
  for(int i = 0; i < num_c_descriptors; i++) {
    ipc_buffer_t *buf = c_descriptors[i];

    if((u64) buf->addr >> 48) {
      return LIBTRANSISTOR_ERR_INVALID_BUFFER_ADDRESS;
    }

    if(buf->size >> 16) {
      return LIBTRANSISTOR_ERR_INVALID_BUFFER_SIZE;
    }
    
    buffer[h++] = (u64) buf->addr & 0xFFFFFFFF;
    buffer[h++] = ((u64) buf->addr >> 32)
      | (buf->size << 16);
  }

  return RESULT_OK;
}

result_t ipc_unmarshal(u32 *buffer, ipc_response_fmt_t *rs, ipc_object_t object) {
  if(rs->raw_data_size & 3) {
    return LIBTRANSISTOR_ERR_INVALID_RAW_DATA_SIZE;
  }

  bool from_domain = object.object_id >= 0;
  
  int raw_data_words = rs->raw_data_size / sizeof(uint32_t);
  
  int h = 0; // h for HEAD

  u32 header0 = buffer[h++];
  u32 header1 = buffer[h++];
  int response_type = header0 & 0xFFFF;

  if(response_type != 0) {
    return LIBTRANSISTOR_ERR_INVALID_IPC_RESPONSE_TYPE;
  }
  
  int num_x_descriptors = (header0 >> 16) & 0xF;
  int num_a_descriptors = (header0 >> 20) & 0xF;
  int num_b_descriptors = (header0 >> 24) & 0xF;
  int num_w_descriptors = (header0 >> 28) & 0xF;

  int raw_data_section_size = header1 & 0b1111111111;
  
  int c_descriptor_flags = (header1 >> 10) & 0xF;
  bool has_handle_descriptor = header1 >> 31;

  int num_copy_handles = 0;
  int num_move_handles = 0;
  handle_t *copy_handles;
  handle_t *move_handles;

  bool has_pid = false;
  int pid;
  
  if(has_handle_descriptor) {
    int handle_descriptor = buffer[h++];
    if(handle_descriptor & 1) {
      has_pid = true;
      pid = *(u64*)(buffer + h);
      h+= 2;
    }
    num_copy_handles = (handle_descriptor >> 1) & 0xF;
    num_move_handles = (handle_descriptor >> 5) & 0xF;
    copy_handles = buffer + h; h+= num_copy_handles;
    move_handles = buffer + h; h+= num_move_handles;
  }

  // skip descriptors
  h+= num_x_descriptors * 2;
  h+= num_a_descriptors * 3;
  h+= num_b_descriptors * 3;
  h+= num_w_descriptors * 3;

  // align head to 4 words
  int raw_data_start = h;
  h = (h + 3) & ~3;

  int domain_header_location = h;

  if(from_domain) {
    h+= 4;
  }
  
  if(buffer[h++] != *((uint32_t*) "SFCO")) {
    return LIBTRANSISTOR_ERR_INVALID_IPC_RESPONSE_MAGIC;
  }
  h++;

  // if this isn't ok, none of our other expectations will make
  // sense, so this is the most meaningful result to return.
  result_t response_code = buffer[h++];
  if(response_code != RESULT_OK) {
    return response_code;
  }
  h++;

  u32 *raw_data = buffer + h;
  
  if((raw_data_section_size
      - 4 // SFCI, command id
      - 4 // padding
      - (from_domain ? 4 + rs->num_objects : 0) // domain header + out objects
      ) != raw_data_words) {
    return LIBTRANSISTOR_ERR_UNEXPECTED_RAW_DATA_SIZE;
  }
  
  if(has_pid != rs->has_pid) {
    return LIBTRANSISTOR_ERR_UNEXPECTED_PID;
  }

  if(num_copy_handles != rs->num_copy_handles) {
    return LIBTRANSISTOR_ERR_UNEXPECTED_COPY_HANDLES;
  }

  if(num_move_handles != rs->num_move_handles + (from_domain ? 0 : rs->num_objects)) {
    return LIBTRANSISTOR_ERR_UNEXPECTED_MOVE_HANDLES;
  }

  if(from_domain) {
    uint8_t *domain_header = (uint8_t*) (buffer + domain_header_location);
    uint8_t command = domain_header[0];
    uint8_t object_count = domain_header[1];
    uint16_t raw_data_size = ((uint16_t*) domain_header)[1];

    if(command != 0) {
      return LIBTRANSISTOR_ERR_UNEXPECTED_DOMAIN_HEADER_COMMAND;
    }

    if(object_count != rs->num_objects) {
      return LIBTRANSISTOR_ERR_UNEXPECTED_OBJECTS;
    }

    uint32_t *domain_ids = (uint32_t*) (domain_header + 16 + raw_data_size);
    for(int i = 0; i < rs->num_objects; i++) {
      rs->objects[i].domain = object.domain;
      rs->objects[i].object_id = domain_ids[i];
    }
  }
  
  for(int i = 0; i < rs->num_copy_handles; i++) { rs->copy_handles[i] = copy_handles[i]; }
  int mhi = 0; // move handle index
  if(!from_domain) {
    for(int i = 0; i < rs->num_objects; i++) {
      rs->objects[i].session = move_handles[mhi++];
      rs->objects[i].object_id = -1;
    }
  }
  for(int i = 0; i < rs->num_move_handles; i++) { rs->move_handles[i] = move_handles[mhi++]; }
  for(int i = 0; i < raw_data_words; i++) {
    rs->raw_data[i] = raw_data[i];
  }
  
  return RESULT_OK;
}

result_t ipc_convert_to_domain(ipc_object_t *object, ipc_domain_t *domain) {
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
  u32 *tls = get_tls();
  r = ipc_marshal(tls, rq, object); if(r) { return r; }
  r = svcSendSyncRequest(object.object_id >= 0 ? object.domain->session : object.session); if(r) { return r; }
  r = ipc_unmarshal(tls, rs, object); if(r) { return r; }

  return RESULT_OK;
}

result_t ipc_close(ipc_object_t object) {
  if(object.object_id < 0) {
    return svcCloseHandle(object.session);
  }
  
  ipc_request_t rq = ipc_default_request;
  rq.close_object = true;

  u32 *tls = get_tls();
  
  result_t r;
  r = ipc_marshal(tls, &rq, object); if(r) { return r; }
  r = svcSendSyncRequest(object.domain->session); if (r) { return r; }

  // remote end doesn't seem to actually write a response
  
  return RESULT_OK;
}

result_t ipc_close_domain(ipc_domain_t domain) {
  return svcCloseHandle(domain.session);
}
