/*
 * FGEN.c
 *
 *  Created on: Mar 11, 2023
 *      Author: grzegorz
 */

#include <math.h>

#include "FGEN.h"
#include "AD9834.h"
#include "74HC595.h"
#include "AD5322.h"


extern struct _bsp bsp;

void FGEN_ClockDivider(dds_clk_div_e clk_div)
{
	switch(clk_div)
	{
		case FGEN_DIV0:
			{
				LL_GPIO_SetOutputPin(FGEN_DIV2_GPIO_Port, FGEN_DIV2_Pin);
				LL_GPIO_SetOutputPin(FGEN_DIV4_GPIO_Port, FGEN_DIV4_Pin);
				LL_GPIO_SetOutputPin(FGEN_DIV8_GPIO_Port, FGEN_DIV8_Pin);
				LL_GPIO_SetOutputPin(FGEN_nDIV10_GPIO_Port, FGEN_nDIV10_Pin);

				bsp.dds.divider = FGEN_DIV0;
			};break;

		case FGEN_DIV2:
		{
				LL_GPIO_ResetOutputPin(FGEN_DIV2_GPIO_Port, FGEN_DIV2_Pin);
				bsp.dds.divider = FGEN_DIV2;
		};break;

		case FGEN_DIV4:
			{
				LL_GPIO_ResetOutputPin(FGEN_DIV4_GPIO_Port, FGEN_DIV4_Pin);
				bsp.dds.divider = FGEN_DIV4;
			}break;

		case FGEN_DIV8:
		{
				LL_GPIO_ResetOutputPin(FGEN_DIV8_GPIO_Port, FGEN_DIV8_Pin);
				bsp.dds.divider = FGEN_DIV8;
			}break;

		case FGEN_DIV10:
			{
				LL_GPIO_ResetOutputPin(FGEN_nDIV10_GPIO_Port, FGEN_nDIV10_Pin);
				bsp.dds.divider = FGEN_DIV10;
			}break;
	}
}

static uint32_t FGEN_ConvertFrequency(float freq)
{
	uint32_t freq28 = 0x00;

	switch(bsp.dds.divider)
	{
		case FGEN_DIV0: freq28 = (uint32_t)(freq / FGEN_DIV0_RES);break;
		case FGEN_DIV2: freq28 = (uint32_t)(freq / FGEN_DIV2_RES);break;
		case FGEN_DIV4: freq28 = (uint32_t)(freq / FGEN_DIV4_RES);break;
		case FGEN_DIV8: freq28 = (uint32_t)(freq / FGEN_DIV8_RES);break;
		case FGEN_DIV10: freq28 = (uint32_t)(freq / FGEN_DIV10_RES);break;
	}

	return freq28;
}

BSP_StatusTypeDef FGEN_SetAmplitude(float amplitude)
{

	float tmp_amp = (float)(FGEN_AMPL_MAX - amplitude);


	return AD5322_SetVOUTA(tmp_amp);
}

BSP_StatusTypeDef FGEN_SetOffset(float offset)
{

	return AD5322_SetVOUTB(offset);


}

BSP_StatusTypeDef FGEN_SetFrequency(float freq)
{
	BSP_StatusTypeDef status = BSP_OK;

	uint32_t freq28 = FGEN_ConvertFrequency(freq);

	status = AD9834_SetFrequency(freq28);
	if(BSP_OK != status){return status;}

	status = AD9834_Start();

	return status;
}

void FGEN_Attenuation(uint8_t attenuation)
{
	switch(attenuation)
	{
		case AT_0dBV:bsp.sn74hc595.shift_reg[SR1] = ~(SR1_ATT_A0);break;

	}

	SN74HC595_Update(bsp.sn74hc595.shift_reg);
}

BSP_StatusTypeDef FGEN_Init()
{
	BSP_StatusTypeDef status = BSP_OK;
	status = FGEN_SetAmplitude(0.0);
	status = FGEN_SetOffset(0.0);
	status = AD9834_Init();

	return status;

}
