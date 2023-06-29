/*
 * scpi_trigger.c
 *
 *  Created on: Mar 17, 2023
 *      Author: grzegorz
 */


#include <Delay.h>
#include <stdio.h>
#include "SCPI_Trigger.h"


extern scpi_choice_def_t boolean_select[];
extern struct bsp_t bsp;
extern osThreadId_t TriggerTaskHandle;

 scpi_choice_def_t trigger_source_select[] =
 {
 		{"IMMediate", 1},
 		{"EXTernal", 2},
 		{"BUS", 3},
		{"OUTput", 4},
 		SCPI_CHOICE_LIST_END
 };

 scpi_choice_def_t trigger_slope_select[] =
 {
		 {"POSitive", 1},
		 {"NEGative", 2},
		 SCPI_CHOICE_LIST_END
 };


 scpi_result_t SCPI_InitiateImmediate(scpi_t* context)
 {

	if((DC == bsp.config.mode) || (AC == bsp.config.mode))
	{
		if(SELECT_ADC1 == bsp.config.measure.adc_type)
		{
			ADS8681_ReadData(bsp.config.measure.count);
		}
		else if(SELECT_ADC2 == bsp.config.measure.adc_type)
		{
			AD7980_ReadData(bsp.config.measure.count);
		}
		else
		{
			return SCPI_RES_ERR;
		}
	}

	return SCPI_RES_OK;
 }

 /*
  * TRIGger:DELay <numeric_value>
  *
  * @INFO:
  * Sets the trigger delay time.
  *
  * @PARAMETERS:
  * 				<numeric_value> :
  *									numeric from 0 to 1000000 (us)
  *									MINimum 0 (us)
  *									MAXimum 1000000 (us)
  *
  * @NOTE:
  * Min. resolution is 1ms.
  */

scpi_result_t SCPI_TriggerDelay(scpi_t* context)
{
	scpi_number_t param_delay;

	if(!SCPI_ParamNumber(context, scpi_special_numbers_def, &param_delay, TRUE))
	{
		return SCPI_RES_ERR;
	}

	if(param_delay.special)
	{
		switch(param_delay.content.tag)
		{
		case SCPI_NUM_MIN: bsp.trigger.delay = 0; break;
		case SCPI_NUM_MAX: bsp.trigger.delay = 1000000; break;
		case SCPI_NUM_DEF: bsp.trigger.delay = 0; break;
		default: SCPI_ErrorPush(context, SCPI_ERROR_ILLEGAL_PARAMETER_VALUE); return SCPI_RES_ERR;
		}
	}
	else
	{
		if(SCPI_UNIT_NONE == param_delay.unit || SCPI_UNIT_UNITLESS == param_delay.unit)
		{
			if(param_delay.content.value < 0 || param_delay.content.value > 1000000)
			{
				SCPI_ErrorPush(context, SCPI_ERROR_DATA_OUT_OF_RANGE);
				return SCPI_RES_ERR;
			}
			else
			{
				bsp.trigger.delay = param_delay.content.value;
				return SCPI_RES_OK;
			}
		}
		else
		{
			SCPI_ErrorPush(context, SCPI_ERROR_INVALID_SUFFIX);
			return SCPI_RES_ERR;
		}
	}

	return SCPI_RES_OK;
}

/*
 * TRIGger:DELay?
 *
 * @INFO:
 * Query the trigger delay time. Response is a numeric value.
 *
 */

scpi_result_t SCPI_TriggerDelayQ(scpi_t* context)
{
	SCPI_ResultUInt32(context, bsp.trigger.delay);
	return SCPI_RES_OK;
}

/*
 * TRIGger[:IMMediate]
 *
 * @INFO:
 * Causes the trigger to execute a measurement, regardless of the trigger state.
 *
 */

scpi_result_t SCPI_TriggerImmediate(scpi_t* context)
{

	if(TRIG_OUT != bsp.trigger.source)
	{
		LL_GPIO_TogglePin(TRIG_OUT_GPIO_Port, TRIG_OUT_Pin);
		DWT_Delay_us(bsp.trigger.delay);
		LL_GPIO_TogglePin(TRIG_OUT_GPIO_Port, TRIG_OUT_Pin);


	}
	else
	{
		SCPI_ErrorPush(context, SCPI_ERROR_TRIGGER_IGNORED);
		return SCPI_RES_ERR;
	}

	return SCPI_RES_OK;
}

/*
 * TRIGger:SOURce {IMMediate|EXTernal|BUS|OUTput}
 *
 * @INFO:
 * Sets the trigger mode.
 *
 * @PARAMETERS:
 * 				BUS :		BUS trigger mode
 * 				EXTernal :	external trigger mode
 * 				INTernal :	internal trigger mode
 * 				OUTput :	the board outputs a trigger pulse
 *
 */

scpi_result_t SCPI_TriggerSource(scpi_t* context)
{
	int32_t paramTRIG;

	if(!SCPI_ParamChoice(context, trigger_source_select, &paramTRIG, TRUE))
	{
		return SCPI_RES_ERR;
	}

	bsp.trigger.source = paramTRIG;

	if(TRIG_OUT == paramTRIG)
	{
		LL_GPIO_ResetOutputPin(TRIG_EN_GPIO_Port, TRIG_EN_Pin);
		osThreadSuspend(TriggerTaskHandle);
	}
	else
	{
		LL_GPIO_SetOutputPin(TRIG_EN_GPIO_Port, TRIG_EN_Pin);
		osThreadResume(TriggerTaskHandle);
	}

	return SCPI_RES_OK;
}

