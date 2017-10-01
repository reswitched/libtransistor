.align 4

.macro SVC_BEGIN name
    .section .text.\name, "ax", %progbits
    .global \name
    .type \name, %function
    .align 2
    .cfi_startproc
\name:
.endm

.macro SVC_END
    .cfi_endproc
.endm

.macro DEFINE_OUT00_SVC id, name
    SVC_BEGIN svc\name
        svc \id
        ret
    SVC_END
.endm

.macro DEFINE_OUT32_SVC id, name
    SVC_BEGIN svc\name
        str x0, [sp, #-0x10]!
        svc \id
        ldr x2, [sp]
        str w1, [x2]
        add sp, sp, #0x10
        ret
    SVC_END
.endm

.macro DEFINE_OUT64_SVC id, name
    SVC_BEGIN svc\name
        str x0, [sp, #-0x10]!
        svc \id
        ldr x2, [sp]
        str x1, [x2]
        add sp, sp, #0x10
        ret
    SVC_END
.endm

.macro DEFINE_OUT32_ARG2_SVC id, name
    SVC_BEGIN svc\name
        str x1, [sp, #-0x10]!
        svc \id
        ldr x2, [sp]
        str w1, [x2]
        add sp, sp, #0x10
        ret
    SVC_END
.endm

.macro DEFINE_OUT32_PAIR_SVC id, name
    SVC_BEGIN svc\name
        stp x0, x1, [sp, #-0x10]!
        svc \id
        ldr x3, [sp]
        str w1, [x3]
        ldr x3, [sp, #8]
        str w2, [x3]
        add sp, sp, #0x10
        ret
    SVC_END
.endm

DEFINE_OUT64_SVC 0x01, SetHeapSize
DEFINE_OUT00_SVC 0x02, SetMemoryPermission
DEFINE_OUT00_SVC 0x03, SetMemoryAttribute
DEFINE_OUT00_SVC 0x04, MapMemory
DEFINE_OUT00_SVC 0x05, UnmapMemory
DEFINE_OUT32_SVC 0x06, QueryMemory

DEFINE_OUT00_SVC 0x07, ExitProcess

DEFINE_OUT32_SVC 0x08, CreateThread
DEFINE_OUT00_SVC 0x09, StartThread
DEFINE_OUT00_SVC 0x0A, ExitThread
DEFINE_OUT00_SVC 0x0B, SleepThread
DEFINE_OUT32_SVC 0x0C, GetThreadPriority
DEFINE_OUT00_SVC 0x0D, SetThreadPriority
SVC_BEGIN svcGetThreadCoreMask
    stp x0, x1, [sp, #-0x10]!
    svc 0xE
    ldr x3, [sp]
    str w1, [x3]
    ldr x3, [sp, #8]
    str x2, [x3]
    add sp, sp, #0x10
    ret
SVC_END
DEFINE_OUT00_SVC 0x0F, SetThreadCoreMask
DEFINE_OUT00_SVC 0x10, GetCurrentProcessorNumber

DEFINE_OUT00_SVC 0x11, SignalEvent
DEFINE_OUT00_SVC 0x12, ClearEvent

DEFINE_OUT00_SVC 0x13, MapSharedMemory
DEFINE_OUT00_SVC 0x14, UnmapSharedMemory
DEFINE_OUT32_SVC 0x15, CreateTransferMemory

DEFINE_OUT00_SVC 0x16, CloseHandle

DEFINE_OUT00_SVC 0x17, ResetSignal
DEFINE_OUT32_SVC 0x18, WaitSynchronization
DEFINE_OUT00_SVC 0x19, CancelSynchronization
DEFINE_OUT00_SVC 0x1A, ArbitrateLock
DEFINE_OUT00_SVC 0x1B, ArbitrateUnlock
DEFINE_OUT00_SVC 0x1C, WaitProcessWideKeyAtomic
DEFINE_OUT00_SVC 0x1D, SignalProcessWideKey
DEFINE_OUT00_SVC 0x1E, GetSystemTick

DEFINE_OUT32_SVC 0x1F, ConnectToNamedPort
DEFINE_OUT00_SVC 0x20, SendSyncRequestLight
DEFINE_OUT00_SVC 0x21, SendSyncRequest
DEFINE_OUT00_SVC 0x22, SendSyncRequestWithUserBuffer
DEFINE_OUT32_SVC 0x23, SendAsyncRequestWithUserBuffer

DEFINE_OUT64_SVC 0x24, GetProcessId
DEFINE_OUT64_SVC 0x25, GetThreadId

DEFINE_OUT00_SVC 0x26, Break
DEFINE_OUT00_SVC 0x27, OutputDebugString
DEFINE_OUT00_SVC 0x28, ReturnFromException

DEFINE_OUT64_SVC 0x29, GetInfo
DEFINE_OUT00_SVC 0x2A, FlushEntireDataCache
DEFINE_OUT00_SVC 0x2B, FlushDataCache

SVC_BEGIN svcGetLastThreadInfo
    str x2, [sp, #-0x10]!
    stp x0, x1, [sp, #-0x10]!
    svc 0x2F
    ldr x7, [sp]
    str x1, [x7]
    str x2, [x7, #8]
    str x3, [x7, #0x10]
    str x4, [x7, #0x18]
    ldr x7, [sp, #8]
    str x5, [x7]
    ldr x7, [sp, #0x10]
    str w6, [x7]
    add sp, sp, #0x20
    ret
SVC_END


DEFINE_OUT64_SVC 0x30, GetResourceLimitLimitValue
DEFINE_OUT64_SVC 0x31, GetResourceLimitCurrentValue

DEFINE_OUT00_SVC 0x32, SetThreadActivity
DEFINE_OUT00_SVC 0x33, GetThreadContext3

DEFINE_OUT00_SVC 0x3C, DumpInfo

DEFINE_OUT32_PAIR_SVC 0x40, CreateSession
DEFINE_OUT32_SVC 0x41, AcceptSession
DEFINE_OUT00_SVC 0x42, ReplyAndReceiveLight
DEFINE_OUT32_SVC 0x43, ReplyAndReceive
DEFINE_OUT32_SVC 0x44, ReplyAndReceiveWithUserBuffer
DEFINE_OUT32_PAIR_SVC 0x45, CreateEvent
DEFINE_OUT00_SVC 0x4D, SleepSystem

DEFINE_OUT32_SVC 0x4E, ReadWriteRegister
DEFINE_OUT00_SVC 0x4F, SetProcessActivity

DEFINE_OUT32_SVC 0x50, CreateSharedMemory
DEFINE_OUT00_SVC 0x51, MapTransferMemory
DEFINE_OUT00_SVC 0x52, UnmapTransferMemory
DEFINE_OUT32_SVC 0x53, CreateInterruptEvent
SVC_BEGIN svcQueryPhysicalAddress
    str x0, [sp, #-0x10]!
    svc 0x54
    ldr x4, [sp]
    str x1, [x4]
    str x2, [x4, #8]
    str x3, [x4, #0x10]
    add sp, sp, #0x10
    ret
SVC_END

DEFINE_OUT64_SVC 0x55, QueryIoMapping
DEFINE_OUT32_SVC 0x56, CreateDeviceAddressSpace
DEFINE_OUT00_SVC 0x57, AttachDeviceAddressSpace
DEFINE_OUT00_SVC 0x58, DetachDeviceAddressSpace
DEFINE_OUT00_SVC 0x59, MapDeviceAddressSpaceByForce
DEFINE_OUT00_SVC 0x5A, MapDeviceAddressSpaceAligned
DEFINE_OUT64_SVC 0x5B, MapDeviceAddressSpace
DEFINE_OUT00_SVC 0x5C, UnmapDeviceAddressSpace
DEFINE_OUT00_SVC 0x5D, InvalidateProcessDataCache
DEFINE_OUT00_SVC 0x5E, StoreProcessDataCache
DEFINE_OUT00_SVC 0x5F, FlushProcessDataCache

DEFINE_OUT32_SVC 0x60, DebugActiveProcess
DEFINE_OUT00_SVC 0x61, BreakDebugProcess
DEFINE_OUT00_SVC 0x62, TerminateDebugProcess
DEFINE_OUT00_SVC 0x63, GetDebugEvent
DEFINE_OUT00_SVC 0x64, ContinueDebugEvent
DEFINE_OUT32_SVC 0x65, GetProcessList
DEFINE_OUT32_SVC 0x66, GetThreadList
DEFINE_OUT00_SVC 0x67, GetDebugThreadContext
DEFINE_OUT00_SVC 0x68, SetDebugThreadContext

DEFINE_OUT32_ARG2_SVC 0x69, QueryDebugProcessMemory
DEFINE_OUT00_SVC 0x6A, ReadDebugProcessMemory
DEFINE_OUT00_SVC 0x6B, WriteDebugProcessMemory
DEFINE_OUT00_SVC 0x6C, SetHardwareBreakPoint
SVC_BEGIN svcGetDebugThreadParam
    stp x0, x1, [sp, #-0x10]!
    svc 0x6D
    ldr x3, [sp]
    str x1, [x3]
    ldr x3, [sp, #8]
    str w2, [x3]
    add sp, sp, #0x10
    ret
SVC_END

DEFINE_OUT32_PAIR_SVC 0x70, CreatePort
DEFINE_OUT32_SVC 0x71, ManageNamedPort
DEFINE_OUT32_SVC 0x72, ConnectToPort

DEFINE_OUT00_SVC 0x73, SetProcessMemoryPermission
DEFINE_OUT00_SVC 0x74, MapProcessMemory
DEFINE_OUT00_SVC 0x75, UnmapProcessMemory
DEFINE_OUT32_ARG2_SVC 0x76, QueryProcessMemory
DEFINE_OUT00_SVC 0x77, MapProcessCodeMemory
DEFINE_OUT00_SVC 0x78, UnmapProcessCodeMemory

DEFINE_OUT32_SVC 0x79, CreateProcess
DEFINE_OUT00_SVC 0x7A, StartProcess
DEFINE_OUT00_SVC 0x7B, TerminateProcess
DEFINE_OUT64_SVC 0x7C, GetProcessInfo

DEFINE_OUT32_SVC 0x7D, CreateResourceLimit
DEFINE_OUT00_SVC 0x7E, SetResourceLimitLimitValue

DEFINE_OUT00_SVC 0x7F, CallSecureMonitor
