/**
 * @file libtransistor/ipc.h
 * @brief Interprocess Communication data structures and functions
 */

#pragma once

#include<libtransistor/types.h>

/**
* @struct ipc_domain_t
* @brief Represents an IPC object domain
*/
typedef struct {
	session_h session;
} ipc_domain_t;

/**
* @struct ipc_object_t
* @brief Represents either an object within an IPC domain or a standalone object
*/
typedef struct {
	int32_t object_id; ///< -1 if this represents a session, >= 0 if this represents a domain object
	union {
		session_h session; ///< object_id = -1
		ipc_domain_t *domain; ///< object_id >= 0
	};
} ipc_object_t;

/**
* @struct ipc_buffer_t
* @brief Buffer for transfer over IPC
*/
typedef struct {
	void *addr;
	uint64_t size; ///< Size in bytes.
	uint32_t type;
} ipc_buffer_t;

/**
* @struct ipc_request_t
* @brief Represents an unmarshalled IPC request
*
* see http://switchbrew.org/index.php?title=IPC_Marshalling#IPC_Command_Structure
*/
typedef struct {
	uint32_t type;
	uint32_t num_buffers;
	ipc_buffer_t **buffers; ///< This should point to an array of \ref num_buffers buffers
	uint32_t request_id;
	uint32_t *raw_data;
	size_t raw_data_size; ///< Size in bytes of \ref raw_data
	bool send_pid;
	uint8_t num_copy_handles;
	uint8_t num_move_handles;
	uint8_t num_objects;
	handle_t *copy_handles; ///< Array of \ref num_copy_handles handles to be copied
	handle_t *move_handles; ///< Array of \ref num_move_handles handles to be moved
	ipc_object_t *objects; ///< Array of \ref num_objects objects to be referenced
	bool close_object; ///< Whether or not to close the domain object. You should use \ref ipc_close instead of this.
} ipc_request_t;

/**
* @struct ipc_response_fmt_t
* @brief Fill this struct with what you expect the response format to be before passing it to ipc_unmarshal()
*
* Represents the expectations for an IPC response and contains pointers to buffers for
* response data to be written to.
*/
typedef struct {
	uint32_t num_copy_handles;
	uint32_t num_move_handles;
	uint32_t num_objects;
	handle_t *copy_handles;
	handle_t *move_handles;
	ipc_object_t *objects;
  
	size_t raw_data_size; ///< size in bytes of \ref raw_data
	uint32_t *raw_data;

	bool has_pid;
	uint32_t *pid;
} ipc_response_fmt_t;

/**
* @brief An IPC request with default values set
*
* @param type Default: 4
* @param num_buffers Default: 0
* @param buffers Default: NULL
* @param request_id Default: 0
* @param raw_data Default: 0
* @param raw_data_size Default: 0
* @param send_pid Default: 0
* @param num_copy_handles Default: 0
* @param num_move_handles Default: 0
* @param num_objects Default: 0
* @param copy_handles Default: NULL
* @param move_handles Default: NULL
* @param objects Default: NULL
* @param close_object Default: false
*/
extern ipc_request_t      ipc_default_request;

/**
* @brief An IPC response format with default values set
*
* @param num_copy_handles Default: 0
* @param num_move_handles Default: 0
* @param num_objects Default: 0
* @param copy_handles Default: NULL
* @param move_handles Default: NULL
* @param objects Default: NULL
* @param raw_data_size Default: 0
* @param raw_data Default: 0
* @param has_pid Default: false
* @param pid Default: 0
*/
extern ipc_response_fmt_t ipc_default_response_fmt;

/**
* @brief An IPC object with default NULL values set
*
* @param session Default: 0
* @param object_id Default: 1
*/
extern ipc_object_t       ipc_null_object;

/// Default: 0
extern int ipc_debug_flag;

/**
* @brief Packs the IPC message described by `rq` and `object` into `buffer`.
*
* @param buffer Target for marshalled IPC message
* @param rq Request to pack
* @param object Object to send the request to
*/
result_t ipc_marshal(uint32_t *buffer, ipc_request_t *rq, ipc_object_t object);

/**
* @brief Unpacks the IPC message described by `rs` from `buffer`. `object` should
* be the object the request was sent to.
*
* @param buffer Marshalled IPC message
* @param rs Response format expectations
* @param object Object that the response was received from
*/
result_t ipc_unmarshal(uint32_t *buffer, ipc_response_fmt_t *rs, ipc_object_t object);

/**
* @brief Send a request described by `rq` to `object` and then unpack the response
*
* @param object Object to send request to
* @param rq Request to send
* @param rs Response expectations
*/
result_t ipc_send(ipc_object_t object, ipc_request_t *rq, ipc_response_fmt_t *rs);

/**
* @brief Converts `session` to a domain object and initializes `domain`.
*  Guarenteed to initialize `domain`, making it valid to call `ipc_close_domain`
*  on the newly initialized domain if this returns != RESULT_OK
*
* @param session Object to convert to a domain object
* @param domain Domain to initialize
*/
result_t ipc_convert_to_domain(ipc_object_t *session, ipc_domain_t *domain);

/**
* @brief Closes the `object`
*
* @param object Object to close
*/
result_t ipc_close(ipc_object_t object);

/**
* @brief Closes the whole `domain`
*
* @param domain Domain to close
*/
result_t ipc_close_domain(ipc_domain_t domain);
