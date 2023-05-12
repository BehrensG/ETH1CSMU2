/*
 * AD7980.c
 *
 *  Created on: Apr 18, 2023
 *      Author: grzegorz
 */


#include "AD7980.h"

extern SPI_HandleTypeDef hspi4;
extern struct _bsp bsp;

HAL_StatusTypeDef AD7980_ReadData(uint16_t count)
{
	HAL_StatusTypeDef status = HAL_OK;
	uint16_t data[2] = {0x0000,0x00000};
	for(uint16_t x = 0; x < count; x++)
	{
		LL_GPIO_SetOutputPin(SPI4_NSS_GPIO_Port, SPI4_NSS_Pin);
		//status = HAL_SPI_Receive(&hspi4, (uint8_t*)adc_data, 2, 1000);
		status = HAL_SPI_Receive_DMA(&hspi4, (uint8_t*)data, 2);
		LL_GPIO_ResetOutputPin(SPI4_NSS_GPIO_Port, SPI4_NSS_Pin);
		bsp.adc[AD7980_VOLT_CH].meas[x] = (float)((AD7980_FSR_CENTER - data[AD7980_VOLT_CH])*AD7980_LSB);
		bsp.adc[AD7980_CURR_CH].meas[x] = (float)((AD7980_FSR_CENTER - data[AD7980_CURR_CH])*AD7980_LSB);
	}

	return status;

}

void AD7980_RXDataToVoltage(uint16_t count)
{
	for(uint16_t x = 0; x < count; x++)
	{
		//bsp.adc[AD7980_VOLT_CH].meas[x] = (float)((AD7980_FSR_CENTER - bsp.adc[AD7980_VOLT_CH].data[x])*AD7980_LSB);
		//bsp.adc[AD7980_CURR_CH].meas[x] = (float)((AD7980_FSR_CENTER - bsp.adc[AD7980_CURR_CH].data[x])*AD7980_LSB);
	}

}
