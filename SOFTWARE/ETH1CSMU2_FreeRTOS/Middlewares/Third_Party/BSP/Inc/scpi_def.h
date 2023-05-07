#ifndef __SCPI_DEF_H_
#define __SCPI_DEF_H_

#include "scpi/scpi.h"

#define SCPI_INPUT_BUFFER_LENGTH 512
#define SCPI_ERROR_QUEUE_SIZE 17
#define SCPI_IDN1 "GB"
#define SCPI_IDN2 "ETH1SMU2"
#define SCPI_IDN3 "0.01"
#define SCPI_IDN4 "SN000000000001"

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


size_t SCPI_Write(scpi_t * context, const char * data, size_t len);
int SCPI_Error(scpi_t * context, int_fast16_t err);
scpi_result_t SCPI_Control(scpi_t * context, scpi_ctrl_name_t ctrl, scpi_reg_val_t val);
scpi_result_t SCPI_Reset(scpi_t * context);
scpi_result_t SCPI_Flush(scpi_t * context);

void scpi_server_init(void);
scpi_result_t SCPI_SystemCommTcpipControlQ(scpi_t * context);
size_t SCPI_GetChannels(scpi_t* context, scpi_channel_value_t array[]);

void resistor_curr_gain_set();
void resistor_volt_gain_set();

#endif /* __SCPI_DEF_H_ */
