#ifndef ICHOR_PORT_H
#define ICHOR_PORT_H
#include <stdint.h>

#define PORT_SEND (0)
#define PORT_RECV (1)

#define PORT_RIGHT_RECV (1 << 0)
#define PORT_RIGHT_SEND (1 << 1)

#define PORT_MSG_TYPE_DEFAULT (1 << 0)
#define PORT_MSG_TYPE_RIGHT (1 << 1)

#define PORT_DEAD (~0)
#define PORT_NULL (0)

typedef struct __attribute__((packed))
{
    uint8_t type;        /* Type of message */
    uint32_t size;       /* Size of payload */
    uint32_t dest;       /* Destination port */
    uint32_t port_right; /* Optional: Port right to send */
} PortMessageHeader;

typedef uint32_t Port;
#endif