#include <ichor/alloc.h>
#include <ichor/debug.h>
#include <ichor/libheap.h>
#include <ichor/syscalls.h>
#include <ichor/vm.h>

void *heap_hook_alloc_block(void *ctx, size_t size)
{
    (void)ctx;

    VmObject object = sys_vm_create(size, 0, 0);
    sys_vm_map(NULL, &object, VM_PROT_READ | VM_PROT_WRITE, -1, VM_MAP_ANONYMOUS);

    return object.buf;
}

void heap_hook_free_block(void *ctx, void *ptr, size_t size)
{
    (void)ctx;
    // munmap(ptr, size);
}

void heap_hook_error(void *ctx, const char *msg)
{
    (void)ctx;
    ichor_debug("%s", msg);
}

struct Heap _heap = {
    .alloc = heap_hook_alloc_block,
    .free = heap_hook_free_block,
    .error = heap_hook_error,
};

void *ichor_malloc(size_t size)
{
    void *res = heap_alloc(&_heap, size);
    return res;
}

void ichor_free(void *ptr)
{
    heap_free(&_heap, ptr);
}

void *ichor_realloc(void *ptr, size_t size)
{
    void *res = heap_realloc(&_heap, ptr, size);
    return res;
}

void *ichor_calloc(size_t num, size_t size)
{
    void *res = heap_calloc(&_heap, num, size);
    return res;
}
