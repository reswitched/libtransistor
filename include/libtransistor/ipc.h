/**
 * @file libtransistor/ipc.h
 * @brief Interprocess Communication data structures and functions
 *
 * This file contains some of the types and functions required for IPC server
 * functionality. The remaining functionality is found in ipcserver.h
 *
 */

#pragma once

#ifdef __cplusplus
extern "C" {
#endif

#include<libtransistor/types.h>

struct ipc_server_object_t;

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
	bool is_borrowed; ///< whether or not this object is being borrowed from a loader or not
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
* @brief Represents an unmarshalled outgoing IPC request
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
* @struct ipc_request_fmt_t
* @brief Describes format expectations for an incoming IPC request
*
* Represents the expectations for an IPC request and contains pointers to buffers for
* request data to be written to.
*
* Used for IPC server.
*/
typedef struct {
	uint32_t num_buffers; ///< Number of buffers to expect
	ipc_buffer_t **buffers; ///< This should point to an array of \ref num_buffers buffers, with the `type` fields filled out. The `addr` and `size` fields will be unpacked.
	uint32_t *raw_data; ///< Buffer to copy raw request data into
	size_t raw_data_size; ///< Size in bytes of \ref raw_data to expect
	bool send_pid; ///< Whether to expect an incoming PID
	uint64_t *pid; ///< Where to put an incoming PID, if one is expected and present
	uint8_t num_copy_handles; ///< How many handles to expect to be copied
	uint8_t num_move_handles; ///< How many handles to expect to be moved
	uint8_t num_objects; ///< How many objects to expect to be referenced
	handle_t *copy_handles; ///< Array to be populated with the expected amount of incoming copy handles
	handle_t *move_handles; ///< Array to be populated with the expected amount of incoming move handles
	struct ipc_server_object_t **objects; ///< Array to be populated with the expected amount of points to objects referenced by the request
} ipc_request_fmt_t;

/**
* @struct ipc_response_t
* @brief Represents an unmarshalled outgoing IPC response
*
* Used for IPC server.
*/
typedef struct {
	uint32_t type;
	uint32_t num_buffers;
	ipc_buffer_t **buffers;
	result_t result_code;
	uint32_t *raw_data;
	size_t raw_data_size; // in BYTES
	bool send_pid;
	uint8_t num_copy_handles;
	uint8_t num_move_handles;
	uint8_t num_objects;
	handle_t *copy_handles;
	handle_t *move_handles;
	struct ipc_server_object_t **objects;
} ipc_response_t;

/**
* @struct ipc_response_fmt_t
* @brief Describes format expectations for an incoming IPC response
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
 * @brief An IPC response with default values set
 *
 * Used for IPC server.
 */
extern ipc_response_t     ipc_default_response;

/**
 * @brief An IPC request format with default values set
 *
 * Used for IPC server.
 */
extern ipc_request_fmt_t  ipc_default_request_fmt;

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
 * @brief Describes an incoming IPC message. Used as an intermediate during unpacking.
 *
 * This struct is populated by ipc_unpack(), and contains pointers to the original IPC buffer.
 * As such, the original IPC buffer should not be modified until this struct will no longer
 * be referenced.
 */
typedef struct {
	uint16_t message_type;
	uint32_t raw_data_section_size; ///< in words
	uint32_t num_x_descriptors;
	uint32_t num_a_descriptors;
	uint32_t num_b_descriptors;
	uint32_t num_w_descriptors;
	uint32_t c_descriptor_flags;
	uint32_t *x_descriptors;
	uint32_t *a_descriptors;
	uint32_t *b_descriptors;
	uint32_t *w_descriptors;
	uint32_t *c_descriptors;
	uint32_t num_copy_handles;
	uint32_t num_move_handles;
	handle_t *copy_handles; ///< points to original ipc buffer
	handle_t *move_handles; ///< points to original ipc buffer
	bool has_pid;
	uint64_t pid;
	int pre_padding; ///< size of padding (in words) before aligned data section
	int post_padding; ///< size of padding (in words) after aligned data section
	uint32_t *data_section; ///< may point to domain header, may point to SFCI/SFCO
} ipc_message_t;

/**
 * @brief Packs the IPC request described by `rq` and `object` into `buffer`.
 *
 * @param buffer Target for marshalled IPC request
 * @param rq Request to pack
 * @param object Object to send the request to
 */
result_t ipc_pack_request(uint32_t *buffer, ipc_request_t *rq, ipc_object_t object);

/**
 * @brief Packs the IPC response described by `rs` and `object` into `buffer`.
 *
 * Used by IPC server.
 *
 * @param buffer Target for marshalled IPC response
 * @param rs Response to pack
 * @param object Object to send the response from
 */
result_t ipc_pack_response(uint32_t *buffer, ipc_response_t *rs, struct ipc_server_object_t *object);

/**
 * @brief Unpacks the IPC message from `buffer`, filling out `msg`.
 *
 * @param buffer Packed IPC message
 * @param msg Partially unpacked IPC message
 */
result_t ipc_unpack(uint32_t *buffer, ipc_message_t *msg);

/**
 * @brief Unflattens the IPC request described by `rq` from `msg`
 *
 * It is expected that the decision for which object to dispatch to can be
 * made based off of the fields in \ref ipc_message_t alone, without having
 * to unflatten it fully.
 *
 * Used by IPC server.
 *
 * @param msg IPC message to unflatten
 * @param rs Format expectations for incoming request
 * @param object Object that the request is destined for.
 */
result_t ipc_unflatten_request(ipc_message_t *msg, ipc_request_fmt_t *rs, struct ipc_server_object_t *object);

/**
 * @brief Unflattens the IPC response described by `rs` from `msg`.
 *
 * @param buffer Marshalled IPC message
 * @param rs Response format expectations
 * @param object Object that the response was received from
*/
result_t ipc_unflatten_response(ipc_message_t *msg, ipc_response_fmt_t *rs, ipc_object_t object);

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
*  `domain` is only initialized if RESULT_OK is returned.
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

#ifdef __cplusplus
}
#endif
