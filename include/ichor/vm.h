#ifndef ICHOR_VM_H
#define ICHOR_VM_H
#include <stddef.h>

#define VM_MEM_DMA (1 << 0)

#define VM_PROT_NONE (1 << 0)
#define VM_PROT_READ (1 << 1)
#define VM_PROT_WRITE (1 << 2)
#define VM_PROT_EXEC (1 << 3)

#define VM_MAP_ANONYMOUS (1 << 0)
#define VM_MAP_FIXED (1 << 1)
#define VM_MAP_PHYS (1 << 2)

typedef struct __attribute__((packed))
{
    void *buf;
    size_t size;
} VmObject;

#endif