#include<libtransistor/types.h>
#include<libtransistor/svc.h>
#include<libtransistor/tls.h>
#include<libtransistor/err.h>
#include<libtransistor/ipc.h>
#include<libtransistor/ipcserver.h>

#include<string.h>

result_t ipc_server_create(ipc_server_t *srv, port_h port, ipc_server_object_factory_t object_factory) {
	srv->port = port;
	srv->object_factory = object_factory;
	for(int i = 0; i < MAX_SERVICE_SESSIONS; i++) {
		srv->sessions[i].state = IPC_SESSION_STATE_INVALID;
	}
	return RESULT_OK;
}

static void hipc_manager_dispatch(ipc_server_object_t *obj, ipc_message_t *msg, uint32_t rqid);
static void hipc_manager_close(ipc_server_object_t *obj);

static uint64_t make_timestamp() {
	static uint64_t timestamp = 0; // svcGetSystemTick might make a suitable substitute
	return timestamp++;
}

result_t ipc_server_create_session(ipc_server_t *srv, session_h server_side, session_h client_side, ipc_server_object_t *object) {
	int i = 0;
	for(; i < MAX_SERVICE_SESSIONS; i++) {
		if(srv->sessions[i].state == IPC_SESSION_STATE_INVALID) {
			break;
		}
	}
	if(i == MAX_SERVICE_SESSIONS) {
		svcCloseHandle(server_side);
		if(client_side != 0) {
			svcCloseHandle(client_side);
		}
		return LIBTRANSISTOR_ERR_IPCSERVER_TOO_MANY_SESSIONS;
	}
	ipc_server_session_t *sess = &(srv->sessions[i]);
	sess->handle = server_side;
	sess->client_handle = client_side;
	sess->state = IPC_SESSION_STATE_INITIALIZING;
	sess->is_domain = false;
	sess->owning_server = srv;
	sess->hipc_manager_object.userdata = NULL;
	sess->hipc_manager_object.is_domain_object = false;
	sess->hipc_manager_object.owning_domain = NULL;
	sess->hipc_manager_object.owning_session = sess;
	sess->hipc_manager_object.dispatch = hipc_manager_dispatch;
	sess->hipc_manager_object.close = hipc_manager_close;
	sess->domain.owning_session = sess;
	for(int i = 0; i < MAX_DOMAIN_OBJECTS; i++) {
		sess->domain.objects[i] = NULL;
	}
	sess->active_object = NULL;
	sess->object = object;
	sess->object->is_domain_object = false;
	sess->object->domain_id = 0;
	sess->object->owning_domain = NULL;
	sess->object->owning_session = sess;
	sess->last_touch_timestamp = make_timestamp(); // get lowest priority
	sess->state = IPC_SESSION_STATE_LISTENING;
	return RESULT_OK;
}

result_t ipc_server_accept_session(ipc_server_t *srv) {
	result_t r;
	session_h handle;
	if((r = svcAcceptSession(&handle, srv->port)) != RESULT_OK) {
		return r;
	}

	ipc_server_object_t *object;
	if((r = srv->object_factory(&object)) != RESULT_OK) {
		svcCloseHandle(handle);
		return r;
	}
	
	return ipc_server_create_session(srv, handle, 0, object);
}

int session_touch_timestamp_compare(const void *va, const void *vb) {
	const ipc_server_session_t *a = va;
	const ipc_server_session_t *b = vb;

	return (a->last_touch_timestamp > b->last_touch_timestamp) - (a->last_touch_timestamp < b->last_touch_timestamp);
}

