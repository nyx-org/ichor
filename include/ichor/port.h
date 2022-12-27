#ifndef ICHOR_PORT_H
#define ICHOR_PORT_H
#include <stddef.h>
#include <stdint.h>

#define PORT_SEND (0)
#define PORT_RECV (1)

#define PORT_RIGHT_RECV (1 << 0)
#define PORT_RIGHT_SEND (1 << 1)

#define PORT_MSG_TYPE_DEFAULT (1 << 0)
#define PORT_MSG_TYPE_RIGHT (1 << 1)
#define PORT_MSG_TYPE_RIGHT_ONCE (1 << 2)

#define PORT_DEAD (~0)
#define PORT_NULL (0)

#define PORT_COMMON_BOOTSTRAP 0

typedef struct __attribute__((packed))
{
    uintptr_t address;
    uint16_t size;
} PortSharedMemoryDescriptor;

typedef struct __attribute__((packed))
{
    uint8_t type;                         /* Type of message */
    uint32_t size;                        /* Size of payload */
    uint32_t dest;                        /* Destination port */
    uint32_t port_right;                  /* Optional: Port right to send */
    uint8_t shmd_count;                   /* Shared memory descriptor count */
    PortSharedMemoryDescriptor shmds[16]; /* Shared memory descriptors */
} PortMessageHeader;

typedef uint32_t Port;

int ichor_wait_for_message(Port port, size_t size, void *buffer);
int ichor_send_bidirectional_message(Port port_to_reply_on, PortMessageHeader *message);
PortMessageHeader *ichor_send_and_wait_for_reply(PortMessageHeader *message_to_send, size_t size_to_recv, PortMessageHeader *recv);
PortMessageHeader *ichor_send_and_wait_for_reply_port(Port port, PortMessageHeader *message_to_send, size_t size_to_recv, PortMessageHeader *recv);
PortMessageHeader *ichor_send_port_right_and_wait_for_reply(Port port, PortMessageHeader *message, size_t size_to_recv, PortMessageHeader *recv);

#endif