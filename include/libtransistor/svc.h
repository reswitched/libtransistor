/**
 * @file libtransistor/svc.h
 * @brief Supervisor Calls
 */

#pragma once

#ifdef __cplusplus
extern "C" {
#endif

#define CURRENT_PROCESS 0xffff8001
#define CURRENT_THREAD 0xffff8000

typedef struct PACKED {
	void *base_addr;
	uint64_t size;
	uint32_t memory_type;
	uint32_t memory_attribute;
	uint32_t permission;
	uint32_t device_ref_count;
	uint32_t ipc_ref_count;
	uint32_t padding;
} memory_info_t;

/**
 * @brief Sets the size of the heap
 *
 * @param outAddr Output for address of the heap
 * @param size Size of the heap
 */
result_t svcSetHeapSize(void **outAddr, uint32_t size);

/**
 * @brief Sets memory permissions
 *
 * @param addr Adress of region to reprotect
 * @param size Size of region to reprotect
 * @param permission Permissions
 *
 * addr and size must be page-aligned, and execute bit is not allowed.
 */
result_t svcSetMemoryPermission(void *addr, uint64_t size, uint32_t permission);

/**
 * @brief Sets memory attributes
 *
 * @param addr Description
 * @param size Description
 * @param state0 Description
 * @param state1 Description
 */
result_t svcSetMemoryAttribute(void *addr, uint64_t size, uint32_t state0, uint32_t state1);

/**
 * @brief Map memory
 *
 * @param dest Description
 * @param src Description
 * @param size Description
 */
result_t svcMapMemory(void *dest, void *src, uint64_t size);

/**
 * @brief Unmap memory
 *
 * @param dest Description
 * @param src Description
 * @param size Description
 */
result_t svcUnmapMemory(void *dest, void *src, uint64_t size);

/**
 * @brief Query memory
 *
 * @param memory_info Description
 * @param page_info Description
 * @param addr Description
 */
result_t svcQueryMemory(memory_info_t *memory_info, uint32_t *page_info, void *addr);

/**
 * @brief Exit the process
 */
void __attribute__((__noreturn__)) svcExitProcess();

/**
 * @brief Create a new thread
 *
 * @param out Description
 * @param entry Description
 * @param arg Description
 * @param stacktop Description
 * @param priority Description
 * @param processor_id Description
 */
result_t svcCreateThread(thread_h *out, thread_entry entry, uint64_t arg, void *stacktop, int32_t priority, int32_t processor_id);

/**
 * @brief Start a thread
 *
 * @param thread The handle to the thread to be started
 */
result_t svcStartThread(thread_h thread);

/**
 * @brief Exit thread
 */
void __attribute__((__noreturn__)) svcExitThread();

/**
 * @brief Sleep thread for specified time
 *
 * @param nanos Amount of time in nanoseconds
 */
result_t svcSleepThread(uint64_t nanos);

/**
 * @brief Get the thread priority
 *
 * @param priority Description
 * @param thread Description
 */
result_t svcGetThreadPriority(uint32_t *priority, thread_h thread);

/**
 * @brief Set thread core mask
 *
 * @param thread Description
 * @param in Description
 * @param in2 Description
 */
result_t svcSetThreadCoreMask(thread_h thread, uint32_t in, uint64_t in2);

/**
 * @brief Get the current processor number
 */
uint32_t svcGetCurrentProcessorNumber();

/**
 * @brief Signal an event
 *
 * @param event Description
 */
result_t svcSignalEvent(wevent_h event);

/**
 * @brief Clear an event
 *
 * @param event Description
 */
result_t svcClearEvent(event_h event);

/**
 * @brief Map shared memory
 *
 * @param block Description
 * @param addr Description
 * @param size Description
 * @param permission Description
 */
result_t svcMapSharedMemory(shared_memory_h block, void *addr, uint64_t size, uint32_t permission);

/**
 * @brief Unmap shared memory
 *
 * @param block Description
 * @param addr Description
 * @param size Description
 */
result_t svcUnmapSharedMemory(shared_memory_h block, void *addr, uint64_t size);

/**
 * @brief Create transfer memory
 *
 * @param out Description
 * @param addr Description
 * @param size Description
 * @param permission Description
 */
result_t svcCreateTransferMemory(transfer_memory_h *out, void *addr, uint64_t size, uint32_t permission);

/**
 * @brief Closes the specified handle
 *
 * @param handle Description
 */
result_t svcCloseHandle(handle_t handle);

/**
 * @brief Resets a signal
 *
 *        revent or process
 *
 * @param signal Description
 */
result_t svcResetSignal(handle_t signal);

/**
 * @brief Wait synchronization
 *
 * @param handle_index Description
 * @param handles Description
 * @param num_handles Description
 * @param timeout Description
 */
result_t svcWaitSynchronization(uint32_t *handle_index, handle_t *handles, uint32_t num_handles, uint64_t timeout);

/**
 * @brief Cancel synchronization
 *
 * @param handle Description
 */
result_t svcCancelSynchronization(handle_t handle);

/**
 * @brief Arbitrate lock
 *
 * @param current_thread Description
 * @param lock Description
 * @param requesting_thread Description
 */
void svcArbitrateLock(thread_h current_thread, void *lock, thread_h requesting_thread);

/**
 * @brief Arbitrate unlock
 *
 * @param lock Description
 */
void svcArbitrateUnlock(void *lock);

/**
 * @brief Wait process wide key atomic
 *
 * @param ptr0 Description
 * @param ptr1 Description
 * @param thread Description
 * @param timeout Description
 */
result_t svcWaitProcessWideKeyAtomic(void *ptr0, void *ptr1, thread_h thread, uint64_t timeout);

/**
 * @brief Wait process wide key atomic
 *
 * @param ptr Description
 * @param value Description
 */
result_t svcSignalProcessWideKey(void *ptr, uint32_t value);

/**
 * @brief Get the system time tick
 */
uint64_t svcGetSystemTick();

/**
 * @brief Connect to a named port
 *
 * @param out Description
 * @param name Description
 */
result_t svcConnectToNamedPort(session_h *out, char name[8]);
// sendSyncRequestLight

/**
 * @brief Send sync request
 *
 * @param session Description
 */
result_t svcSendSyncRequest(session_h session);

/**
 * @brief Send sync request with user buffer
 *
 * @param buffer Description
 * @param size Description
 * @param session Description
 */
result_t svcSendSyncRequestWithUserBuffer(void *buffer, uint64_t size, session_h session);
// sendAsyncRequestWithUserBuffer

/**
 * @brief Get a process's ID
 *
 * @param pid Output PID
 * @param thread_or_process_handle Thread or process to query PID of
 */
result_t svcGetProcessId(uint32_t *pid, handle_t thread_or_process_handle);
// getProcessId

/**
 * @brief Get a thread ID
 *
 * @param handle_out Description
 * @param handle_in Description
 */
result_t svcGetThreadId(thread_h *handle_out, thread_h handle_in);
// break

/**
 * @brief Output a debug string
 *
 * @param str Description
 * @param size Description
 */
void svcOutputDebugString(char *str, uint64_t size);

/**
 * @brief Return from exception
 *
 * @param result Description
 */
void svcReturnFromException(uint64_t result);

/**
 * @brief Get info
 *
 * @param info Description
 * @param info_id Description
 * @param handle Description
 * @param info_sub_id Description
 */
result_t svcGetInfo(uint64_t *info, uint64_t info_id, handle_t handle, uint64_t info_sub_id);
// flushEntireDataCache
// flushDataCache
// mapPhysicalMemory
// unmapPhysicalMemory
// 0x2E?
// getLastThreadInfo
// getResourceLimitLimitValue
// getResourceLimitCurrentValue
// setThreadActivity
// getThreadContext3
// 0x34-0x3B?
// dumpInfo
// 0x3D-0x3F?
result_t svcCreateSession(session_h *server, session_h *client, bool is_light, uint32_t unknown);
// createSession

/**
 * @brief Accept session
 *
 * @param out Description
 * @param port Description
 */
result_t svcAcceptSession(session_h *out, port_h port);
// replyAndReceiveLight

/**
 * @brief Reply and recieve
 *
 * @param handle_idx Description
 * @param handles Description
 * @param num_handles Description
 * @param reply_session Description
 * @param timeout Description
 */
result_t svcReplyAndReceive(uint32_t *handle_idx, session_h *handles, uint32_t num_handles, session_h reply_session, uint64_t timeout);

/**
 * @brief Reply and recieve with user buffer
 *
 * @param handle_idx Description
 * @param buffer Description
 * @param size Description
 * @param handles Description
 * @param num_handles Description
 * @param reply_session Description
 * @param timeout Description
 */
result_t svcReplyAndReceiveWithUserBuffer(uint32_t *handle_idx, void *buffer, uint64_t size, session_h *handles, uint32_t num_handles, session_h reply_session, uint64_t timeout);
// createEvent
// 0x46-0x4E?
// sleepSystem

/**
 * @brief Read/Write register
 *
 * @param out_value Description
 * @param addr Description
 * @param rw_mask Description
 * @param in_value Description
 */
result_t svcReadWriteRegister(uint32_t *out_value, uint64_t addr, uint32_t rw_mask, uint32_t in_value);
// setProcessActivity

/**
 * @brief Create a block of shared memory
 *
 * @param out Description
 * @param size Description
 * @param self_permissions Description
 * @param foreign_permissions Description
 */
result_t svcCreateSharedMemory(shared_memory_h *out, uint64_t size, uint32_t self_permissions, uint32_t foreign_permissions);

/**
 * @brief Map transfer memory
 *
 * @param handle Description
 * @param addr Description
 * @param size Description
 * @param perm Description
 */
result_t svcMapTransferMemory(transfer_memory_h handle, void *addr, uint64_t size, uint32_t perm);

/**
 * @brief Unmap transfer memory
 *
 * @param handle Description
 * @param addr Description
 * @param size Description
 */
result_t svcUnmapTransferMemory(transfer_memory_h handle, void *addr, uint64_t size);
// createInterruptEvent
// queryPhysicalAddress

/**
 * @brief Query IO mapping
 *
 * @param virt_addr Description
 * @param phys_addr Description
 * @param size Description
 */
result_t svcQueryIoMapping(void *virt_addr, uint64_t phys_addr, uint64_t size);
// createDeviceAddressSpace

/**
 * @brief Attach device address space
 *
 * @param device Description
 * @param space Description
 */
result_t svcAttachDeviceAddressSpace(uint32_t device, dev_addr_space_h space);

/**
 * @brief Detach device address space
 *
 * @param device Description
 * @param space Description
 */
result_t svcDetachDeviceAddressSpace(uint32_t device, dev_addr_space_h space);

/**
 * @brief Map device address space by force
 *
 * @param space Description
 * @param process Description
 * @param dev_addr Description
 * @param dev_size Description
 * @param map_addr Description
 * @param perm Description
 */
result_t svcMapDeviceAddressSpaceByForce(dev_addr_space_h space, process_h process, uint64_t dev_addr, uint64_t dev_size, uint64_t map_addr, uint32_t perm);

/**
 * @brief Map device address space aligned
 *
 * @param space Description
 * @param process Description
 * @param dev_addr Description
 * @param dev_size Description
 * @param map_addr Description
 * @param perm Description
 */
result_t svcMapDeviceAddressSpaceAligned(dev_addr_space_h space, process_h process, uint64_t dev_addr, uint64_t dev_size, uint64_t map_addr, uint32_t perm);
// mapDeviceAddressSpace

/**
 * @brief Unmap device address space
 *
 * @param space Description
 * @param process Description
 * @param map_addr Description
 * @param map_size Description
 * @param perm Description
 */
result_t svcUnmapDeviceAddressSpace(dev_addr_space_h space, process_h process, uint64_t map_addr, uint64_t map_size, uint32_t perm);
// invalidateProcessDataCache
// storeProcessDataCache
// flushProcessDataCache

/**
 * @brief Debug active process
 *
 * @param out Description
 * @param process_id Description
 */
result_t svcDebugActiveprocess(debug_h *out, uint64_t process_id);
// breakDebugProcess
// terminateDebugProcess
// getDebugEvent
// continueDebugEvent
// getProcessList
// getThreadList
// getDebugThreadContext
// setDebugThreadContext

/**
 * @brief Query debug process memory
 *
 * @param memory_info Description
 * @param page_info Description
 * @param debug Description
 * @param addr Description
 */
result_t svcQueryDebugProcessMemory(memory_info_t *memory_info, uint32_t *page_info, debug_h debug, uint64_t addr);

/**
 * @brief Read debug process memory
 *
 * @param buffer Description
 * @param debug Description
 * @param addr Description
 * @param size Description
 */
result_t svcReadDebugProcessMemory(void *buffer, debug_h debug, uint64_t addr, uint64_t size);

/**
 * @brief Write debug process memory
 *
 * @param buffer Description
 * @param debug Description
 * @param addr Description
 * @param size Description
 */
result_t svcWriteDebugProcessMemory(debug_h debug, void *buffer, uint64_t addr, uint64_t size);
// setHardwareBreakPoint
// getDebugThreadParam
// 0x6D-0x6F?
// createPort
// manageNamedPort
// connectToPort

/**
 * @brief Reprotect memory in the given process
 *
 * @param process Process to reprotect memory in
 * @param addr Address in given process
 * @param size Size of region to reprotect
 * @param prot Protections
 */
result_t svcSetProcessMemoryPermission(process_h process, void *addr, uint64_t size, uint32_t prot);

// mapProcessMemory
// unmapProcessMemory
// queryProcessmemory

/**
 * @brief Map process code memory
 */
result_t svcMapProcessCodeMemory(process_h process, void *dst, void *src, uint64_t size);

/**
 * @brief Unmap process code memory
 */
result_t svcUnmapProcessCodeMemory(process_h process, void *dst, void *src, uint64_t size);

// createProcess
// startProcess
// terminateProcess
// getProcessInfo
// createResourceLimit
// setResourceLimitLimitValue
// callSecureMonitor

enum {
	SVC_ID_SET_HEAP_SIZE = 0x01,
	SVC_ID_SET_MEMORY_PERMISSION = 0x02,
	SVC_ID_SET_MEMORY_ATTRIBUTE = 0x03,
	SVC_ID_MAP_MEMORY = 0x04,
	SVC_ID_UNMAP_MEMORY = 0x05,
	SVC_ID_QUERY_MEMORY = 0x06,

	SVC_ID_EXIT_PROCESS = 0x07,

	SVC_ID_CREATE_THREAD = 0x08,
	SVC_ID_START_THREAD = 0x09,
	SVC_ID_EXIT_THREAD = 0x0A,
	SVC_ID_SLEEP_THREAD = 0x0B,
	SVC_ID_GET_THREAD_PRIORITY = 0x0C,
	SVC_ID_SET_THREAD_PRIORITY = 0x0D,
	SVC_ID_GET_THREAD_CORE_MASK = 0x0E,
	SVC_ID_SET_THREAD_CORE_MASK = 0x0F,
	SVC_ID_GET_CURRENT_PROCESSOR_NUMBER = 0x10,

	SVC_ID_SIGNAL_EVENT = 0x11,
	SVC_ID_CLEAR_EVENT = 0x12,

	SVC_ID_MAP_SHARED_MEMORY = 0x13,
	SVC_ID_UNMAP_SHARED_MEMORY = 0x14,
	SVC_ID_CREATE_TRANSFER_MEMORY = 0x15,

	SVC_ID_CLOSE_HANDLE = 0x16,

	SVC_ID_RESET_SIGNAL = 0x17,
	SVC_ID_WAIT_SYNCHRONIZATION = 0x18,
	SVC_ID_CANCEL_SYNCHRONIZATION = 0x19,
	SVC_ID_ARBITRATE_LOCK = 0x1A,
	SVC_ID_ARBITRATE_UNLOCK = 0x1B,
	SVC_ID_WAIT_PROCESS_WIDE_KEY_ATOMIC = 0x1C,
	SVC_ID_SIGNAL_PROCESS_WIDE_KEY = 0x1D,
	SVC_ID_GET_SYSTEM_TICK = 0x1E,

	SVC_ID_CONNECT_TO_NAMED_PORT = 0x1F,
	SVC_ID_SEND_SYNC_REQUEST_LIGHT = 0x20,
	SVC_ID_SEND_SYNC_REQUEST = 0x21,
	SVC_ID_SEND_SYNC_REQUEST_WITH_USER_BUFFER = 0x22,
	SVC_ID_SEND_ASYNC_REQUEST_WITH_USER_BUFFER = 0x23,

	SVC_ID_GET_PROCESS_ID = 0x24,
	SVC_ID_GET_THREAD_ID = 0x25,

	SVC_ID_BREAK = 0x26,
	SVC_ID_OUTPUT_DEBUG_STRING = 0x27,
	SVC_ID_RETURN_FROM_EXCEPTION = 0x28,

	SVC_ID_GET_INFO = 0x29,
	SVC_ID_FLUSH_ENTIRE_DATA_CACHE = 0x2A,
	SVC_ID_FLUSH_DATA_CACHE = 0x2B,
	SVC_ID_GET_LAST_THREAD_INFO = 0x2C,

	SVC_ID_GET_RESOURCE_LIMIT_LIMIT_VALUE = 0x30,
	SVC_ID_GET_RESOURCE_LIMIT_CURRENT_VALUE = 0x31,

	SVC_ID_SET_THREAD_ACTIVITY = 0x32,
	SVC_ID_GET_THREAD_CONTEXT3 = 0x33,

	SVC_ID_DUMP_INFO = 0x3C,

	SVC_ID_CREATE_SESSION = 0x40,
	SVC_ID_ACCEPT_SESSION = 0x41,
	SVC_ID_REPLY_AND_RECEIVE_LIGHT = 0x42,
	SVC_ID_REPLY_AND_RECEIVE = 0x43,
	SVC_ID_REPLY_AND_RECEIVE_WITH_USER_BUFFER = 0x44,
	SVC_ID_CREATE_EVENT = 0x4E,
	SVC_ID_SLEEP_SYSTEM = 0x4D,

	SVC_ID_READ_WRITE_REGISTER = 0x4E,
	SVC_ID_SET_PROCESS_ACTIVITY = 0x4F,

	SVC_ID_CREATE_SHARED_MEMORY = 0x50,
	SVC_ID_MAP_TRANSFER_MEMORY = 0x51,
	SVC_ID_UNMAP_TRANSFER_MEMORY = 0x52,
	SVC_ID_CREATE_INTERRUPT_EVENT = 0x53,
	SVC_ID_QUERY_PHYSICAL_ADDRESS = 0x54,

	SVC_ID_QUERY_IO_MAPPING = 0x55,
	SVC_ID_CREATE_DEVICE_ADDRESS_SPACE = 0x56,
	SVC_ID_ATTACH_DEVICE_ADDRESS_SPACE = 0x57,
	SVC_ID_DETACH_DEVICE_ADDRESS_SPACE = 0x58,
	SVC_ID_MAP_DEVICE_ADDRESS_SPACE_BY_FORCE = 0x59,
	SVC_ID_MAP_DEVICE_ADDRESS_SPACE_ALIGNED = 0x5A,
	SVC_ID_MAP_DEVICE_ADDRESS_SPACE = 0x5B,
	SVC_ID_UNMAP_DEVICE_ADDRESS_SPACE = 0x5C,
	SVC_ID_INVALIDATE_PROCESS_DATA_CACHE = 0x5D,
	SVC_ID_STORE_PROCESS_DATA_CACHE = 0x5E,
	SVC_ID_FLUSH_PROCESS_DATA_CACHE = 0x5F,

	SVC_ID_DEBUG_ACTIVE_PROCESS = 0x60,
	SVC_ID_BREAK_DEBUG_PROCESS = 0x61,
	SVC_ID_TERMINATE_DEBUG_PROCESS = 0x62,
	SVC_ID_GET_DEBUG_EVENT = 0x63,
	SVC_ID_CONTINUE_DEBUG_EVENT = 0x64,
	SVC_ID_GET_PROCESS_LIST = 0x65,
	SVC_ID_GET_THREAD_LIST = 0x66,
	SVC_ID_GET_DEBUG_THREAD_CONTEXT = 0x67,
	SVC_ID_SET_DEBUG_THREAD_CONTEXT = 0x68,

	SVC_ID_QUERY_DEBUG_PROCESS_MEMORY = 0x69,
	SVC_ID_READ_DEBUG_PROCESS_MEMORY = 0x6A,
	SVC_ID_WRITE_DEBUG_PROCESS_MEMORY = 0x6B,
	SVC_ID_SET_HARDWARE_BREAK_POINT = 0x6C,
	SVC_ID_GET_DEBUG_THREAD_PARAM = 0x6D,

	SVC_ID_CREATE_PORT = 0x70,
	SVC_ID_MANAGE_NAMED_PORT = 0x71,
	SVC_ID_CONNECT_TO_PORT = 0x72,

	SVC_ID_SET_PROCESS_MEMORY_PERMISSION = 0x73,
	SVC_ID_MAP_PROCESS_MEMORY = 0x74,
	SVC_ID_UNMAP_PROCESS_MEMORY = 0x75,
	SVC_ID_QUERY_PROCESS_MEMORY = 0x76,
	SVC_ID_MAP_PROCESS_CODE_MEMORY = 0x77,
	SVC_ID_UNMAP_PROCESS_CODE_MEMORY = 0x78,

	SVC_ID_CREATE_PROCESS = 0x79,
	SVC_ID_START_PROCESS = 0x7A,
	SVC_ID_TERMINATE_PROCESS = 0x7B,
	SVC_ID_GET_PROCESS_INFO = 0x7C,

	SVC_ID_CREATE_RESOURCE_LIMIT = 0x7D,
	SVC_ID_SET_RESOURCE_LIMIT_LIMIT_VALUE = 0x7E,

	SVC_ID_CALL_SECURE_MONITOR = 0x7F,
};

#ifdef __cplusplus
}
#endif
