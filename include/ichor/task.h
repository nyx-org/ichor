#ifndef ICHOR_TASK_H
#define ICHOR_TASK_H
#include <stddef.h>

typedef struct __attribute__((packed))
{
    void *space;
    size_t pid;
} Task;

#endif