/**
 * @file libtransistor/svc.h
 * @brief Service functions
 */

#pragma once

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
 * @param outAddr Description
 * @param size Description
 */
result_t svcSetHeapSize(void **outAddr, uint32_t size);

/**
 * @brief Sets memory permissions
 *
 * @param addr Description
 * @param size Description
 * @param permission Description
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
void svcExitProcess();

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
void svcExitThread();

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
// setProcessMemoryPermission
// mapProcessMemory
// unmapProcessMemory
// queryProcessmemory
// mapProcessCodeMemory
// unmapProcessCodeMemory
// createProcess
// startProcess
// terminateProcess
// getProcessInfo
// createResourceLimit
// setResourceLimitLimitValue
// callSecureMonitor
