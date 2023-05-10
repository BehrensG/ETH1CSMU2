#ifndef __SCPI_DEF_H_
#define __SCPI_DEF_H_

#include "scpi/scpi.h"

#include "tx_api.h"
#include "nx_api.h"
#include "app_netxduo.h"

#define SCPI_INPUT_BUFFER_LENGTH 512
#define SCPI_ERROR_QUEUE_SIZE 17
#define SCPI_IDN1 "GB"
#define SCPI_IDN2 "ETH1SMU2"
#define SCPI_IDN3 "0.01"
#define SCPI_IDN4 "SN000000000001"

#define DEVICE_PORT 2000

#define TX_SCPI_THREAD_MEM_SIZE		1024
#define TX_SCPI_THREAD_INPUT_VAL	0
#define TX_SCPI_THREAD_PRIO			5

extern const scpi_command_t scpi_commands[];
extern scpi_interface_t scpi_interface;
extern char scpi_input_buffer[];
extern scpi_error_t scpi_error_queue_data[];
extern scpi_t scpi_context;

struct _scpi_channel_value_t {
    int32_t row;
    int32_t col;
};
typedef struct _scpi_channel_value_t scpi_channel_value_t;


#define STATE_NONE			0
#define STATE_INIT			1
#define STATE_INIT_ERR		2
#define STATE_LISTEN		3
#define STATE_LISTEN_ERR	4
#define STATE_ACCEPT		5
#define STATE_ACCEPT_ERR	6
#define STATE_RECEIVE		7
#define STATE_RECEIVE_ERR	8
#define STATE_RELISTEN		9

void tx_scpi_server_thread_entry(ULONG thread_input);

size_t SCPI_Write(scpi_t * context, const char * data, size_t len);
int SCPI_Error(scpi_t * context, int_fast16_t err);
scpi_result_t SCPI_Control(scpi_t * context, scpi_ctrl_name_t ctrl, scpi_reg_val_t val);
scpi_result_t SCPI_Reset(scpi_t * context);
scpi_result_t SCPI_Flush(scpi_t * context);


scpi_result_t SCPI_SystemCommTcpipControlQ(scpi_t * context);
size_t SCPI_GetChannels(scpi_t* context, scpi_channel_value_t array[]);


#endif /* __SCPI_DEF_H_ */
