
#include <stdio.h>
#include <stdlib.h>
#include <string.h>


#include "scpi_def.h"
#include "scpi/scpi.h"

typedef struct {
	uint8_t	state;
} user_data_t;

user_data_t user_data = {
    .state = STATE_NONE
};

extern NX_IP	nx_ipv4_instance;
NX_TCP_SOCKET	nx_ipv4_tcp_socket;
extern NX_PACKET_POOL		nx_ipv4_packet_pool;

extern UCHAR* 		tx_memory_ptr;
extern TX_QUEUE		link_queue;

NX_PACKET* scpi_packet;

UCHAR data_buffer[NX_PACKET_POOL_SIZE];
uint32_t bytes_read;

size_t SCPI_Write(scpi_t * context, const char * data, size_t len)
{
	UINT ret;

    if (context->user_context != 0)
    {
    	ret = nx_packet_allocate(&nx_ipv4_packet_pool, &scpi_packet, NX_TCP_PACKET, NX_WAIT_FOREVER);
    	ret = nx_packet_data_append(scpi_packet, (VOID *)data, len, &nx_ipv4_packet_pool, NX_WAIT_FOREVER);
    	if(nx_tcp_socket_send(&nx_ipv4_tcp_socket, scpi_packet, NX_WAIT_FOREVER) == NX_SUCCESS)
        {
    		ret = nx_packet_release(scpi_packet);
    		tx_thread_sleep(5);
        	return 0;

        }
        else
        {
        	ret = nx_packet_release(scpi_packet);
        	return 1;
        }

    }
}

scpi_result_t SCPI_Flush(scpi_t * context)
{

    return SCPI_RES_OK;
}

int SCPI_Error(scpi_t * context, int_fast16_t err) {
    (void) context;

    return 0;
}

scpi_result_t SCPI_Control(scpi_t * context, scpi_ctrl_name_t ctrl, scpi_reg_val_t val)
{

    return SCPI_RES_OK;
}

scpi_result_t SCPI_Reset(scpi_t * context) {

    (void) context;

    return SCPI_RES_OK;
}


void  nx_tcp_disconnect_received(NX_TCP_SOCKET *socket)
{
    /* Check for proper disconnected socket.  */
    if (socket != NULL)
    {

    }

}

void  nx_tcp_connect_received(NX_TCP_SOCKET *socket_ptr, UINT port)
{
    /* Check for the proper socket and port.  */
    if ((socket_ptr != NULL) || (port != 2000))
    {
    	user_data.state = STATE_ACCEPT;
    }
    else
    {

    }

}


static void socket_init(int port)
{
	UINT ret;
	ULONG  actual_status;



    /* Create a socket.  */
	ret =  nx_tcp_socket_create(&nx_ipv4_instance,
								&nx_ipv4_tcp_socket,
								"SCPI server socket",
                                 NX_IP_NORMAL,
								 NX_FRAGMENT_OKAY,
								 NX_IP_TIME_TO_LIVE,
								 32 * 1024,
                                 NX_NULL,
								 nx_tcp_disconnect_received);

	if (ret)
	{
		user_data.state = STATE_INIT_ERR;
		return;
	}

	user_data.state = STATE_LISTEN;

}

static void socket_listen(int port)
{
	UINT ret;

	ret =  nx_tcp_server_socket_listen(&nx_ipv4_instance, port, &nx_ipv4_tcp_socket, 5, nx_tcp_connect_received);

	if(ret)
    {
		user_data.state = STATE_LISTEN_ERR;
    	nx_tcp_socket_delete(&nx_ipv4_tcp_socket);
        return;
    }
	user_data.state = STATE_ACCEPT;
}

static void socket_accept()
{
	UINT ret;

    ret = nx_tcp_server_socket_accept(&nx_ipv4_tcp_socket, NX_WAIT_FOREVER);

    if(ret)
    {
    	user_data.state = STATE_ACCEPT_ERR;
        return;
    }

    user_data.state = STATE_RECEIVE;

}



static void socket_receive()
{
	ULONG ret;
	TX_MEMSET(data_buffer, '\0', sizeof(data_buffer));

    if (nx_tcp_socket_receive(&nx_ipv4_tcp_socket, &scpi_packet, NX_WAIT_FOREVER) == NX_SUCCESS)
    {
    	 nx_packet_data_retrieve(scpi_packet, data_buffer, &bytes_read);
     	 nx_packet_release(scpi_packet);
    	 tx_thread_sleep(5);

    }
    else
    {
    	user_data.state = STATE_RELISTEN;
    	return;
    }

    if (bytes_read > 0)
    {

       SCPI_Input(&scpi_context, data_buffer, bytes_read);
       user_data.state = STATE_RECEIVE;

    } else
    {
    	user_data.state = STATE_RECEIVE_ERR;
    }


    return;

}

static void socket_relisten(int port)
{
	UINT ret;

	//ret = nx_tcp_server_socket_unlisten(&nx_ipv4_instance, 2000);
	ret = nx_tcp_server_socket_unaccept(&nx_ipv4_tcp_socket);
	ret = nx_tcp_server_socket_relisten(&nx_ipv4_instance, port, &nx_ipv4_tcp_socket);
	user_data.state = STATE_ACCEPT;
}

void tx_scpi_server_thread_entry(ULONG thread_input)
{
    UINT ret, link_queue_msg;

    SCPI_Init(&scpi_context,
            scpi_commands,
            &scpi_interface,
            scpi_units_def,
            SCPI_IDN1, SCPI_IDN2, SCPI_IDN3, SCPI_IDN4,
            scpi_input_buffer, SCPI_INPUT_BUFFER_LENGTH,
            scpi_error_queue_data, SCPI_ERROR_QUEUE_SIZE);

    scpi_context.user_context = &user_data;
    user_data.state = STATE_INIT;

    while (1)
    {
    	ret = tx_queue_receive(&link_queue, &link_queue_msg, TX_WAIT_FOREVER);

    	if(TX_SUCCESS == ret)
    	{
    		if(LINK_UP == link_queue_msg)
    		{
    			switch(user_data.state)
    			{
    				case STATE_INIT: socket_init(DEVICE_PORT); break;
    				case STATE_LISTEN: socket_listen(DEVICE_PORT); break;
    				case STATE_ACCEPT: socket_accept(); break;
    				case STATE_RECEIVE:socket_receive(); break;
    				case STATE_RELISTEN:socket_relisten(DEVICE_PORT); break;
     			}
    		}
    		else if(LINK_DOWN == link_queue_msg)
    		{

    		}
    	}
    	else
    	{

    	}

    	tx_thread_sleep(5);
    }

}
