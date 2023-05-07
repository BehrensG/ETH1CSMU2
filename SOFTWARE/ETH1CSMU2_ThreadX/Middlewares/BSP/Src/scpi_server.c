/*
 * scpi_server.c
 *
 *  Created on: Feb 2, 2020
 *      Author: grzegorz
 */


/*-
 * Copyright (c) 2012-2013 Jan Breuer,
 *
 * All Rights Reserved
 *
 * Redistribution and use in source and binary forms, with or without
 * modification, are permitted provided that the following conditions are
 * met:
 * 1. Redistributions of source code must retain the above copyright notice,
 *    this list of conditions and the following disclaimer.
 * 2. Redistributions in binary form must reproduce the above copyright
 *    notice, this list of conditions and the following disclaimer in the
 *    documentation and/or other materials provided with the distribution.
 *
 * THIS SOFTWARE IS PROVIDED BY THE AUTHORS ``AS IS'' AND ANY EXPRESS OR
 * IMPLIED WARRANTIES, INCLUDING, BUT NOT LIMITED TO, THE IMPLIED
 * WARRANTIES OF MERCHANTABILITY AND FITNESS FOR A PARTICULAR PURPOSE ARE
 * DISCLAIMED. IN NO EVENT SHALL THE AUTHORS OR CONTRIBUTORS BE LIABLE
 * FOR ANY DIRECT, INDIRECT, INCIDENTAL, SPECIAL, EXEMPLARY, OR
 * CONSEQUENTIAL DAMAGES (INCLUDING, BUT NOT LIMITED TO, PROCUREMENT OF
 * SUBSTITUTE GOODS OR SERVICES; LOSS OF USE, DATA, OR PROFITS; OR
 * BUSINESS INTERRUPTION) HOWEVER CAUSED AND ON ANY THEORY OF LIABILITY,
 * WHETHER IN CONTRACT, STRICT LIABILITY, OR TORT (INCLUDING NEGLIGENCE
 * OR OTHERWISE) ARISING IN ANY WAY OUT OF THE USE OF THIS SOFTWARE, EVEN
 * IF ADVISED OF THE POSSIBILITY OF SUCH DAMAGE.
 */

/**
 * @file   scpi_server.c
 * @date   Thu Nov 15 10:58:45 UTC 2012
 *
 * @brief  TCP/IP SCPI Server
 *
 *
 */


#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "tx_api.h"
#include "nx_api.h"

#include "scpi_def.h"
#include "scpi/scpi.h"


TX_THREAD scpi_server_thread;

#define DEVICE_PORT 2000
#define CONTROL_PORT 2001

#define SCPI_THREAD_MEM_SIZE	2048
#define SCPI_THREAD_INPUT_VAL	0
#define SCPI_THREAD_PRIO		5
extern UCHAR* tx_memory_ptr;


#define SCPI_MSG_TIMEOUT                0
#define SCPI_MSG_TEST                   1
#define SCPI_MSG_IO_LISTEN              2
#define SCPI_MSG_CONTROL_IO_LISTEN      3
#define SCPI_MSG_IO                     4
#define SCPI_MSG_CONTROL_IO             5
#define SCPI_MSG_SET_ESE_REQ            6
#define SCPI_MSG_SET_ERROR              7

typedef struct {
	char *io_listen;
    char *control_io_listen;
    char *io;
    char *control_io;
    uint16_t evtQueue;
    //FILE * fio;
    //fd_set fds;
} user_data_t;

user_data_t user_data = {
    .io_listen = NULL,
    .io = NULL,
    .control_io_listen = NULL,
    .control_io = NULL,
    .evtQueue = 0,
};

uint8_t msg;
UCHAR data_buffer[2048];
ULONG bytes_read;
UINT source_port;

TX_QUEUE	scpi_queue;



struct _queue_event_t {
    uint8_t cmd;
    uint8_t param1;
    int16_t param2;
} __attribute__((__packed__));
typedef struct _queue_event_t queue_event_t;



size_t SCPI_Write(scpi_t * context, const char * data, size_t len)
{
	UINT status;
	//NX_PACKET *my_packet;
	ULONG packet_size;
    if (context->user_context != 0) {



    	//status = nx_tcp_socket_mss_get(&io_listen, &packet_size);
    	//status = nx_packet_allocate(&AppPool, &my_packet, NX_TCP_PACKET, NX_WAIT_FOREVER);
    	status = nx_packet_data_append(my_packet, (VOID *)data, len, &AppPool, NX_WAIT_FOREVER);
      /*  if(nx_tcp_socket_send(&io_listen, my_packet, NX_WAIT_FOREVER) == NX_SUCCESS)
        {

        	//status = nx_packet_release(my_packet);
        	return 0;

        }
        else
        {
        	status = nx_packet_release(my_packet);
        	return 1;
        }
        */
    }
}

scpi_result_t SCPI_Flush(scpi_t * context) {
    if (context->user_context != NULL) {

    }
    return SCPI_RES_OK;
}

int SCPI_Error(scpi_t * context, int_fast16_t err) {
    (void) context;
    // BEEP
    if (err != 0) {
        /* New error */
        /* Beep */
        /* Error LED ON */
    } else {
        /* No more errors in the queue */
        /* Error LED OFF */
    }
    return 0;
}

scpi_result_t SCPI_Control(scpi_t * context, scpi_ctrl_name_t ctrl, scpi_reg_val_t val) {
    char b[16];

    return SCPI_RES_OK;
}

scpi_result_t SCPI_Reset(scpi_t * context) {

    (void) context;

    return SCPI_RES_OK;
}

