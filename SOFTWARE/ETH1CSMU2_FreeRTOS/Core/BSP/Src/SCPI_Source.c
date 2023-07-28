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
#include "ADS8681.h"
#include "Delay.h"
#include "TCP_Package.h"
#include "AD7980.h"

extern struct bsp_t bsp;
extern uint8_t adc_gain_value[3];
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
	SCPI_ResultFloat(context, bsp.config.curr_range.value);
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
	{"AC",3},
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

scpi_result_t SCPI_SourceFunctionMode(scpi_t* context)
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
	case AC: DG419_Switch(DG419_SIGN_SEL,GPIO_ON); break;
	}


	return SCPI_RES_OK;
}

scpi_result_t SCPI_SourceFunctionModeQ(scpi_t* context)
{
	switch(bsp.config.mode)
	{
		case DC: SCPI_ResultCharacters(context, "DC", 2); break;
		case LIST: SCPI_ResultCharacters(context, "LIST", 3); break;
		case AC: SCPI_ResultCharacters(context, "AC", 4); break;
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

static uint8_t VOLT_GetRangeIndex(float value)
{

	for(uint8_t x = 0; x < 3; x++)
	{
		if((bsp.config.dc.voltage.range[2] >= value) && (bsp.config.dc.voltage.range[1] < value))
		{
			return 2;
		}
		else if((bsp.config.dc.voltage.range[1] >= value) && (bsp.config.dc.voltage.range[0] < value))
		{
			return 1;
		}
		else if((bsp.config.dc.voltage.range[0] >= value))
		{
			return 0;
		}
		else
		{
			return 2;
		}

	}
	return 2;
}



static void DCVOLT_Correction(uint8_t signal, uint8_t index)
{
	float meas[2] = {0.0, 0.0};
	float correction = 0.0, tmp_corr = 0.0;


	if(bsp.config.dc.voltage.correction)
	{
		if(SELECT_ADC2 == bsp.config.measure.adc_type)
		{
			DG419_Switch(DG419_ADC1_SEL, 1);
			TIM_Delay_us(10000);
		}
		TIM_Delay_us(20000);
		ADS8681_VoltageCorrection(meas);


		correction = bsp.config.dc.voltage.value - meas[ADC_VOLTAGE];
		correction += bsp.config.dc.voltage.value;

		(SELECT_ADC1 == bsp.config.measure.adc_type) ? DG419_Switch(DG419_ADC1_SEL, 1) : DG419_Switch(DG419_ADC2_SEL, 1);

		if(SIGN_POS == signal)
		{
			tmp_corr = 12.0f - (correction + bsp.eeprom.structure.calib.dac8565.offset_a[index])*bsp.eeprom.structure.calib.dac8565.vout_a[index];
			tmp_corr = tmp_corr/bsp.config.dc.voltage.gain;

			DAC8565_SetVOUT(VOUTA, 4.0f);
			TIM_Delay_us(4000);
			DAC8565_SetVOUT(VOUTB, tmp_corr);
			bsp.state.calib_mode = MODE_VOLTAGE;
		}
		else if(SIGN_NEG == signal)
		{
			tmp_corr = 12.0f - (fabs(correction) + bsp.eeprom.structure.calib.dac8565.offset_b[index])*bsp.eeprom.structure.calib.dac8565.vout_b[index];
			tmp_corr = tmp_corr/bsp.config.dc.voltage.gain;

			DAC8565_SetVOUT(VOUTA, fabs(tmp_corr));
			TIM_Delay_us(4000);
			DAC8565_SetVOUT(VOUTB, 4.0f);
		}
	}
}

scpi_result_t SCPI_SourceVoltageDCImmediate(scpi_t* context)
{
	scpi_number_t value;
	float tmp_volt;
	uint8_t index;


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
			case SCPI_NUM_MIN: bsp.config.dc.voltage.value = SOURCE_VOLT_DC_MIN_VAL; break;
			case SCPI_NUM_MAX: bsp.config.dc.voltage.value = SOURCE_VOLT_DC_MAX_VAL; break;
			case SCPI_NUM_DEF: bsp.config.dc.voltage.value = SOURCE_VOLT_DC_DEF_VAL; break;
			default: SCPI_ErrorPush(context, SCPI_ERROR_ILLEGAL_PARAMETER_VALUE); return SCPI_RES_ERR;
		}
	}
	else
	{
		if((value.content.value > SOURCE_VOLT_DC_MAX_VAL) || (value.content.value < SOURCE_VOLT_DC_MIN_VAL))
		{
			SCPI_ErrorPush(context, SCPI_ERROR_DATA_OUT_OF_RANGE);
			return SCPI_RES_ERR;
		}

		bsp.config.dc.voltage.value = (float)(value.content.value);

		if((bsp.config.dc.voltage.value <= SOURCE_VOLT_DC_MAX_VAL) && (bsp.config.dc.voltage.value > SOURCE_VOLT_DC_DEF_VAL))
		{
			index = bsp.config.dc.voltage.index = VOLT_GetRangeIndex(fabs(value.content.value));

			tmp_volt = 12.0f - (bsp.config.dc.voltage.value + bsp.eeprom.structure.calib.dac8565.offset_a[index])*bsp.eeprom.structure.calib.dac8565.vout_a[index];
			tmp_volt = tmp_volt/bsp.config.dc.voltage.gain;

			ADS8681_RangeSelect(bsp.config.dc.voltage.value*bsp.config.measure.gain[ADC_VOLTAGE]);

			DAC8565_SetVOUT(VOUTA, 4.0f);
			HAL_Delay(2);
			DAC8565_SetVOUT(VOUTB, tmp_volt);
			bsp.state.calib_mode = MODE_VOLTAGE;
			DCVOLT_Correction(SIGN_POS, index);
		}
		else if((bsp.config.dc.voltage.value >= SOURCE_VOLT_DC_MIN_VAL) && (bsp.config.dc.voltage.value < SOURCE_VOLT_DC_DEF_VAL))
		{
			index = bsp.config.dc.voltage.index = VOLT_GetRangeIndex(fabs(value.content.value));

			tmp_volt = 12.0f - (fabs(bsp.config.dc.voltage.value) + bsp.eeprom.structure.calib.dac8565.offset_b[index])*bsp.eeprom.structure.calib.dac8565.vout_b[index];
			tmp_volt = tmp_volt/bsp.config.dc.voltage.gain;

			ADS8681_RangeSelect(bsp.config.dc.voltage.value*bsp.config.measure.gain[ADC_VOLTAGE]);

			DAC8565_SetVOUT(VOUTA, fabs(tmp_volt));
			HAL_Delay(2);
			DAC8565_SetVOUT(VOUTB, 4.0f);
			bsp.state.calib_mode = MODE_VOLTAGE;
			DCVOLT_Correction(SIGN_NEG, index);
		}
		else if(SOURCE_VOLT_DC_DEF_VAL == bsp.config.dc.voltage.value)
		{

			ADS8681_RangeSelect(bsp.config.dc.voltage.value*bsp.config.measure.gain[ADC_VOLTAGE]);

			if(bsp.eeprom.structure.calib.dac8565.zero_offset >= 0.0)
			{
				DAC8565_SetVOUT(VOUTA, bsp.eeprom.structure.calib.dac8565.zero_offset);
				HAL_Delay(2);
				DAC8565_SetVOUT(VOUTB, SOURCE_VOLT_DC_DEF_VAL);
				bsp.state.calib_mode = MODE_VOLTAGE;
			}
			else
			{
				DAC8565_SetVOUT(VOUTA, SOURCE_VOLT_DC_DEF_VAL);
				HAL_Delay(2);
				DAC8565_SetVOUT(VOUTB, bsp.eeprom.structure.calib.dac8565.zero_offset);
				bsp.state.calib_mode = MODE_VOLTAGE;
			}
		}
	}

	return SCPI_RES_OK;
}


