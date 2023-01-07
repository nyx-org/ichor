#include <ichor/alloc.h>
#include <ichor/debug.h>
#include <ichor/liballoc.h>
#include <ichor/syscalls.h>
#include <ichor/vm.h>

void *liballoc_alloc(size_t n)
{
    VmObject object = sys_vm_create(n * 4096, 0, 0);
    sys_vm_map(NULL, &object, VM_PROT_READ | VM_PROT_WRITE, -1, VM_MAP_ANONYMOUS);

    return object.buf;
}

int liballoc_free(void *ptr, size_t n)
{
    (void)ptr;
    (void)n;
    return 0;
}

int liballoc_lock()
{
    return 0;
}

int liballoc_unlock()
{
    return 0;
}