result_t ipc_server_process(ipc_server_t *srv, uint64_t timeout) {
	while(1) {
		handle_t handles[MAX_SERVICE_SESSIONS+1];
		ipc_server_session_t *sessions[MAX_SERVICE_SESSIONS];
		int num_listening_sessions = 0;
		handles[0] = srv->port;
		
		for(int i = 0; i < MAX_SERVICE_SESSIONS; i++) {
			if(srv->sessions[i].state == IPC_SESSION_STATE_LISTENING) {
				sessions[num_listening_sessions] = &(srv->sessions[i]);
				num_listening_sessions++;
			}
		}

		qsort(sessions, num_listening_sessions, sizeof(sessions[0]), session_touch_timestamp_compare);
		
		for(int i = 0; i < num_listening_sessions; i++) {
			handles[1 + i] = sessions[i]->handle;
		}
		
		result_t r;
		uint32_t handle_index;
		r = svcWaitSynchronization(&handle_index, handles, num_listening_sessions + 1, timeout);
		if(r == 0xEA01) { // timeout
			// nothing was signalled, so touch all sessions
			for(int i = 0; i < num_listening_sessions; i++) {
				sessions[i]->last_touch_timestamp = make_timestamp();
			}
			return RESULT_OK;
		}
		if(r != RESULT_OK) {
			return r;
		}
		timeout = 0; // if we loop again, don't wait any longer than we wanted to

		if(handle_index == 0) { // port
			if((r = ipc_server_accept_session(srv)) != RESULT_OK) {
				return r;
			}
		} else { // session
			// mark all sessions before or at the signalled one as touched.
			// the important part is that we *don't* touch the sessions after it,
			// meaning they will be sorted earlier on the next iteration of the loop
			// and get first priority in case we missed them with this iteration.
			// that way, no session can DoS the IPC server.
			for(int i = 0; i <= handle_index-1; i++) {
				sessions[i]->last_touch_timestamp = make_timestamp();
			}
			ipc_server_session_receive(sessions[handle_index-1], timeout); // timeout is 0, but I think it still makes sense to pass it
		}
	}
}

result_t ipc_server_destroy(ipc_server_t *srv) {
	svcCloseHandle(srv->port);
	for(int i = 0; i < MAX_SERVICE_SESSIONS; i++) {
		if(srv->sessions[i].state != IPC_SESSION_STATE_INVALID) {
			ipc_server_session_close(&srv->sessions[i]);
		}
	}
	return RESULT_OK;
}

result_t ipc_server_object_register(ipc_server_object_t *parent, ipc_server_object_t *child) {
	result_t r;
	if(parent->is_domain_object) {
		return ipc_server_domain_add_object(parent->owning_domain, child);
	} else {
		session_h server;
		session_h client;
		if((r = svcCreateSession(&server, &client, false, 0)) != RESULT_OK) {
			return r;
		}
		return ipc_server_create_session(parent->owning_session->owning_server, server, client, child);
	}
}

result_t ipc_server_object_reply(ipc_server_object_t *obj, ipc_response_t *rs) {
	if(obj->owning_session->state != IPC_SESSION_STATE_PROCESSING) {
		return LIBTRANSISTOR_ERR_IPCSERVER_INVALID_SESSION_STATE;
	}
	if(obj->owning_session->active_object != obj) {
		return LIBTRANSISTOR_ERR_IPCSERVER_OBJECT_NOT_ACTIVE;
	}

	result_t r;
	
	uint32_t *tls = get_tls();
	uint32_t handle_index;
	if((r = ipc_pack_response(tls, rs, obj)) != RESULT_OK) {
		return r;
	}
	r = svcReplyAndReceive(&handle_index, NULL, 0, obj->owning_session->handle, 0);
	if(r != 0xea01) { // we should timeout instantly, as we're not listening on any handles
		obj->owning_session->state = IPC_SESSION_STATE_ERRORED;
		return r;
	}

	obj->owning_session->active_object = NULL;
	obj->owning_session->state = IPC_SESSION_STATE_LISTENING;
	return RESULT_OK;
}