static int8_t CURR_GetRangeIndex(float value)
{
	for(uint8_t x = 0; x < 4; x++)
	{
		if((bsp.config.dc.current.range[3] >= value) && (bsp.config.dc.current.range[2] < value))
		{
			return 3;
		}
		else if((bsp.config.dc.current.range[2] >= value) && (bsp.config.dc.current.range[1] < value))
		{
			return 2;
		}
		else if((bsp.config.dc.current.range[1] >= value) && (bsp.config.dc.current.range[0] < value))
		{
			return 1;
		}
		else if((bsp.config.dc.current.range[0] >= value))
		{
			return 0;
		}
		else
		{
			return 2;
		}

	}
	return 3;
}


static scpi_result_t CURR_SetLimit(scpi_t* context, float* current)
{
	scpi_number_t value;
	float tmp_curr;


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
			case SCPI_NUM_MIN: bsp.config.dc.current.value[CURR_POS] = SOURCE_CURR_DC_MIN_VAL; break;
			case SCPI_NUM_MAX: bsp.config.dc.current.value[CURR_POS] = SOURCE_CURR_DC_MAX_VAL; break;
			case SCPI_NUM_DEF: bsp.config.dc.current.value[CURR_POS] = SOURCE_CURR_DC_DEF_VAL; break;
			default: SCPI_ErrorPush(context, SCPI_ERROR_ILLEGAL_PARAMETER_VALUE); return SCPI_RES_ERR;
		}
	}
	else
	{
		if((value.content.value > SOURCE_CURR_DC_MAX_VAL) || (value.content.value < SOURCE_CURR_DC_MIN_VAL))
		{
			SCPI_ErrorPush(context, SCPI_ERROR_DATA_OUT_OF_RANGE);
			return SCPI_RES_ERR;
		}

		tmp_curr = (float)(value.content.value);

		if((tmp_curr <= SOURCE_CURR_DC_MAX_VAL) && (tmp_curr > 0.0f))
		{
			*current = fabs(tmp_curr);
		}
			return SCPI_RES_OK;
		}

	return SCPI_RES_OK;
}


