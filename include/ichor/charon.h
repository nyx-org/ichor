#ifndef ICHOR_CHARON_H
#define ICHOR_CHARON_H
#include <ichor/base.h>

#define PACKED __attribute__((packed))

#define CHARON_MODULE_MAX 16
#define CHARON_MMAP_SIZE_MAX 128

typedef enum
{
    MMAP_FREE,
    MMAP_RESERVED,
    MMAP_MODULE,
    MMAP_RECLAIMABLE,
    MMAP_FRAMEBUFFER
} CharonMemoryMapEntryType;

typedef struct PACKED
{

    uintptr_t base;
    size_t size;
    CharonMemoryMapEntryType type;
} CharonMemoryMapEntry;

typedef struct PACKED
{
    uint8_t count;
    CharonMemoryMapEntry entries[CHARON_MMAP_SIZE_MAX];
} CharonMemoryMap;

typedef struct PACKED
{
    bool present;
    uintptr_t address;
    uint32_t width, height, pitch, bpp;
} CharonFramebuffer;

typedef struct PACKED
{
    uint32_t size;
    uintptr_t address;
    const char name[16];
} CharonModule;

typedef struct PACKED
{
    uint8_t count;
    CharonModule modules[CHARON_MODULE_MAX];
} CharonModules;

typedef struct PACKED
{
    uintptr_t rsdp;
    CharonFramebuffer framebuffer;
    CharonModules modules;
    CharonMemoryMap memory_map;
} Charon;

#undef PACKED

#endif