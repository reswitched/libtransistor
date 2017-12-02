#pragma once

#include<libtransistor/types.h>
#include<libtransistor/ipc.h>

#define MAX_SERVICE_SESSIONS 63
#define MAX_DOMAIN_OBJECTS 512

struct ipc_server_object_t;
struct ipc_server_domain_t;
struct ipc_server_session_t;

typedef struct ipc_server_object_t {
	void *userdata;

	bool is_domain_object;
	uint32_t domain_id;
	struct ipc_server_domain_t *owning_domain;
	struct ipc_server_session_t *owning_session;
	
	// raw_data points to SFCI
	result_t (*dispatch)(struct ipc_server_object_t *obj, ipc_message_t *msg, void *raw_data, size_t raw_data_size);
	result_t (*close)();
} ipc_server_object_t;

typedef struct ipc_server_domain_t {
	ipc_server_object_t *objects[MAX_DOMAIN_OBJECTS];
	struct ipc_server_session_t *owning_session;
} ipc_server_domain_t;

typedef enum {
	IPC_SESSION_STATE_INVALID,
	IPC_SESSION_STATE_INITIALIZING,
	IPC_SESSION_STATE_LISTENING,
	IPC_SESSION_STATE_PROCESSING,
} ipc_server_session_state_t;

typedef struct ipc_server_session_t {
	session_h handle;
	bool is_domain;
	ipc_server_object_t hipc_manager_object;
	ipc_server_object_t *active_object;
	ipc_server_object_t *object;
	ipc_server_domain_t domain;
	ipc_server_session_state_t state;
	uint8_t message_buffer[0x100];
} ipc_server_session_t;

/*
  you are expected to initialize `userdata`, `dispatch`, and `close`.
  libtransistor will initialize all other fields.
 */
typedef result_t (*ipc_server_object_factory_t)(ipc_server_object_t **obj);

typedef struct {
	port_h port;
	ipc_server_session_t sessions[MAX_SERVICE_SESSIONS];
	ipc_server_object_factory_t object_factory;
} ipc_server_t;

result_t ipc_server_create(ipc_server_t *srv, port_h port, ipc_server_object_factory_t object_factory);
result_t ipc_server_accept_session(ipc_server_t *srv);
result_t ipc_server_process(ipc_server_t *srv, uint64_t timeout);
result_t ipc_server_destroy(ipc_server_t *srv);

result_t ipc_server_object_reply(ipc_server_object_t *obj, ipc_response_t *rs);

result_t ipc_server_domain_get_object(ipc_server_domain_t *domain, uint32_t object_id, ipc_server_object_t **object);

result_t ipc_server_session_receive(ipc_server_session_t *sess, uint64_t timeout);
result_t ipc_server_session_close(ipc_server_session_t *sess);
