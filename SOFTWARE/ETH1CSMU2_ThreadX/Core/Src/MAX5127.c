/*
 * MAX5127.c
 *
 *  Created on: Mar 12, 2023
 *      Author: grzegorz
 */

#include "MAX5217.h"

extern I2C_HandleTypeDef hi2c3;

void MAX5217_Init()
{
	MAX5217_SetVoltage(0.0);
}


// Code adjusted to the schematic of ETH1CSMU2. The input range is from -25mV to 25mV.
HAL_StatusTypeDef MAX5217_SetVoltage(float voltage)
{
	uint8_t i2c_data[3] = {0x00};
	float tmp = ((voltage * VOLT_DIV)/2) + VOLT_MID;
	uint16_t reg16 = (uint16_t)(tmp/MAX5217_LSB);
	HAL_StatusTypeDef status = HAL_OK;

	i2c_data[0] = CODE_LOAD;
	i2c_data[1] = (uint8_t)(reg16 >> 8);
	i2c_data[2] = (uint8_t)(reg16 & 0xFF);

	status = HAL_I2C_Master_Transmit(&hi2c3, MAX5217_ADDR, i2c_data, 3, 1000);

	return status;
}

