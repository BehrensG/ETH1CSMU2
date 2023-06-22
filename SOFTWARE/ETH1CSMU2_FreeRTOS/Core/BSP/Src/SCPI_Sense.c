/*
 * scpi_sense.c
 *
 *  Created on: Mar 19, 2023
 *      Author: grzegorz
 */

#include "SCPI_Sense.h"
#include "BSP.h"
#include "GPIO.h"

extern scpi_choice_def_t scpi_boolean_select[];
extern struct bsp_t bsp;

uint8_t adc_gain_value[3] = {100,10,1};

static uint8_t CHECK_GainValue(uint8_t gain)
{
	for(uint8_t x = 0; x < 3; x++)
	{
		if(gain == adc_gain_value[x])
		{
			return 0;
		}
	}
	return 1;
}

scpi_result_t SCPI_SenseFunctionOn(scpi_t* context)
{
	int32_t state = 0;

	if(!SCPI_ParamChoice(context, scpi_boolean_select, &state, TRUE))
	{
		return SCPI_RES_ERR;
	}

	bsp.config.measure.enable = (uint8_t)(state);

	return SCPI_RES_OK;
}

scpi_result_t SCPI_SenseFunctionOnQ(scpi_t* context)
{
	SCPI_ResultUInt8(context, bsp.config.measure.enable);
	return SCPI_RES_OK;
}

scpi_result_t SCPI_SenseSelectADC(scpi_t* context)
{
	uint32_t adc_type;
	if(!SCPI_ParamUInt32(context, &adc_type, TRUE))
	{
		return SCPI_RES_ERR;
	}

	if((SELECT_ADC1 != adc_type) && (SELECT_ADC2 != adc_type))
	{
		SCPI_ErrorPush(context, SCPI_ERROR_ILLEGAL_PARAMETER_VALUE);
		return SCPI_RES_ERR;
	}

	bsp.config.measure.adc_type = adc_type;
	if(SELECT_ADC1 == adc_type)
	{
		DG419_Switch(DG419_ADC1_SEL, 1);
	}
	else
	{
		DG419_Switch(DG419_ADC2_SEL, 1);
	}


	return SCPI_RES_OK;
}

scpi_result_t SCPI_SenseSelectADCQ(scpi_t* context)
{
	SCPI_ResultUInt8(context, bsp.config.measure.adc_type);
	return SCPI_RES_OK;
}

scpi_result_t SCPI_SenseCount(scpi_t* context)
{
	uint32_t count;

	if(!SCPI_ParamUInt32(context, &count, TRUE))
	{
		return SCPI_RES_ERR;
	}

	if((count > ADC_SAMPLE_SIZE) || (0 == count))
	{
		SCPI_ErrorPush(context, SCPI_ERROR_DATA_OUT_OF_RANGE);
		return SCPI_RES_ERR;
	}

	bsp.config.measure.count = count;
	return SCPI_RES_OK;
}

scpi_result_t SCPI_SenseCountQ(scpi_t* context)
{
	SCPI_ResultUInt32(context, bsp.config.measure.count);
	return SCPI_RES_OK;
}

static uint8_t GAIN_GetIndex(uint32_t value)
{
	uint8_t gain[3] = {1, 10, 100};

	for(uint8_t x = 0; x < 2; x++)
	{
		if(gain[x] == value)
		{
			return x;
		}
	}

	return 0;
}

scpi_result_t SCPI_SenseVoltageGain(scpi_t* context)
{
	uint32_t gain;

	if(SCPI_ParamUInt32(context, &gain, TRUE))
	{
		return SCPI_RES_ERR;
	}

	if(CHECK_GainValue(gain))
	{
		SCPI_ErrorPush(context, SCPI_ERROR_ILLEGAL_PARAMETER_VALUE);
		return SCPI_RES_ERR;
	}

	bsp.config.measure.gain[ADC_VOLTAGE] = gain;
	bsp.config.measure.gain_index[ADC_VOLTAGE] = GAIN_GetIndex(gain);
	DG444_Switch(DG444_GAIN_VOLT, gain);

	return SCPI_RES_OK;
}

scpi_result_t SCPI_SenseVoltageGainQ(scpi_t* context)
{
	SCPI_ResultUInt8(context, bsp.config.measure.gain[ADC_VOLTAGE]);
	return SCPI_RES_OK;
}

scpi_result_t SCPI_SenseCurrentGain(scpi_t* context)
{
	uint32_t gain;

	if(SCPI_ParamUInt32(context, &gain, TRUE))
	{
		return SCPI_RES_ERR;
	}

	if(CHECK_GainValue(gain))
	{
		SCPI_ErrorPush(context, SCPI_ERROR_ILLEGAL_PARAMETER_VALUE);
		return SCPI_RES_ERR;
	}

	bsp.config.measure.gain[ADC_CURRENT] = gain;
	bsp.config.measure.gain_index[ADC_CURRENT] = GAIN_GetIndex(gain);
	DG444_Switch(DG444_GAIN_CURR, gain);

	return SCPI_RES_OK;
}
scpi_result_t SCPI_SenseCurrentGainQ(scpi_t* context)
{
	SCPI_ResultUInt8(context, bsp.config.measure.gain[ADC_CURRENT]);
	return SCPI_RES_OK;
}


scpi_result_t SCPI_SenseMeasureDelay(scpi_t* context)
{

	uint32_t delay;

	if(SCPI_ParamUInt32(context, &delay, TRUE))
	{
		return SCPI_RES_ERR;
	}

	bsp.config.measure.delay = delay;

	return SCPI_RES_OK;
}

scpi_result_t SCPI_SenseMeasureDelayQ(scpi_t* context)
{
	SCPI_ResultUInt32(context, bsp.config.measure.delay);
	return SCPI_RES_OK;
}

scpi_result_t SCPI_SenseVoltageListMeasureQ(scpi_t* context)
{
	return SCPI_RES_OK;
}
