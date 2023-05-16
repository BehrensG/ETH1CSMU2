/*
 * scpi_source.c
 *
 *  Created on: Mar 19, 2023
 *      Author: grzegorz
 */

#include <math.h>

#include "SCPI_Def.h"
#include "SCPI_Source.h"
#include "GPIO.h"
#include "DAC8565.h"
#include "FGEN.h"

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

scpi_choice_def_t function_select[] =
{
    {"DC", 1},
    {"LIST", 2},
	{"SINE",3},
    SCPI_CHOICE_LIST_END
};


/*
 * SOURce:VOLTage:MODE <mode>
 *
 * @INFO:
 * Select the output signal. Possible mode values are: DC, ARBitrary and SINE.
 *
 * @PARAMETERS:
 * 				mode		DC - Select DC mode.
 * 							LIST - Select LIST mode.
 * 							SINE - Select SINE mode.
 *
 * @NOTE:
 * The selection of the source mode will have a influence on the parameters of [SOURce:]FUNCtion[:SHAPe].
 */

scpi_result_t SCPI_SourceVoltageMode(scpi_t* context)
{
	int32_t select = 0;

	if(!SCPI_ParamChoice(context, function_select, &select, FALSE))
	{
		return SCPI_RES_ERR;
	}

	bsp.config.mode = select;

	switch(select)
	{
	case DC: DG419_Switch(DG419_SIGN_SEL,GPIO_OFF); break;
	case LIST: DG419_Switch(DG419_SIGN_SEL,GPIO_OFF); break;
	case SINE: DG419_Switch(DG419_SIGN_SEL,GPIO_ON); break;
	}


	return SCPI_RES_OK;
}

scpi_result_t SCPI_SourceVoltageModeQ(scpi_t* context)
{
	switch(bsp.config.mode)
	{
		case DC: SCPI_ResultCharacters(context, "DC", 2); break;
		case LIST: SCPI_ResultCharacters(context, "LIST", 3); break;
		case SINE: SCPI_ResultCharacters(context, "SINE", 4); break;
	}
	return SCPI_RES_OK;
}

/*
 * SOURce:VOLTage:DC[:IMMediate] <dc_value>
 *
 * @INFO:
 * Set the output shape, according to the selected function mode.
 *
 * @PARAMETERS:
 * 				<dc_voltage> - 	set the DC voltage, between -12.0 to 12.0 volts.
 *								MINimum - -12.0 voltage
 *								MAXimum - 12.0 voltage
 *								DEFault - 0.0 voltage
 *
 * @NOTE:
 *
 */

scpi_result_t SCPI_SourceVoltageLevelDCImmediate(scpi_t* context)
{
	scpi_number_t value;
	float tmp_volt;

	if(DC != bsp.config.mode)
	{
		SCPI_ErrorPush(context, SCPI_ERROR_SETTINGS_CONFLICT);
		return SCPI_RES_ERR;
	}
	if(!SCPI_ParamNumber(context, scpi_special_numbers_def, &value, TRUE))
	{
		return SCPI_RES_ERR;
	}

	if(value.special)
	{
		switch(value.content.tag)
		{
			case SCPI_NUM_MIN: bsp.config.dc.value = SOURCE_DC_MIN_VAL; break;
			case SCPI_NUM_MAX: bsp.config.dc.value = SOURCE_DC_MAX_VAL; break;
			case SCPI_NUM_DEF: bsp.config.dc.value = SOURCE_DC_DEF_VAL; break;
			default: SCPI_ErrorPush(context, SCPI_ERROR_ILLEGAL_PARAMETER_VALUE); return SCPI_RES_ERR;
		}
	}
	else
	{
		if((value.content.value > SOURCE_DC_MAX_VAL) || (value.content.value < SOURCE_DC_MIN_VAL))
		{
			SCPI_ErrorPush(context, SCPI_ERROR_DATA_OUT_OF_RANGE);
			return SCPI_RES_ERR;
		}

		bsp.config.dc.value = (float)(value.content.value);

		if((bsp.config.dc.value <= SOURCE_DC_MAX_VAL) && (bsp.config.dc.value > SOURCE_DC_DEF_VAL))
		{
			tmp_volt = (float)(bsp.config.dc.value/bsp.config.dc.gain);

			DAC8565_SetVOUT(VOUTA, fabs(tmp_volt));
			DAC8565_SetVOUT(VOUTB, SOURCE_DC_DEF_VAL);
		}
		else if((bsp.config.dc.value >= SOURCE_DC_MIN_VAL) && (bsp.config.dc.value < SOURCE_DC_DEF_VAL))
		{
			tmp_volt = (float)(bsp.config.dc.value/bsp.config.dc.gain);

			DAC8565_SetVOUT(VOUTA, SOURCE_DC_DEF_VAL);
			DAC8565_SetVOUT(VOUTB, fabs(tmp_volt));
		}
		else if(SOURCE_DC_DEF_VAL == bsp.config.dc.value)
		{
			DAC8565_SetVOUT(VOUTA, SOURCE_DC_DEF_VAL);
			DAC8565_SetVOUT(VOUTB, SOURCE_DC_DEF_VAL);
		}
	}

	return SCPI_RES_OK;
}

