/*
 * AD7980.c
 *
 *  Created on: Apr 18, 2023
 *      Author: grzegorz
 */


#include "AD7980.h"

extern SPI_HandleTypeDef hspi4;

float* AD7980_RXDataToVoltage(uint16_t* rx_data);

HAL_StatusTypeDef AD7980_ReadData(uint16_t* rx_data)
{
	HAL_StatusTypeDef status = HAL_OK;
	uint16_t adc_data[2] = {0x0000,0x00000};
	LL_GPIO_SetOutputPin(SPI4_NSS_GPIO_Port, SPI4_NSS_Pin);
	//DWT_Delay_ns(600);
	//status = HAL_SPI_Receive(&hspi4, (uint8_t*)adc_data, 2, 1000);
	status = HAL_SPI_Receive_DMA(&hspi4, (uint8_t*)adc_data, 2);
	LL_GPIO_ResetOutputPin(SPI4_NSS_GPIO_Port, SPI4_NSS_Pin);
	rx_data[0] = adc_data[0];
	rx_data[1] = adc_data[1];
	return status;

}

float* AD7980_RXDataToVoltage(uint16_t* rx_data)
{
	static float meas[2] = {0.0, 0.0};
	meas[AD7980_VOLT_CH] = (float)((AD7980_FSR_CENTER - rx_data[AD7980_VOLT_CH])*AD7980_LSB);
	meas[AD7980_CURR_CH] = (float)((AD7980_FSR_CENTER - rx_data[AD7980_CURR_CH])*AD7980_LSB);
	return meas;

}
