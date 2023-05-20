/*
 * DAC8565.c
 *
 *  Created on: Mar 26, 2023
 *      Author: grzegorz
 */

#include "DAC8565.h"

extern SPI_HandleTypeDef hspi2;


static HAL_StatusTypeDef DAC8565_SetOneChannel(DAC8565_ChannelSelect channel, float voltage);
static HAL_StatusTypeDef DAC8565_SetAllChannels(float voltage);
static HAL_StatusTypeDef DAC8565_DisableInteralReference();

void DAC8565_Init()
{
	DAC8565_DisableInteralReference();
	DAC8565_SetVOUT(VOUTA, 0.0);
	DAC8565_SetVOUT(VOUTB, 0.0);
	DAC8565_SetVOUT(VOUTC, 1.0);
	DAC8565_SetVOUT(VOUTD, 1.0);
}

HAL_StatusTypeDef DAC8565_SetVOUT(DAC8565_ChannelSelect channel, float voltage)
{
	HAL_StatusTypeDef status = HAL_OK;

	switch (channel)
	{
		case VOUTA:
		case VOUTB:
		case VOUTC:
		case VOUTD: status = DAC8565_SetOneChannel(channel, voltage); break;
		case ALL: status = DAC8565_SetAllChannels(voltage); break;
	}

	return status;
}

static HAL_StatusTypeDef DAC8565_SetOneChannel(DAC8565_ChannelSelect channel, float voltage)
{
	HAL_StatusTypeDef status = HAL_OK;
	uint8_t spi_data[3] = {0x00};

	uint16_t data = (uint16_t)(voltage/DAC8565_VOUT_LSB);

	switch(channel)
	{
		case VOUTA: spi_data[0] = DAC8565_VOUTA; break;
		case VOUTB: spi_data[0] = DAC8565_VOUTB; break;
		case VOUTC: spi_data[0] = DAC8565_VOUTC; break;
		case VOUTD: spi_data[0] = DAC8565_VOUTD; break;
		case ALL: /* do nothing */ ;break;
	}

	spi_data[1] = (uint8_t)(data >> 8);
	spi_data[2] = (uint8_t)(data & 0xFF);

	LL_GPIO_ResetOutputPin(SPI2_NSS_GPIO_Port, SPI2_NSS_Pin);
	status = HAL_SPI_Transmit(&hspi2, spi_data, 3, 1000);
	LL_GPIO_SetOutputPin(SPI2_NSS_GPIO_Port, SPI2_NSS_Pin);
	return status;
}

static HAL_StatusTypeDef DAC8565_SetAllChannels(float voltage)
{
	HAL_StatusTypeDef status = HAL_OK;
	uint8_t spi_data[3] = {0x00};

	uint16_t data = (uint16_t)(voltage/DAC8565_VOUT_LSB);

	spi_data[0] = DAC8565_VOUTALL;
	spi_data[1] = (uint8_t)(data >> 8);
	spi_data[2] = (uint8_t)(data & 0xFF);

	LL_GPIO_ResetOutputPin(SPI2_NSS_GPIO_Port, SPI2_NSS_Pin);
	status = HAL_SPI_Transmit(&hspi2, (uint8_t*)spi_data, 3, 1000);
	LL_GPIO_SetOutputPin(SPI2_NSS_GPIO_Port, SPI2_NSS_Pin);

	return status;
}

static HAL_StatusTypeDef DAC8565_DisableInteralReference()
{
	HAL_StatusTypeDef status = HAL_OK;
	uint8_t spi_data[3] = {0x01, 0x20, 0x00};

	LL_GPIO_ResetOutputPin(SPI2_NSS_GPIO_Port, SPI2_NSS_Pin);
	status = HAL_SPI_Transmit(&hspi2, (uint8_t*)spi_data, 3, 1000);
	LL_GPIO_SetOutputPin(SPI2_NSS_GPIO_Port, SPI2_NSS_Pin);

	return status;
}
