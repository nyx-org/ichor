#ifndef ICHOR_SYSCALLS_H
#define ICHOR_SYSCALLS_H
#include <ichor/port.h>
#include <ichor/task.h>
#include <ichor/vm.h>
#include <stdbool.h>
#include <stddef.h>
#include <stdint.h>

#define SYS_LOG 0
#define SYS_EXIT 1
#define SYS_MSG 2
#define SYS_ALLOC_PORT 3
#define SYS_GET_COMMON_PORT 4
#define SYS_REGISTER_COMMON_PORT 5
#define SYS_VM_CREATE 6
#define SYS_CREATE_TASK 7
#define SYS_START_TASK 8
#define SYS_VM_WRITE 9
#define SYS_VM_MAP 10

extern int sys_errno;

uint64_t syscall0(int syscall);
uint64_t syscall1(int syscall, uint64_t param1);
uint64_t syscall2(int syscall, uint64_t param1, uint64_t param2);
uint64_t syscall3(int syscall, uint64_t param1, uint64_t param2, uint64_t param3);
uint64_t syscall4(int syscall, uint64_t param1, uint64_t param2, uint64_t param3, uint64_t param4);

/* Outputs a string to the kernel's debug buffer */
void sys_log(const char *string);

/* Exits the current task with status `status` */
void sys_exit(int status);

/* Performs a message of type `msg_type` with `header` to/from port `port`. Returns size sent/received */
size_t sys_msg(uint8_t msg_type, Port port_to_receive, size_t bytes_to_receive, PortMessageHeader *header);

/* Allocates a port and returns it */
Port sys_alloc_port(uint8_t rights);

/* Returns a port right to the common port `id` */
Port sys_get_common_port(Port id);

/* Registers a port right to the common port `id` */
void sys_register_common_port(Port id, Port port);

/* Creates a new VmObject with size `size`, flags `flags` and addr `addr` */
VmObject sys_vm_create(size_t size, uintptr_t addr, uint16_t flags);

/* Creates a new task */
Task *sys_create_task(void);

/* Starts a task at entry_point `entry_point` */
void sys_start_task(Task *task, uintptr_t entry_point);

/* Starts a task at entry_point `entry_point`, with stack pointer `stack_ptr`, allocates if `alloc` is true */
void sys_start_task_stack(Task *task, uintptr_t entry_point, uintptr_t stack_ptr, bool alloc);

/* Map object `vm` with protection `protection` at virtual address `vaddr` (optional) with flags `flags` */
void sys_vm_map(VmObject *vm, uint16_t protection, uintptr_t vaddr, uint16_t flags);

#endif