/*
 * TRIGger:SOURce?
 *
 * @INFO:
 * Query the trigger mode. Response is BUS, EXT, IMM or OUT.
 *
 */

scpi_result_t SCPI_TriggerSourceQ(scpi_t* context)
{

	switch(bsp.trigger.source)
	{
		case TRIG_BUS: SCPI_ResultCharacters(context, "BUS", 3); break;
		case TRIG_EXT: SCPI_ResultCharacters(context, "EXT", 3); break;
		case TRIG_IMM: SCPI_ResultCharacters(context, "IMM", 3); break;
		case TRIG_OUT: SCPI_ResultCharacters(context, "OUT", 3); break;
	}
	return SCPI_RES_OK;
}

/*
 * TRIGger:OUTput
 *
 * @INFO:
 * Output a TTL-compatible square pulse with the specified edge (TRIG:OUTP:SLOP command) is to output. The trigger pulse time is 5ms.
 *
 *
 */

scpi_result_t SCPI_TriggerOutput(scpi_t* context)
{

	if(TRIG_OUT != bsp.trigger.source)
	{
		SCPI_ErrorPush(context, SCPI_ERROR_TRIGGER_IGNORED);
		return SCPI_RES_ERR;
	}

	LL_GPIO_TogglePin(TRIG_OUT_GPIO_Port, TRIG_OUT_Pin);
	DWT_Delay_us(bsp.trigger.delay);
	LL_GPIO_TogglePin(TRIG_OUT_GPIO_Port, TRIG_OUT_Pin);

	return SCPI_RES_OK;
}

/*
 * TRIGger:SLOPe {POSitive|NEGative}
 *
 * @INFO:
 * Select a rising or falling edge for the “trigger out” signal.
 *
 * @PARAMETERS:
 * 				POSitive :	rising edge
 * 				NEGative :	falling edge
 *
 */

scpi_result_t SCPI_TriggerSlope(scpi_t* context)
{
	int32_t paramSLOPE;
	//GPIO_InitTypeDef GPIO_InitStruct = {0};

	if(!SCPI_ParamChoice(context, trigger_slope_select, &paramSLOPE, TRUE))
	{
		return SCPI_RES_ERR;
	}


/*
	HAL_GPIO_DeInit(TRIG_IN_GPIO_Port, TRIG_IN_Pin);
	GPIO_InitStruct.Pin = TRIG_IN_Pin;

	switch(paramSLOPE)
	{
		case SLOPE_POS: GPIO_InitStruct.Mode = GPIO_MODE_IT_RISING; break;
		case SLOPE_NEG: GPIO_InitStruct.Mode = GPIO_MODE_IT_FALLING; break;
	}

	GPIO_InitStruct.Pull = GPIO_NOPULL;
	LL_GPIO_Init(TRIG_IN_GPIO_Port, &GPIO_InitStruct);
*/
	bsp.trigger.in_slope = paramSLOPE;

	return SCPI_RES_OK;
}

/*
 * TRIGger:SLOPe?
 *
 * @INFO:
 * Query trigger input slope edge. Returns POS or NEG.
 *
 */

scpi_result_t SCPI_TriggerSlopeQ(scpi_t* context)
{

	switch(bsp.trigger.in_slope)
	{
		case SLOPE_POS: SCPI_ResultCharacters(context, "POS", 3); break;
		case SLOPE_NEG: SCPI_ResultCharacters(context, "NEG", 3); break;
	}

	return SCPI_RES_OK;
}

/*
 * TRIGger:OUTput:SLOPe {POSitive|NEGative}
 *
 * @INFO:
 * Select a rising or falling edge for the “trigger out” signal.
 *
 * @PARAMETERS:
 * 				POSitive :	rising edge
 * 				NEGative :	falling edge
 *
 */

scpi_result_t SCPI_TriggerOutputSlope(scpi_t* context)
{
	int32_t paramSLOPE;

	if(!SCPI_ParamChoice(context, trigger_slope_select, &paramSLOPE, TRUE))
	{
		return SCPI_RES_ERR;
	}

	switch(paramSLOPE)
	{
		case SLOPE_POS: LL_GPIO_ResetOutputPin(TRIG_OUT_GPIO_Port, TRIG_OUT_Pin); break;
		case SLOPE_NEG: LL_GPIO_SetOutputPin(TRIG_OUT_GPIO_Port, TRIG_OUT_Pin); break;
	}

	bsp.trigger.out_slope = paramSLOPE;

	return SCPI_RES_OK;
}

/*
 * TRIGger:OUTput:SLOPe?
 *
 * @INFO:
 * Query trigger output slope edge. Returns POS or NEG.
 *
 */

scpi_result_t SCPI_TriggerOutputSlopeQ(scpi_t* context)
{

	switch(bsp.trigger.out_slope)
	{
		case SLOPE_POS: SCPI_ResultCharacters(context, "POS", 3); break;
		case SLOPE_NEG: SCPI_ResultCharacters(context, "NEG", 3); break;
	}

	return SCPI_RES_OK;
}

/*
 * *TRG
 *
 * @INFO:
 * This command triggers the device if the trigger source is set to Bus.
 *
 */

scpi_result_t SCPI_TRG(scpi_t* context)
{

	if(TRIG_BUS != bsp.trigger.source)
	{
		SCPI_ErrorPush(context, SCPI_ERROR_TRIGGER_IGNORED);
		return SCPI_RES_ERR;
	}

	return SCPI_RES_OK;
}
