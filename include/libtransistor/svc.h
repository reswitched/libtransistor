#pragma once

typedef struct PACKED {
  void *base_addr;
  u64 size;
  u32 memory_type;
  u32 memory_attribute;
  u32 permission;
  u32 device_ref_count;
  u32 ipc_ref_count;
  u32 padding;
} memory_info_t;

result_t svcSetHeapSize(void **outAddr, u32 size);
result_t svcSetMemoryPermission(void *addr, u64 size, u32 permission);
result_t svcSetMemoryAttribute(void *addr, u64 size, u32 state0, u32 state1);
result_t svcMapMemory(void *dest, void *src, u64 size);
result_t svcUnmapMemory(void *dest, void *src, u64 size);
result_t svcQueryMemory(memory_info_t *memory_info, u32 *page_info, void *addr);
void svcExitProcess();
result_t svcCreateThread(thread_h *out, thread_entry entry, u64 arg, void *stacktop, s32 priority, s32 processor_id);
result_t svcStartThread(thread_h thread);
void svcExitThread();
result_t svcSleepThread(u64 nanos);
result_t svcGetThreadPriority(u32 *priority, thread_h thread);
result_t svcSetThreadCoreMask(thread_h thread, u32 in, u64 in2);
u32 svcGetCurrentProcessorNumber();
result_t svcSignalEvent(handle_t event);
result_t svcClearEvent(handle_t event);
result_t svcMapSharedMemory(shared_memory_h block, void *addr, u64 size, u32 permission);
result_t svcUnmapSharedMemory(shared_memory_h block, void *addr, u64 size);
result_t svcCreateTransferMemory(transfer_memory_h *out, void *addr, u64 size, u32 permission);
result_t svcCloseHandle(handle_t handle);
result_t svcResetSignal(handle_t signal);
result_t svcWaitSynchronization(u32 *handle_index, handle_t *handles, u32 num_handles, u64 timeout);
result_t svcCancelSynchronization(handle_t handle);
void svcArbitrateLock(thread_h current_thread, void *lock, thread_h requesting_thread);
void svcArbitrateUnlock(void *lock);
result_t svcWaitProcessWideKeyAtomic(void *ptr0, void *ptr1, thread_h thread, u64 timeout);
result_t svcSignalProcessWideKey(void *ptr, u32 value);
u64 svcGetSystemTick();
result_t svcConnectToNamedPort(session_h *out, char name[8]);
// sendSyncRequestLight
result_t svcSendSyncRequest(session_h session);
result_t svcSendSyncRequestWithUserBuffer(void *buffer, u64 size, session_h session);
// sendAsyncRequestWithUserBuffer
// getProcessId
// getThreadId
// break
void svcOutputDebugString(char *str, u64 size);
void svcReturnFromException(u64 result);
result_t svcGetInfo(u64 *info, u64 info_id, handle_t handle, u64 info_sub_id);
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
result_t svcReplyAndReceive(u32 *handle_idx, session_h *handles, u32 num_handles, session_h reply_session, u64 timeout);
result_t svcReplyAndReceiveWithUserBuffer(u32 *handle_idx, void *buffer, u64 size, session_h *handles, u32 num_handles, session_h reply_session, u64 timeout);
// createEvent
// 0x46-0x4E?
// sleepSystem
result_t svcReadWriteRegister(u32 *out_value, u64 addr, u32 rw_mask, u32 in_value);
// setProcessActivity
result_t svcCreateSharedMemory(shared_memory_h *out, u64 size, u32 self_permissions, u32 foreign_permissions);
result_t svcMapTransferMemory(transfer_memory_h handle, void *addr, u64 size, u32 perm);
result_t svcUnmapTransferMemory(transfer_memory_h handle, void *addr, u64 size);
// createInterruptEvent
// queryPhysicalAddress
result_t svcQueryIoMapping(void *virt_addr, u64 phys_addr, u64 size);
// createDeviceAddressSpace
result_t svcAttachDeviceAddressSpace(u32 device, dev_addr_space_h space);
result_t svcDetachDeviceAddressSpace(u32 device, dev_addr_space_h space);
result_t svcMapDeviceAddressSpaceByForce(dev_addr_space_h space, process_h process, u64 dev_addr, u64 dev_size, u64 map_addr, u32 perm);
result_t svcMapDeviceAddressSpaceAligned(dev_addr_space_h space, process_h process, u64 dev_addr, u64 dev_size, u64 map_addr, u32 perm);
// mapDeviceAddressSpace
result_t svcUnmapDeviceAddressSpace(dev_addr_space_h space, process_h process, u64 map_addr, u64 map_size, u32 perm);
// invalidateProcessDataCache
// storeProcessDataCache
// flushProcessDataCache
result_t svcDebugActiveprocess(debug_h *out, u64 process_id);
// breakDebugProcess
// terminateDebugProcess
// getDebugEvent
// continueDebugEvent
// getProcessList
// getThreadList
// getDebugThreadContext
// setDebugThreadContext
result_t svcQueryDebugProcessMemory(memory_info_t *memory_info, u32 *page_info, debug_h debug, u64 addr);
result_t svcReadDebugProcessMemory(void *buffer, debug_h debug, u64 addr, u64 size);
result_t svcWriteDebugProcessMemory(debug_h debug, void *buffer, u64 addr, u64 size);
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
