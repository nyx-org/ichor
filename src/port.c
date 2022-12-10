#include <ichor/error.h>
#include <ichor/port.h>
#include <ichor/syscalls.h>

int ichor_wait_for_message(Port port, size_t size, void *buffer)
{
    size_t bytes_received = 0;
    while (bytes_received == 0)
    {
        bytes_received = sys_msg(PORT_RECV, port, size, buffer);
    }

    return ERR_SUCCESS;
}

int ichor_send_bidirectional_message(Port port_to_reply_on, PortMessageHeader *message)
{
    message->type = PORT_MSG_TYPE_RIGHT_ONCE;
    message->port_right = port_to_reply_on;

    sys_msg(PORT_SEND, PORT_NULL, -1, message);

    return sys_errno;
}

PortMessageHeader *ichor_send_and_wait_for_reply(PortMessageHeader *message)
{
    Port port_to_reply_on = sys_alloc_port(PORT_RIGHT_RECV | PORT_RIGHT_SEND);

    ichor_send_bidirectional_message(port_to_reply_on, message);

    ichor_wait_for_message(port_to_reply_on, message->size, message);

    sys_free_port(port_to_reply_on);

    return message;
}

PortMessageHeader *ichor_send_and_wait_for_reply_port(Port port, PortMessageHeader *message)
{
    ichor_send_bidirectional_message(port, message);

    ichor_wait_for_message(port, message->size, message);

    return message;
}