/*
 * SOURce:VOLTage:DC[:IMMediate] <dc_value>
 *
 * @INFO:
 * Set the output shape, according to the selected function mode.
 *
 * @PARAMETERS:
 * 				<dc_voltage> - 	set the DC voltage, between -12.0 to 12.0 volts.
 *								MINimum - -12.0 voltage
 *								MAXimum - 12.0 voltage
 *								DEFault - 0.0 voltage
 *
 * @NOTE:
 *
 */
scpi_result_t SCPI_SourceVoltageLevelDCImmediateQ(scpi_t* context)
{
	SCPI_ResultFloat(context, bsp.config.dc.value);
	return SCPI_RES_OK;
}


/*
 * SOURce:VOLTage:FGEN frequency,amplitude,offset
 *
 * @INFO:
 *
 * @PARAMETERS:
 *
 * @NOTE:
 *
 */

static scpi_result_t SINE_Frequency(scpi_t * context);
static scpi_result_t SINE_Voltage(scpi_t * context);
static scpi_result_t SINE_Offset(scpi_t * context);

scpi_result_t SCPI_SourceVoltageFgenImmediate(scpi_t* context)
{
	BSP_StatusTypeDef ret;
	float tmp;
	if(SCPI_RES_OK != SINE_Frequency(context))
	{
		return SCPI_RES_ERR;
	}
	if(SCPI_RES_OK != SINE_Voltage(context))
	{
		return SCPI_RES_ERR;
	}
	if(SCPI_RES_OK != SINE_Offset(context))
	{
		return SCPI_RES_ERR;
	}

	tmp = fabs(bsp.config.fgen.amplitude) + fabs(bsp.config.fgen.offset);

	if(tmp > SOURCE_SINE_MAX_VAL)
	{
		SCPI_ErrorPush(context, SCPI_ERROR_DATA_OUT_OF_RANGE);
		return SCPI_RES_ERR;
	}

	ret = FGEN_SetAmplitude(bsp.config.fgen.amplitude);
	ret = FGEN_SetFrequency(bsp.config.fgen.frequency);
	ret = FGEN_SetOffset(bsp.config.fgen.offset);

	return SCPI_RES_OK;
}

static scpi_result_t SINE_Frequency(scpi_t * context)
{
	scpi_number_t freq;

	if(!SCPI_ParamNumber(context, scpi_special_numbers_def, &freq, TRUE))
	{
		return SCPI_RES_ERR;
	}

	if(freq.special)
	{
		switch(freq.content.tag)
		{
		case SCPI_NUM_MIN: bsp.config.fgen.frequency = SOURCE_FGEN_MIN_FREQ; break;
		case SCPI_NUM_MAX: bsp.config.fgen.frequency = SOURCE_FGEN_MAX_FREQ; break;
		case SCPI_NUM_DEF: bsp.config.fgen.frequency = SOURCE_FGEN_DEF_FREQ; break;
		default: SCPI_ErrorPush(context, SCPI_ERROR_ILLEGAL_PARAMETER_VALUE); return SCPI_RES_ERR;
		}
	}
	else
	{
		if(SCPI_UNIT_NONE == freq.unit || SCPI_UNIT_UNITLESS == freq.unit)
		{
			if(freq.content.value < SOURCE_FGEN_MIN_FREQ || freq.content.value > SOURCE_FGEN_MAX_FREQ)
			{
				SCPI_ErrorPush(context, SCPI_ERROR_DATA_OUT_OF_RANGE);
				return SCPI_RES_ERR;
			}
			else
			{

			}
		}
		else if(SCPI_UNIT_HERTZ == freq.unit)
		{

		}
		else
		{
			SCPI_ErrorPush(context, SCPI_ERROR_INVALID_SUFFIX);
			return SCPI_RES_ERR;
		}
	}

	bsp.config.fgen.frequency = (float)(freq.content.value);

	return SCPI_RES_OK;
}