result_t ipc_server_session_receive(ipc_server_session_t *sess, uint64_t timeout) {
	result_t r;
	uint32_t handle_index = 0;
	session_h handle = sess->handle;

	if(sess->state != IPC_SESSION_STATE_LISTENING) {
		return LIBTRANSISTOR_ERR_IPCSERVER_INVALID_SESSION_STATE;
	}

	r = svcReplyAndReceive(&handle_index, &handle, 1, 0, timeout);

	if(r != RESULT_OK) {
		goto failure;
	}

	sess->state = IPC_SESSION_STATE_PROCESSING;
	
	uint32_t *tls = get_tls();
	memcpy(sess->message_buffer, tls, 0x100);
	
	ipc_message_t msg;
	if((r = ipc_unpack((uint32_t*) sess->message_buffer, &msg)) != RESULT_OK) {
		goto failure;
	}

	uint32_t *raw_data = msg.data_section;
	size_t raw_data_size = msg.raw_data_section_size * sizeof(uint32_t);

	ipc_server_object_t *dispatch = NULL;
	if(msg.message_type == 5) {
		dispatch = &sess->hipc_manager_object;
	} else if(msg.message_type == 4) {
		if(sess->is_domain) {
			uint16_t data_size = raw_data[0] >> 16;
			
			if((r = ipc_server_domain_get_object(&sess->domain, raw_data[1], &dispatch)) != RESULT_OK) {
				goto failure;
			}
			// TODO: check that raw_data_size is big enough
			raw_data+= 4;
			raw_data_size = data_size;
		} else {
			dispatch = sess->object;
		}
	} else {
		goto failure;
	}

	sess->active_object = dispatch;

	dispatch->dispatch(dispatch, &msg, raw_data[2]); // dispatch must handle failure itself

	return RESULT_OK;

failure:
	sess->state = IPC_SESSION_STATE_ERRORED;
	return ipc_server_session_close(sess);
}

result_t ipc_server_domain_add_object(ipc_server_domain_t *domain, ipc_server_object_t *object) {
	for(int i = 0; i < MAX_DOMAIN_OBJECTS; i++) {
		if(domain->objects[i] == NULL) {
			domain->objects[i] = object;
			object->is_domain_object = true;
			object->domain_id = i;
			object->owning_session = domain->owning_session;
			object->owning_domain = domain;
			return RESULT_OK;
		}
	}
	return LIBTRANSISTOR_ERR_TOO_MANY_OBJECTS;
}

result_t ipc_server_domain_get_object(ipc_server_domain_t *domain, uint32_t object_id, ipc_server_object_t **object) {
	if(object_id >= MAX_DOMAIN_OBJECTS) {
		return LIBTRANSISTOR_ERR_IPCSERVER_NO_SUCH_OBJECT;
	}
	if(domain->objects[object_id] == NULL) {
		return LIBTRANSISTOR_ERR_IPCSERVER_NO_SUCH_OBJECT;
	}
	*object = domain->objects[object_id];
	return RESULT_OK;
}

result_t ipc_server_session_close(ipc_server_session_t *sess) {
	if(sess->state == IPC_SESSION_STATE_INVALID) {
		return LIBTRANSISTOR_ERR_IPCSERVER_INVALID_SESSION_STATE;
	}

	svcCloseHandle(sess->handle);
	if(sess->client_handle != 0) {
		svcCloseHandle(sess->client_handle);
	}
	ipc_server_object_close(&sess->hipc_manager_object);
	if(sess->object != NULL) {
		ipc_server_object_close(sess->object);
	}
	for(int i = 0; i < MAX_DOMAIN_OBJECTS; i++) {
		if(sess->domain.objects[i] != NULL) {
			ipc_server_object_close(sess->domain.objects[i]);
		}
	}
	
	sess->state = IPC_SESSION_STATE_INVALID;
		
	return RESULT_OK;
}

result_t ipc_server_object_close(ipc_server_object_t *obj) {
	if(obj->close != NULL) {
		obj->close(obj);
	}
	return RESULT_OK;
}

static void hipc_manager_dispatch(ipc_server_object_t *obj, ipc_message_t *msg, uint32_t rqid) {
	// TODO: implement this
}

static void hipc_manager_close(ipc_server_object_t *obj) {
}
