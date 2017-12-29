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

result_t svcSetHeapSize(void **outAddr, uint32_t size);
result_t svcSetMemoryPermission(void *addr, uint64_t size, uint32_t permission);
result_t svcSetMemoryAttribute(void *addr, uint64_t size, uint32_t state0, uint32_t state1);
result_t svcMapMemory(void *dest, void *src, uint64_t size);
result_t svcUnmapMemory(void *dest, void *src, uint64_t size);
result_t svcQueryMemory(memory_info_t *memory_info, uint32_t *page_info, void *addr);
void svcExitProcess();
result_t svcCreateThread(thread_h *out, thread_entry entry, uint64_t arg, void *stacktop, int32_t priority, int32_t processor_id);
result_t svcStartThread(thread_h thread);
void svcExitThread();
result_t svcSleepThread(uint64_t nanos);
result_t svcGetThreadPriority(uint32_t *priority, thread_h thread);
result_t svcSetThreadCoreMask(thread_h thread, uint32_t in, uint64_t in2);
uint32_t svcGetCurrentProcessorNumber();
result_t svcSignalEvent(wevent_h event);
result_t svcClearEvent(event_h event);
result_t svcMapSharedMemory(shared_memory_h block, void *addr, uint64_t size, uint32_t permission);
result_t svcUnmapSharedMemory(shared_memory_h block, void *addr, uint64_t size);
result_t svcCreateTransferMemory(transfer_memory_h *out, void *addr, uint64_t size, uint32_t permission);
result_t svcCloseHandle(handle_t handle);
result_t svcResetSignal(handle_t signal); // revent or process
result_t svcWaitSynchronization(uint32_t *handle_index, handle_t *handles, uint32_t num_handles, uint64_t timeout);
result_t svcCancelSynchronization(handle_t handle);
void svcArbitrateLock(thread_h current_thread, void *lock, thread_h requesting_thread);
void svcArbitrateUnlock(void *lock);
result_t svcWaitProcessWideKeyAtomic(void *ptr0, void *ptr1, thread_h thread, uint64_t timeout);
result_t svcSignalProcessWideKey(void *ptr, uint32_t value);
uint64_t svcGetSystemTick();
result_t svcConnectToNamedPort(session_h *out, char name[8]);
// sendSyncRequestLight
result_t svcSendSyncRequest(session_h session);
result_t svcSendSyncRequestWithUserBuffer(void *buffer, uint64_t size, session_h session);
// sendAsyncRequestWithUserBuffer
// getProcessId
result_t svcGetThreadId(thread_h *handle_out, thread_h handle_in);
// break
void svcOutputDebugString(char *str, uint64_t size);
void svcReturnFromException(uint64_t result);
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
result_t svcAcceptSession(session_h *out, port_h port);
// replyAndReceiveLight
result_t svcReplyAndReceive(uint32_t *handle_idx, session_h *handles, uint32_t num_handles, session_h reply_session, uint64_t timeout);
result_t svcReplyAndReceiveWithUserBuffer(uint32_t *handle_idx, void *buffer, uint64_t size, session_h *handles, uint32_t num_handles, session_h reply_session, uint64_t timeout);
// createEvent
// 0x46-0x4E?
// sleepSystem
result_t svcReadWriteRegister(uint32_t *out_value, uint64_t addr, uint32_t rw_mask, uint32_t in_value);
// setProcessActivity
result_t svcCreateSharedMemory(shared_memory_h *out, uint64_t size, uint32_t self_permissions, uint32_t foreign_permissions);
result_t svcMapTransferMemory(transfer_memory_h handle, void *addr, uint64_t size, uint32_t perm);
result_t svcUnmapTransferMemory(transfer_memory_h handle, void *addr, uint64_t size);
// createInterruptEvent
// queryPhysicalAddress
result_t svcQueryIoMapping(void *virt_addr, uint64_t phys_addr, uint64_t size);
// createDeviceAddressSpace
result_t svcAttachDeviceAddressSpace(uint32_t device, dev_addr_space_h space);
result_t svcDetachDeviceAddressSpace(uint32_t device, dev_addr_space_h space);
result_t svcMapDeviceAddressSpaceByForce(dev_addr_space_h space, process_h process, uint64_t dev_addr, uint64_t dev_size, uint64_t map_addr, uint32_t perm);
result_t svcMapDeviceAddressSpaceAligned(dev_addr_space_h space, process_h process, uint64_t dev_addr, uint64_t dev_size, uint64_t map_addr, uint32_t perm);
// mapDeviceAddressSpace
result_t svcUnmapDeviceAddressSpace(dev_addr_space_h space, process_h process, uint64_t map_addr, uint64_t map_size, uint32_t perm);
// invalidateProcessDataCache
// storeProcessDataCache
// flushProcessDataCache
result_t svcDebugActiveprocess(debug_h *out, uint64_t process_id);
// breakDebugProcess
// terminateDebugProcess
// getDebugEvent
// continueDebugEvent
// getProcessList
// getThreadList
// getDebugThreadContext
// setDebugThreadContext
result_t svcQueryDebugProcessMemory(memory_info_t *memory_info, uint32_t *page_info, debug_h debug, uint64_t addr);
result_t svcReadDebugProcessMemory(void *buffer, debug_h debug, uint64_t addr, uint64_t size);
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
