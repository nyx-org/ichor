#ifndef ICHOR_ALLOC_H
#define ICHOR_ALLOC_H
#include <stddef.h>
#include <stdint.h>

void *ichor_malloc(size_t size);
void ichor_free(void *ptr);
void *ichor_realloc(void *ptr, size_t size);
void *ichor_calloc(size_t num, size_t size);

#endif