static scpi_result_t SINE_Voltage(scpi_t * context)
{
	scpi_number_t volt;

	if(!SCPI_ParamNumber(context, scpi_special_numbers_def, &volt, TRUE))
	{
		return SCPI_RES_ERR;
	}

	if(volt.special)
	{
		switch(volt.content.tag)
		{
		case SCPI_NUM_MIN: bsp.config.fgen.amplitude = SOURCE_SINE_MIN_VAL; break;
		case SCPI_NUM_MAX: bsp.config.fgen.amplitude = SOURCE_SINE_MAX_VAL; break;
		case SCPI_NUM_DEF: bsp.config.fgen.amplitude = SOURCE_SINE_DEF_VAL; break;
		default: SCPI_ErrorPush(context, SCPI_ERROR_ILLEGAL_PARAMETER_VALUE); return SCPI_RES_ERR;
		}
	}
	else
	{
		if(SCPI_UNIT_NONE == volt.unit || SCPI_UNIT_UNITLESS == volt.unit)
		{
			if(volt.content.value < SOURCE_SINE_MIN_VAL || volt.content.value > SOURCE_SINE_MAX_VAL)
			{
				SCPI_ErrorPush(context, SCPI_ERROR_DATA_OUT_OF_RANGE);
				return SCPI_RES_ERR;
			}
			else
			{

			}
		}
		else if (SCPI_UNIT_VOLT == volt.unit)
		{

		}
		else
		{
			SCPI_ErrorPush(context, SCPI_ERROR_INVALID_SUFFIX);
			return SCPI_RES_ERR;
		}

	}

	bsp.config.fgen.amplitude = (float)(fabs(volt.content.value));

	return SCPI_RES_OK;
}

static scpi_result_t SINE_Offset(scpi_t * context)
{
	scpi_number_t offset;

	if(!SCPI_ParamNumber(context, scpi_special_numbers_def, &offset, TRUE))
	{
		return SCPI_RES_ERR;
	}

	if(offset.special)
	{
		switch(offset.content.tag)
		{
		case SCPI_NUM_MIN: bsp.config.fgen.offset = SOURCE_SINE_MIN_VAL; break;
		case SCPI_NUM_MAX: bsp.config.fgen.offset = SOURCE_SINE_MAX_VAL; break;
		case SCPI_NUM_DEF: bsp.config.fgen.offset = SOURCE_SINE_OFFSET_DEF_VAL; break;
		default: SCPI_ErrorPush(context, SCPI_ERROR_ILLEGAL_PARAMETER_VALUE); return SCPI_RES_ERR;
		}
	}
	else
	{
		if(SCPI_UNIT_NONE == offset.unit || SCPI_UNIT_UNITLESS == offset.unit)
		{
			if(offset.content.value < SOURCE_SINE_MIN_VAL || offset.content.value > SOURCE_SINE_MAX_VAL)
			{
				SCPI_ErrorPush(context, SCPI_ERROR_DATA_OUT_OF_RANGE);
				return SCPI_RES_ERR;
			}
			else
			{

			}
		}
		else if (SCPI_UNIT_VOLT == offset.unit)
		{

		}
		else
		{
			SCPI_ErrorPush(context, SCPI_ERROR_INVALID_SUFFIX);
			return SCPI_RES_ERR;
		}

	}

	bsp.config.fgen.offset = (float)(offset.content.value);

	return SCPI_RES_OK;
}


scpi_result_t SCPI_SourceVoltageFgenImmediateQ(scpi_t* context)
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
	SCPI_ResultArrayUInt8(context, bsp.config.relay.state, MAXROW, SCPI_FORMAT_ASCII);

	return SCPI_RES_OK;
}

scpi_result_t SCPI_SourceVoltageListLoad(scpi_t * context)
{
	return SCPI_RES_OK;
}

scpi_result_t SCPI_SourceVoltageListLoadQ(scpi_t * context)
{
	return SCPI_RES_OK;
}

scpi_result_t SCPI_SourceVoltageListAppend(scpi_t * context)
{
	return SCPI_RES_OK;
}

scpi_result_t SCPI_SourceVoltageListPointsQ(scpi_t * context)
{
	return SCPI_RES_OK;
}

scpi_result_t SCPI_SourceVoltageListStart(scpi_t * context)
{
	return SCPI_RES_OK;
}

scpi_result_t SCPI_SourceVoltageListStop(scpi_t * context)
{
	return SCPI_RES_OK;
}

scpi_result_t SCPI_SourceVoltageListDelay(scpi_t * context)
{
	return SCPI_RES_OK;
}
