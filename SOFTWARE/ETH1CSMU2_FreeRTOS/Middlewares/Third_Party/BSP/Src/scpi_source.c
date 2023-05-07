/*
 * scpi_source.c
 *
 *  Created on: Mar 19, 2023
 *      Author: grzegorz
 */

#include "scpi_source.h"
#include "GPIO.h"
#include "scpi_def.h"

extern struct _bsp bsp;

/*
 * [SOURce]:CURRent:RANGe <range>
 *
 * @INFO:
 * Sets the current or voltage output range of the specified source channel. This
 * command is effective when the automatic ranging function is off.
 *
 * @PARAMETERS:
 *
 * @NOTE:
 *
 */

scpi_result_t SCPI_SourceCurrentRange(scpi_t* context)
{
	return SCPI_RES_OK;
}

/*
 * SOURce:CURRent:RANGe?
 *
 * @INFO:
 *
 * @PARAMETERS:
 *
 * @NOTE:
 *
 */

scpi_result_t SCPI_SourceCurrentRangeQ(scpi_t* context)
{
	return SCPI_RES_OK;
}

/*
 * SOURce:CURRent:RANGe:AUTO <0|OFF|1|ON>
 *
 * @INFO:
 * Enables or disables the automatic ranging function.
 *
 * @PARAMETERS:
 *
 * @NOTE:
 *
 */

scpi_result_t SCPI_SourceCurrentRangeAuto(scpi_t* context)
{
	return SCPI_RES_OK;
}

scpi_result_t SCPI_SourceFunctionMode(scpi_t* context)
{
	return SCPI_RES_OK;
}

scpi_result_t SCPI_SourceFunctionModeQ(scpi_t* context)
{
	return SCPI_RES_OK;
}


scpi_result_t SCPI_SourceRelayOutput(scpi_t * context)
{
	scpi_channel_value_t array[MAXCOL*MAXROW] = {0};
	size_t channel_size = 0;
	uint8_t index = 0;
	scpi_bool_t state = 0;

	channel_size = SCPI_GetChannels(context, array);

	if(!channel_size || (channel_size > MAXROW))
	{
		SCPI_ErrorPush(context, SCPI_ERROR_DATA_OUT_OF_RANGE);
		return SCPI_RES_ERR;
	}

	if(!SCPI_ParamBool(context, &state, TRUE))
	{
		return SCPI_RES_ERR;
	}

	for(uint8_t i = 0; i < channel_size; i++)
	{
		index = array[i].row;
		CXN_Relays_Control(index, state);
		bsp.config.relay.state[index] = (uint8_t)state;
	}

	return SCPI_RES_OK;
}

scpi_result_t SCPI_SourceRelayOutputQ(scpi_t * context)
{
	SCPI_ResultArrayUInt8(context, bsp.config.relay.state, MAXROW, SCPI_FORMAT_NORMAL);
	return SCPI_RES_OK;
}
