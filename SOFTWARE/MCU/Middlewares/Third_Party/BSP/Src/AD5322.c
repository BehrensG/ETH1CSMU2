/*
 * AD5322.c
 *
 *  Created on: Mar 16, 2023
 *      Author: grzegorz
 */

#include "AD5322.h"

extern SPI_HandleTypeDef hspi5;

static HAL_StatusTypeDef AD5322_Send(uint16_t* data);

HAL_StatusTypeDef AD5322_Init()
{
	AD5322_SetVOUTA(0.1);
	AD5322_SetVOUTB(0.0);
}

HAL_StatusTypeDef AD5322_SetVOUTA(float voltage)
{
	uint16_t data = (uint16_t)(voltage/AD5322_VOUTA_LSB);

	return AD5322_Send(&data);
}

HAL_StatusTypeDef AD5322_SetVOUTB(float voltage)
{
	float tmp = (voltage/AD5322_VOLT_MULTI) + AD5322_VOLTB_REF/2;
	uint16_t data = (uint16_t)(voltage/AD5322_VOUTB_LSB);
	data |= AD5322_DACB_ENABLE;

	return AD5322_Send(&data);
}

static HAL_StatusTypeDef AD5322_Send(uint16_t* data)
{
	HAL_StatusTypeDef status = HAL_OK;

	LL_GPIO_ResetOutputPin(SPI5_NSS_GPIO_Port, SPI5_NSS_Pin);
	status = HAL_SPI_Transmit(&hspi5, (uint8_t*)data, 1, 1000);
	LL_GPIO_SetOutputPin(SPI5_NSS_GPIO_Port, SPI5_NSS_Pin);

	LL_GPIO_ResetOutputPin(DAC2_nLDAC_GPIO_Port, DAC2_nLDAC_Pin);
	LL_GPIO_SetOutputPin(DAC2_nLDAC_GPIO_Port, DAC2_nLDAC_Pin);

	return status;
}