scpi_result_t SCPI_SourceCurrentDCPositiveImmediate(scpi_t* context)
{
	uint8_t index;
	float tmp_curr;

	if(SCPI_RES_OK ==CURR_SetLimit(context,	&bsp.config.dc.current.value[CURR_POS]))
	{
		index = bsp.config.dc.current.index[CURR_POS] = CURR_GetRangeIndex(bsp.config.dc.current.value[CURR_POS]);

		AQY212_Switch(index);
		HAL_Delay(2);

		tmp_curr = bsp.config.dc.current.value[CURR_POS]*bsp.config.dc.current.gain*bsp.config.dc.current.resistor[index];
		tmp_curr = tmp_curr*bsp.eeprom.structure.calib.dac8565.vout_d[index];

		DAC8565_SetVOUT(VOUTD, tmp_curr);
		HAL_Delay(2);
		bsp.config.dc.current.mode = CURR_POS;
	}

	return SCPI_RES_OK;
}

scpi_result_t SCPI_SourceCurrentDCPositiveImmediateQ(scpi_t * context)
{
	SCPI_ResultFloat(context, bsp.config.dc.current.value[CURR_POS]);
	return SCPI_RES_OK;
}

scpi_result_t SCPI_SourceCurrentDCNegativeImmediate(scpi_t* context)
{
	uint8_t index;
	float tmp_curr;

	if(SCPI_RES_OK ==CURR_SetLimit(context,	&bsp.config.dc.current.value[CURR_NEG]))
		{
			index = bsp.config.dc.current.index[CURR_NEG] = CURR_GetRangeIndex(bsp.config.dc.current.value[CURR_NEG]);

			AQY212_Switch(index);
			HAL_Delay(2);

			tmp_curr = bsp.config.dc.current.value[CURR_NEG]*bsp.config.dc.current.gain*bsp.config.dc.current.resistor[index];
			tmp_curr = tmp_curr*bsp.eeprom.structure.calib.dac8565.vout_c[index];
			DAC8565_SetVOUT(VOUTC, tmp_curr);
			HAL_Delay(2);
			bsp.config.dc.current.mode = CURR_NEG;
		}

	return SCPI_RES_OK;
}

