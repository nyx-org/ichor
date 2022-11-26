#ifndef ICHOR_BASE_H
#define ICHOR_BASE_H
#include <stdbool.h>
#include <stddef.h>
#include <stdint.h>

#define DIV_CEIL(x, align) (((x) + (align)-1) / (align))
#define ALIGN_UP(x, align) (((x) + (align)-1) & ~((align)-1))
#define ALIGN_DOWN(x, align) ((x) & ~((align)-1))

#endif