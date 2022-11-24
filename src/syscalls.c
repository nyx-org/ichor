#include "ichor/port.h"
#include <ichor/error.h>
#include <ichor/syscalls.h>

int sys_errno = ERR_SUCCESS;

#ifdef __x86_64__

uint64_t syscall0(int syscall)
{
    uint64_t ret;

    __asm__ volatile("int $0x42"
                     : "=b"(sys_errno), "=a"(ret)
                     : "a"(syscall));
    return ret;
}

uint64_t syscall1(int syscall, uint64_t param1)
{
    uint64_t ret;

    __asm__ volatile("int $0x42"
                     : "=b"(sys_errno), "=a"(ret)
                     : "a"(syscall), "D"(param1));

    return ret;
}

uint64_t syscall2(int syscall, uint64_t param1, uint64_t param2)
{
    uint64_t ret;

    __asm__ volatile("int $0x42"
                     : "=b"(sys_errno), "=a"(ret)
                     : "a"(syscall), "D"(param1), "S"(param2));

    return ret;
}

uint64_t syscall3(int syscall, uint64_t param1, uint64_t param2, uint64_t param3)
{
    uint64_t ret;

    __asm__ volatile("int $0x42"
                     : "=b"(sys_errno), "=a"(ret)
                     : "a"(syscall), "D"(param1), "S"(param2), "d"(param3));

    return ret;
}

uint64_t syscall4(int syscall, uint64_t param1, uint64_t param2, uint64_t param3, uint64_t param4)
{
    uint64_t ret;

    __asm__ volatile("int $0x42"
                     : "=b"(sys_errno), "=a"(ret)
                     : "a"(syscall), "D"(param1), "S"(param2), "d"(param3), "c"(param4));

    return ret;
}

#endif

void sys_log(const char *msg)
{
    syscall1(SYS_LOG, (uint64_t)msg);
}

void sys_exit(int status)
{
    syscall1(SYS_EXIT, status);
}

size_t sys_msg(uint8_t msg_type, Port port_to_receive, size_t bytes_to_receive, PortMessageHeader *header)
{
    return syscall4(SYS_MSG, msg_type, port_to_receive, bytes_to_receive, (uint64_t)header);
}

Port sys_alloc_port(uint8_t rights)
{
    return syscall1(SYS_ALLOC_PORT, rights);
}

Port sys_get_common_port(Port id)
{
    return syscall1(SYS_GET_COMMON_PORT, id);
}

void sys_register_common_port(Port id, Port port)
{
    syscall2(SYS_REGISTER_COMMON_PORT, id, port);
}

VmObject sys_vm_create(size_t size, uintptr_t addr, uint16_t flags)
{
    VmObject ret;
    struct
    {
        size_t size;
        uintptr_t addr;
        uint16_t flags;
    } params = {size, addr, flags};

    syscall2(SYS_VM_CREATE, (uintptr_t)&params, (uintptr_t)&ret);

    return ret;
}

void sys_start_task(Task *task, uintptr_t entry_point)
{
    syscall4(SYS_START_TASK, (uintptr_t)task, entry_point, -1, true);
}

void sys_start_task_stack(Task *task, uintptr_t entry_point, uintptr_t stack_ptr, bool alloc)
{
    syscall4(SYS_START_TASK, (uintptr_t)task, entry_point, stack_ptr, alloc);
}

void sys_vm_map(VmObject *vm, uint16_t protection, uintptr_t vaddr, uint16_t flags)
{
    struct
    {
        VmObject *object;
        uint16_t protection;
        uintptr_t vaddr;
        uint16_t flags;
    } params = {vm, protection, vaddr, flags};

    syscall1(SYS_VM_MAP, (uintptr_t)&params);
}