scpi_result_t SCPI_SystemCommTcpipControlQ(scpi_t * context) {
    SCPI_ResultInt(context, CONTROL_PORT);
    return SCPI_RES_OK;
}

static void setEseReq(void) {
    SCPI_RegSetBits(&scpi_context, SCPI_REG_ESR, ESR_REQ);
}

static void setError(int16_t err) {
    SCPI_ErrorPush(&scpi_context, err);
}

void SCPI_RequestControl(void) {
    queue_event_t msg;
    msg.cmd = SCPI_MSG_SET_ESE_REQ;

    /* Avoid sending evtQueue message if ESR_REQ is already set
    if((SCPI_RegGet(&scpi_context, SCPI_REG_ESR) & ESR_REQ) == 0) {
        xQueueSend(user_data.evtQueue, &msg, 1000);
    }
     */

   // xQueueSend(user_data.evtQueue, &msg, 1000);
}

void SCPI_AddError(int16_t err) {
    queue_event_t msg;
    msg.cmd = SCPI_MSG_SET_ERROR;
    msg.param2 = err;

  //  xQueueSend(user_data.evtQueue, &msg, 1000);
}

void  nx_iperf_tcp_rx_disconnect_received(NX_TCP_SOCKET *socket)
{
    /* Check for proper disconnected socket.  */
    if (socket != &io_listen)
    {
    	 nx_tcp_server_socket_unlisten(&IpInstance, 2000);
    	nx_tcp_socket_delete(&io_listen);
        error_counter++;
        createServer(2000);
        msg = SCPI_MSG_IO_LISTEN;
    }

}

void  nx_iperf_tcp_rx_connect_received(NX_TCP_SOCKET *socket_ptr, UINT port)
{
	UINT ret;
    /* Check for the proper socket and port.  */
    if ((socket_ptr != &io_listen) || (port != 2000))
    {
        error_counter++;
    }
    else
    {
    	msg = SCPI_MSG_IO_LISTEN;
    }

}

void createServer(int port)
{
	UINT status;
	ULONG       actual_status;



    /* Create a socket.  */
    status =  nx_tcp_socket_create(&IpInstance, &io_listen, "TCP Server Socket",
                                       NX_IP_NORMAL, NX_FRAGMENT_OKAY, NX_IP_TIME_TO_LIVE, 32 * 1024,
                                       NX_NULL, nx_iperf_tcp_rx_disconnect_received);

        /* Check for error.  */
        if (status)
        {
            return;
        }

        /* Setup this thread to listen.  */
        status =  nx_tcp_server_socket_listen(&IpInstance, port, &io_listen, 5, nx_iperf_tcp_rx_connect_received);

        /* Check for error.  */
        if (status)
        {
            nx_tcp_socket_delete(&io_listen);
            return;
        }


}

static int processIoListen()
{


    if (nx_tcp_server_socket_accept(&io_listen, NX_WAIT_FOREVER) == NX_SUCCESS)
    {
    	msg = SCPI_MSG_IO;
    }


    return 0;
}


static int processIo()
{
	NX_PACKET* rx_packet;
	ULONG status;
	TX_MEMSET(data_buffer, '\0', sizeof(data_buffer));

    if (nx_tcp_socket_receive(&io_listen, &rx_packet, NX_WAIT_FOREVER) == NX_SUCCESS)
    {
    	 nx_packet_data_retrieve(rx_packet, data_buffer, &bytes_read);
     	 nx_packet_release(rx_packet);
    	 tx_thread_sleep(5);

    }
    else
    {
    	return 1;
    }

    if (bytes_read > 0)
    {
    	status = nx_packet_allocate(&AppPool, &my_packet, NX_TCP_PACKET, NX_WAIT_FOREVER);
       SCPI_Input(&scpi_context, data_buffer, bytes_read);
       status = nx_tcp_socket_send(&io_listen, my_packet, NX_WAIT_FOREVER);
         msg = SCPI_MSG_IO;

    } else
    {
        //goto fail2;
    }


    return 0;

}

static void scpi_server_thread_entry(ULONG thread_input)
{
    queue_event_t evt;
    UINT status;


    status = tx_queue_create(&scpi_queue, "scpi_queue", 4,queue_buffer, 160);

    // user_context will be pointer to socket
    SCPI_Init(&scpi_context,
            scpi_commands,
            &scpi_interface,
            scpi_units_def,
            SCPI_IDN1, SCPI_IDN2, SCPI_IDN3, SCPI_IDN4,
            scpi_input_buffer, SCPI_INPUT_BUFFER_LENGTH,
            scpi_error_queue_data, SCPI_ERROR_QUEUE_SIZE);

    scpi_context.user_context = &user_data;
    createServer(DEVICE_PORT);

    while (1) {
        if (msg == SCPI_MSG_IO_LISTEN) { // timeout
        	processIoListen();
        }

        if (msg == SCPI_MSG_IO) {
        	processIo();
        }
    tx_thread_sleep(100);
    }
}

void scpi_server_init(TX_BYTE_POOL *byte_pool)
{
	UINT ret;

	if (tx_byte_allocate(byte_pool, (VOID **) &tx_memory_ptr, SCPI_THREAD_MEM_SIZE, TX_NO_WAIT) != TX_SUCCESS)
	{
		return TX_POOL_ERROR;
	}

	ret = tx_thread_create(&scpi_server_thread,
							"SCPI Server",
							scpi_server_thread_entry,
							SCPI_THREAD_INPUT_VAL,
							tx_memory_ptr,
							SCPI_THREAD_MEM_SIZE,
							SCPI_THREAD_PRIO,
							SCPI_THREAD_PRIO,
							TX_NO_TIME_SLICE,
							TX_AUTO_START);
}
