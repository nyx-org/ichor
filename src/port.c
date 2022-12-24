#include <ichor/error.h>
#include <ichor/port.h>
#include <ichor/syscalls.h>

int ichor_wait_for_message(Port port, size_t size, void *buffer)
{
    while (true)
    {
        if (!sys_msg(PORT_RECV, port, size, buffer))
        {
            sys_yield();
        }
	else
	{
	    break;
	}
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

PortMessageHeader *ichor_send_and_wait_for_reply(PortMessageHeader *message_to_send, size_t size_to_recv, PortMessageHeader *msg_to_receive)
{
    Port port_to_reply_on = sys_alloc_port(PORT_RIGHT_RECV | PORT_RIGHT_SEND);

    ichor_send_bidirectional_message(port_to_reply_on, message_to_send);

    ichor_wait_for_message(port_to_reply_on, size_to_recv, msg_to_receive);

    sys_free_port(port_to_reply_on);

    return msg_to_receive;
}

PortMessageHeader *ichor_send_and_wait_for_reply_port(Port port, PortMessageHeader *message, size_t size_to_recv, PortMessageHeader *recv)
{
    ichor_send_bidirectional_message(port, message);

    ichor_wait_for_message(port, size_to_recv, recv);

    return message;
}

PortMessageHeader *ichor_send_port_right_and_wait_for_reply(Port port, PortMessageHeader *message, size_t size_to_recv, PortMessageHeader *recv)
{
    message->type = PORT_MSG_TYPE_RIGHT;
    message->port_right = port;

    sys_msg(PORT_SEND, PORT_NULL, -1, message);

    ichor_wait_for_message(port, size_to_recv, recv);

    return message;
}
