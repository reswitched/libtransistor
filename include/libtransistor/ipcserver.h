/**
 * @file libtransistor/ipcserver.h
 * @brief IPC Server data structures and functions
 *
 */

#pragma once

#ifdef __cplusplus
extern "C" {
#endif

#include<libtransistor/types.h>
#include<libtransistor/ipc.h>
#include<libtransistor/waiter.h>

#define MAX_SERVICE_PORTS 63
#define MAX_SERVICE_SESSIONS 63 ///< Maximum number of sessions that can be connected to an IPC server
#define MAX_DOMAIN_OBJECTS 512 ///< Maximum number of objects per domain

struct ipc_server_object_t;
struct ipc_server_domain_t;
struct ipc_server_session_t;
struct ipc_server;

/**
 * @struct ipc_server_object_t
 * @brief Represents the server side of an IPC object
 */
typedef struct ipc_server_object_t {
	void *userdata; ///< Pointer to user data

	bool is_domain_object; ///< Whether or not this object is part of a domain
	uint32_t domain_id; ///< This object's ID within its owning domain, if applicable
	struct ipc_server_domain_t *owning_domain; ///< The domain that owns this object, if applicable
	struct ipc_server_session_t *owning_session; ///< The session that owns this object
	
	// raw_data points to SFCI
	/**
	 * @brief IPC message handler function
	 *
	 * @param obj The object that the incoming message is being sent to
	 * @param msg The incoming message, to be used with \ref ipc_unflatten_request.
	 * @param request_id The request ID from the incoming message
	 *
	 * Upon entering this function, the object's owning session will be placed in the \ref IPC_SESSION_STATE_PROCESSING state. To finish processing, either \ref ipc_server_object_reply or \ref ipc_server_object_close must be called. These may be called after returning from the dispatch function, to allow for asynchronous handling of messages.
	 */
	void (*dispatch)(struct ipc_server_object_t *obj, ipc_message_t *msg, uint32_t request_id);

	/**
	 * @brief Release any resources associated with this object
	 *
	 * This function should also free the object itself, if it was dynamically allocated.
	 */
	void (*close)(struct ipc_server_object_t *obj);
} ipc_server_object_t;

/**
 * @struct ipc_server_domain_t
 * @brief Represents the server side of an IPC object domain
 */
typedef struct ipc_server_domain_t {
	ipc_server_object_t *objects[MAX_DOMAIN_OBJECTS]; ///< The objects within this domain
	struct ipc_server_session_t *owning_session; ///< The session that owns this domain
} ipc_server_domain_t;

typedef enum {
	IPC_SESSION_STATE_INVALID, ///< Session does not exist
	IPC_SESSION_STATE_INITIALIZING, ///< Session has been allocated but is still in the process of being initialized
	IPC_SESSION_STATE_LISTENING, ///< Session is waiting for incoming IPC messages
	IPC_SESSION_STATE_PROCESSING, ///< Session is waiting for \ref ipc_server_object_reply or \ref ipc_server_object_close to be called
	IPC_SESSION_STATE_ERRORED, ///< Session has encountered an error
} ipc_server_session_state_t;

typedef struct ipc_server_session_t {
	session_h handle; ///< Server-side handle
	session_h client_handle; ///< Client-side handle
	bool is_domain; ///< Whether this session represents a domain or a single object
	ipc_server_object_t hipc_manager_object; ///< The object for type-5 messages
	ipc_server_object_t *active_object; ///< The object that is being serviced
	ipc_server_object_t *object; ///< The object that this session owns, if it is not a domain
	ipc_server_domain_t domain; ///< The session's domain. Invalid unless \ref is_domain is true.
	ipc_server_session_state_t state; ///< Session's state
	struct ipc_server_t *owning_server; ///< Server that owns this session
	uint8_t message_buffer[0x100]; ///< IPC buffer
	wait_record_t *wait_record;
} ipc_server_session_t;

/*
  you are expected to initialize `userdata`, `dispatch`, and `close`.
  libtransistor will initialize all other fields.
 */
typedef result_t (*ipc_server_object_factory_t)(ipc_server_object_t **obj, void *userdata);

typedef struct ipc_server_port_t {
	port_h port;
	ipc_server_object_factory_t factory;
	void *userdata;
	wait_record_t *wait_record;
	struct ipc_server_t *server;
} ipc_server_port_t;

typedef struct ipc_server_t {
	ipc_server_port_t ports[MAX_SERVICE_PORTS];
	uint32_t num_ports;
	
	ipc_server_session_t sessions[MAX_SERVICE_SESSIONS];

	waiter_t *waiter;
} ipc_server_t;

result_t ipc_server_create(ipc_server_t *srv, waiter_t *waiter);
result_t ipc_server_add_port(ipc_server_t *srv, port_h port, ipc_server_object_factory_t object_factory, void *userdata);
result_t ipc_server_create_session(ipc_server_t *srv, session_h server_side, session_h client_side, ipc_server_object_t *object);
result_t ipc_server_accept_session(ipc_server_t *srv, ipc_server_port_t *port);
result_t ipc_server_destroy(ipc_server_t *srv);

result_t ipc_server_object_register(ipc_server_object_t *owner, ipc_server_object_t *new_object);
result_t ipc_server_object_reply(ipc_server_object_t *obj, ipc_response_t *rs);
result_t ipc_server_object_close(ipc_server_object_t *obj);

result_t ipc_server_domain_add_object(ipc_server_domain_t *domain, ipc_server_object_t *object);
result_t ipc_server_domain_get_object(ipc_server_domain_t *domain, uint32_t object_id, ipc_server_object_t **object);
result_t ipc_server_domain_destroy(ipc_server_domain_t *domain);

result_t ipc_server_session_receive(ipc_server_session_t *sess);
result_t ipc_server_session_close(ipc_server_session_t *sess);

#ifdef __cplusplus
}
#endif
