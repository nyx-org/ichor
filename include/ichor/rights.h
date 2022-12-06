#ifndef ICHOR_RIGHTS_H
#define ICHOR_RIGHTS_H
#include <ichor/base.h>

#define RIGHT_NULL 0
#define RIGHT_IO (1 << 0)
#define RIGHT_DMA (1 << 1)
#define RIGHT_REGISTER_DMA (1 << 2)

typedef uint8_t Rights;

#endif