scpi_result_t SCPI_SourceCurrentDCNegativeImmediateQ(scpi_t * context)
{
	SCPI_ResultFloat(context, bsp.config.dc.current.value[CURR_NEG]);
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
scpi_result_t SCPI_SourceVoltageDCImmediateQ(scpi_t* context)
{
	SCPI_ResultFloat(context, bsp.config.dc.voltage.value);
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

static scpi_result_t AC_Frequency(scpi_t * context);
static scpi_result_t AC_Voltage(scpi_t * context);
static scpi_result_t AC_Offset(scpi_t * context);

scpi_result_t SCPI_SourceVoltageACImmediate(scpi_t* context)
{
	float tmp;
	if(SCPI_RES_OK != AC_Frequency(context))
	{
		return SCPI_RES_ERR;
	}
	if(SCPI_RES_OK != AC_Voltage(context))
	{
		return SCPI_RES_ERR;
	}
	if(SCPI_RES_OK != AC_Offset(context))
	{
		return SCPI_RES_ERR;
	}

	tmp = fabs(bsp.config.ac.amplitude) + fabs(bsp.config.ac.offset);

	if(tmp > SOURCE_AC_MAX_VAL)
	{
		SCPI_ErrorPush(context, SCPI_ERROR_DATA_OUT_OF_RANGE);
		return SCPI_RES_ERR;
	}

	FGEN_SetAmplitude(bsp.config.ac.amplitude/bsp.config.ac.amplit_gain);
	FGEN_SetFrequency(bsp.config.ac.frequency);
	FGEN_SetOffset(-1*bsp.config.ac.offset/bsp.config.ac.offset_gain);

	return SCPI_RES_OK;
}

scpi_result_t SCPI_SourceVoltageACAmplitudeImmediate(scpi_t* context)
{
	float tmp;

	if(SCPI_RES_OK != AC_Voltage(context))
	{
		return SCPI_RES_ERR;
	}

	tmp = fabs(bsp.config.ac.amplitude) + fabs(bsp.config.ac.offset);

	if(tmp > SOURCE_AC_MAX_VAL)
	{
		SCPI_ErrorPush(context, SCPI_ERROR_DATA_OUT_OF_RANGE);
		return SCPI_RES_ERR;
	}

	FGEN_SetAmplitude(bsp.config.ac.amplitude/bsp.config.ac.amplit_gain);

	return SCPI_RES_OK;
}

scpi_result_t SCPI_SourceVoltageACFrequencyImmediate(scpi_t* context)
{

	if(SCPI_RES_OK != AC_Frequency(context))
	{
		return SCPI_RES_ERR;
	}

	FGEN_SetFrequency(bsp.config.ac.frequency);

	return SCPI_RES_OK;
}

scpi_result_t SCPI_SourceVoltageACOffsetImmediate(scpi_t* context)
{
	float tmp;

	if(SCPI_RES_OK != AC_Offset(context))
	{
		return SCPI_RES_ERR;
	}

	tmp = fabs(bsp.config.ac.amplitude) + fabs(bsp.config.ac.offset);

	if(tmp > SOURCE_AC_MAX_VAL)
	{
		SCPI_ErrorPush(context, SCPI_ERROR_DATA_OUT_OF_RANGE);
		return SCPI_RES_ERR;
	}

	FGEN_SetOffset(-1*bsp.config.ac.offset/bsp.config.ac.offset_gain);

	return SCPI_RES_OK;
}

static scpi_result_t AC_Frequency(scpi_t * context)
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
		case SCPI_NUM_MIN: bsp.config.ac.frequency = SOURCE_AC_MIN_FREQ; break;
		case SCPI_NUM_MAX: bsp.config.ac.frequency = SOURCE_AC_MAX_FREQ; break;
		case SCPI_NUM_DEF: bsp.config.ac.frequency = SOURCE_AC_DEF_FREQ; break;
		default: SCPI_ErrorPush(context, SCPI_ERROR_ILLEGAL_PARAMETER_VALUE); return SCPI_RES_ERR;
		}
	}
	else
	{
		if(SCPI_UNIT_NONE == freq.unit || SCPI_UNIT_UNITLESS == freq.unit)
		{
			if(freq.content.value < SOURCE_AC_MIN_FREQ || freq.content.value > SOURCE_AC_MAX_FREQ)
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

	bsp.config.ac.frequency = (float)(freq.content.value);

	return SCPI_RES_OK;
}

static scpi_result_t AC_Voltage(scpi_t * context)
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
		case SCPI_NUM_MIN: bsp.config.ac.amplitude = SOURCE_AC_MIN_VAL; break;
		case SCPI_NUM_MAX: bsp.config.ac.amplitude = SOURCE_AC_MAX_VAL; break;
		case SCPI_NUM_DEF: bsp.config.ac.amplitude = SOURCE_AC_DEF_VAL; break;
		default: SCPI_ErrorPush(context, SCPI_ERROR_ILLEGAL_PARAMETER_VALUE); return SCPI_RES_ERR;
		}
	}
	else
	{
		if(SCPI_UNIT_NONE == volt.unit || SCPI_UNIT_UNITLESS == volt.unit)
		{
			if(volt.content.value < SOURCE_AC_MIN_VAL || volt.content.value > SOURCE_AC_MAX_VAL)
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

	bsp.config.ac.amplitude = (float)(fabs(volt.content.value));

	return SCPI_RES_OK;
}

static scpi_result_t AC_Offset(scpi_t * context)
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
		case SCPI_NUM_MIN: bsp.config.ac.offset = SOURCE_AC_MIN_VAL; break;
		case SCPI_NUM_MAX: bsp.config.ac.offset = SOURCE_AC_MAX_VAL; break;
		case SCPI_NUM_DEF: bsp.config.ac.offset = SOURCE_AC_OFFSET_DEF_VAL; break;
		default: SCPI_ErrorPush(context, SCPI_ERROR_ILLEGAL_PARAMETER_VALUE); return SCPI_RES_ERR;
		}
	}
	else
	{
		if(SCPI_UNIT_NONE == offset.unit || SCPI_UNIT_UNITLESS == offset.unit)
		{
			if(offset.content.value < SOURCE_AC_MIN_VAL || offset.content.value > SOURCE_AC_MAX_VAL)
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

	bsp.config.ac.offset = (float)(offset.content.value);

	return SCPI_RES_OK;
}


scpi_result_t SCPI_SourceVoltageACImmediateQ(scpi_t* context)
{

	return SCPI_RES_OK;
}

scpi_result_t SCPI_Output(scpi_t * context)
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

scpi_result_t SCPI_OutputQ(scpi_t * context)
{
	SCPI_ResultArrayUInt8(context, bsp.config.relay.state, MAXROW, SCPI_FORMAT_ASCII);

	return SCPI_RES_OK;
}

scpi_result_t SCPI_SourceVoltageDCCorrection(scpi_t * context)
{
	scpi_bool_t correction = 0;

	if(!SCPI_ParamBool(context, &correction, TRUE))
	{
		return SCPI_RES_ERR;
	}

	bsp.config.dc.voltage.correction = (uint8_t)correction;

	return SCPI_RES_OK;
}

scpi_result_t SCPI_SourceVoltageDCCorrectionQ(scpi_t * context)
{
	SCPI_ResultBool(context, bsp.config.dc.voltage.correction);

	return SCPI_RES_OK;
}

scpi_result_t SCPI_SourceVoltageListLoad(scpi_t * context)
{
	return SCPI_RES_OK;
}

scpi_result_t SCPI_SourceVoltageListLoadQ(scpi_t * context)
{
	uint32_t part = 0, rest = 0;
	uint32_t start = 0;
	part = bsp.config.list.count/MAX_PART_SAMPLES;
	rest = bsp.config.list.count % MAX_PART_SAMPLES;

	for(uint8_t x = 0 ; x < part; x++)
	{
		SCPI_ResultCharacters(context, TCP_Package(bsp.config.list.data, start, MAX_PART_SAMPLES), TCP_PACKGE_SIZE);
		start += MAX_PART_SAMPLES;
	}
	if(rest)
	{
		SCPI_ResultCharacters(context, TCP_Package(bsp.config.list.data, start, rest), TCP_PACKGE_SIZE);
	}

	return SCPI_RES_OK;
}

scpi_result_t SCPI_SourceVoltageListAppend(scpi_t * context)
{
	return SCPI_RES_OK;
}

scpi_result_t SCPI_SourceVoltageListPointsQ(scpi_t * context)
{

	SCPI_ResultUInt32(context, bsp.config.list.count);

	return SCPI_RES_OK;
}

scpi_result_t SCPI_SourceVoltageListStart(scpi_t * context)
{
	scpi_number_t value;

	if(!SCPI_ParamNumber(context, scpi_special_numbers_def, &value, TRUE))
	{
		return SCPI_RES_ERR;
	}

	if(value.special)
	{
		switch(value.content.tag)
		{
			case SCPI_NUM_MIN:
				{
					if(bsp.config.list.start < bsp.config.list.stop)
					{
						bsp.config.list.start = SOURCE_LIST_START_MIN_VAL;
					}
					else
					{
						SCPI_ErrorPush(context, SCPI_ERROR_DATA_OUT_OF_RANGE);
						return SCPI_RES_ERR;
					}
				} break;

			case SCPI_NUM_MAX:
			case SCPI_NUM_DEF:
				{
					if(bsp.config.list.start < bsp.config.list.stop)
					{
						bsp.config.list.start = SOURCE_LIST_START_MAX_VAL;
					}
					else
					{
						SCPI_ErrorPush(context, SCPI_ERROR_DATA_OUT_OF_RANGE);
						return SCPI_RES_ERR;
					}
				} break;

			default: SCPI_ErrorPush(context, SCPI_ERROR_ILLEGAL_PARAMETER_VALUE); return SCPI_RES_ERR;
		}
	}
	else
	{
		if((bsp.config.list.start > SOURCE_LIST_START_MAX_VAL) || (bsp.config.list.start < SOURCE_LIST_STOP_MAX_VAL))
		{
			SCPI_ErrorPush(context, SCPI_ERROR_DATA_OUT_OF_RANGE);
			return SCPI_RES_ERR;
		}

		if(bsp.config.list.start < bsp.config.list.stop)
		{
			bsp.config.list.start = (uint32_t)(value.content.value);
		}
		else
		{
			SCPI_ErrorPush(context, SCPI_ERROR_DATA_OUT_OF_RANGE);
			return SCPI_RES_ERR;
		}
	}

	return SCPI_RES_OK;
}

scpi_result_t SCPI_SourceVoltageListStop(scpi_t * context)
{
	scpi_number_t value;

	if(!SCPI_ParamNumber(context, scpi_special_numbers_def, &value, TRUE))
	{
		return SCPI_RES_ERR;
	}

	if(value.special)
	{
		switch(value.content.tag)
		{
			case SCPI_NUM_MIN:
				{
					if(bsp.config.list.stop > bsp.config.list.start)
					{
						bsp.config.list.stop = SOURCE_LIST_STOP_MIN_VAL;
					}
					else
					{
						SCPI_ErrorPush(context, SCPI_ERROR_DATA_OUT_OF_RANGE);
						return SCPI_RES_ERR;
					}
				} break;

			case SCPI_NUM_MAX:
			case SCPI_NUM_DEF:
				{
					if(bsp.config.list.stop > bsp.config.list.start)
					{
						bsp.config.list.stop = SOURCE_LIST_STOP_MAX_VAL;
					}
					else
					{
						SCPI_ErrorPush(context, SCPI_ERROR_DATA_OUT_OF_RANGE);
						return SCPI_RES_ERR;
					}
				} break;

			default: SCPI_ErrorPush(context, SCPI_ERROR_ILLEGAL_PARAMETER_VALUE); return SCPI_RES_ERR;
		}
	}
	else
	{
		if((bsp.config.list.stop > SOURCE_LIST_STOP_MAX_VAL) || (bsp.config.list.stop < SOURCE_LIST_STOP_MIN_VAL))
		{
			SCPI_ErrorPush(context, SCPI_ERROR_DATA_OUT_OF_RANGE);
			return SCPI_RES_ERR;
		}

		if(bsp.config.list.stop > bsp.config.list.start)
		{
			bsp.config.list.stop = (uint32_t)(value.content.value);
		}
		else
		{
			SCPI_ErrorPush(context, SCPI_ERROR_DATA_OUT_OF_RANGE);
			return SCPI_RES_ERR;
		}
	}

	return SCPI_RES_OK;
}

scpi_result_t SCPI_SourceVoltageListDelay(scpi_t * context)
{
	scpi_number_t value;

	if(!SCPI_ParamNumber(context, scpi_special_numbers_def, &value, TRUE))
	{
		return SCPI_RES_ERR;
	}

	if(value.special)
	{
		switch(value.content.tag)
		{
			case SCPI_NUM_MIN: bsp.config.list.delay = SOURCE_LIST_DELAY_MIN_VAL; break;
			case SCPI_NUM_MAX: bsp.config.list.delay = SOURCE_LIST_DELAY_MAX_VAL; break;
			case SCPI_NUM_DEF: bsp.config.list.delay = SOURCE_LIST_DELAY_DEF_VAL; break;
			default: SCPI_ErrorPush(context, SCPI_ERROR_ILLEGAL_PARAMETER_VALUE); return SCPI_RES_ERR;
		}
	}
	else
	{
		if((bsp.config.list.delay > SOURCE_LIST_DELAY_MAX_VAL) || (bsp.config.list.delay < SOURCE_LIST_DELAY_MIN_VAL))
		{
			SCPI_ErrorPush(context, SCPI_ERROR_DATA_OUT_OF_RANGE);
			return SCPI_RES_ERR;
		}

		bsp.config.list.delay = (uint32_t)(value.content.value);
	}

	return SCPI_RES_OK;
}

scpi_result_t SCPI_SourceVoltageListDelayQ(scpi_t * context)
{
	SCPI_ResultUInt32(context, bsp.config.list.delay);
	return SCPI_RES_OK;
}

scpi_result_t SCPI_SourceVoltageListMeasureEnable(scpi_t * context)
{
	scpi_bool_t enable = 0;

	if(!SCPI_ParamBool(context, &enable, TRUE))
	{
		return SCPI_RES_ERR;
	}

	bsp.config.list.meas_enable = (uint8_t)enable;

	return SCPI_RES_OK;
}

scpi_result_t SCPI_SourceVoltageListMeasureEnableQ(scpi_t * context)
{
	SCPI_ResultBool(context, (scpi_bool_t)bsp.config.list.meas_enable);
	return SCPI_RES_OK;
}


static void SCPI_SetVoltageForList(float value)
{
	float tmp;
	uint8_t index;

	if((value <= SOURCE_VOLT_DC_MAX_VAL) && (value > SOURCE_VOLT_DC_DEF_VAL))
	{
		index = VOLT_GetRangeIndex(fabs(value));

		tmp = 12.0f - (value + bsp.eeprom.structure.calib.dac8565.offset_a[index])*bsp.eeprom.structure.calib.dac8565.vout_a[index];
		tmp = tmp/bsp.config.dc.voltage.gain;

		DAC8565_SetVOUT(VOUTA, 4.0f);
		HAL_Delay(2);
		DAC8565_SetVOUT(VOUTB, tmp);

	}
	else if((value >= SOURCE_VOLT_DC_MIN_VAL) && (value < SOURCE_VOLT_DC_DEF_VAL))
	{
		index = VOLT_GetRangeIndex(fabs(value));

		tmp = 12.0f - (fabs(value) + bsp.eeprom.structure.calib.dac8565.offset_b[index])*bsp.eeprom.structure.calib.dac8565.vout_b[index];
		tmp = tmp/bsp.config.dc.voltage.gain;

		DAC8565_SetVOUT(VOUTA, fabs(tmp));
		HAL_Delay(2);
		DAC8565_SetVOUT(VOUTB, 4.0f);

	}
	else if(SOURCE_VOLT_DC_DEF_VAL == value)
	{

		if(bsp.eeprom.structure.calib.dac8565.zero_offset >= 0.0)
		{
			DAC8565_SetVOUT(VOUTA, bsp.eeprom.structure.calib.dac8565.zero_offset);
			HAL_Delay(2);
			DAC8565_SetVOUT(VOUTB, SOURCE_VOLT_DC_DEF_VAL);
		}
		else
		{
			DAC8565_SetVOUT(VOUTA, SOURCE_VOLT_DC_DEF_VAL);
			HAL_Delay(2);
			DAC8565_SetVOUT(VOUTB, bsp.eeprom.structure.calib.dac8565.zero_offset);
		}
	}

}

scpi_result_t SCPI_SourceVoltageListImmediate(scpi_t * context)
{
	uint32_t index = 0;

	if(LIST != bsp.config.mode)
	{
		SCPI_ErrorPush(context, SCPI_ERROR_SETTINGS_CONFLICT);
		return SCPI_RES_ERR;
	}

	for(uint32_t i = bsp.config.list.start; i < bsp.config.list.stop; i++)
	{
		if(bsp.config.list.count > index)
		{
			SCPI_SetVoltageForList(bsp.config.list.data[i]);
			HAL_Delay(bsp.config.list.delay);

			if(bsp.config.list.meas_enable)
			{
				(SELECT_ADC1 == bsp.config.measure.adc_type) ? ADS8681_MeasureForList(index) : AD7980_MeasureForList(index);
			}
		}
		else
		{
			break;
		}

		index++;
	}

	return SCPI_RES_OK;
}
