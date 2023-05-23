/*
 * AD7980.c
 *
 *  Created on: Apr 18, 2023
 *      Author: grzegorz
 */


#include "AD7980.h"

extern SPI_HandleTypeDef hspi4;
extern struct bsp_t bsp;

HAL_StatusTypeDef AD7980_ReadData(uint16_t count)
{
	HAL_StatusTypeDef status = HAL_OK;
	uint16_t data[2] = {0x0000,0x00000};
	float tmp[2];
	uint8_t volt_gain_index, curr_gain_index;

	volt_gain_index = bsp.config.measure.gain_index[ADC_VOLTAGE];
	curr_gain_index = bsp.config.measure.gain_index[ADC_CURRENT];

	for(uint16_t x = 0; x < count; x++)
	{
		LL_GPIO_SetOutputPin(SPI4_NSS_GPIO_Port, SPI4_NSS_Pin);
		//status = HAL_SPI_Receive(&hspi4, (uint8_t*)adc_data, 2, 1000);
		status = HAL_SPI_Receive_DMA(&hspi4, (uint8_t*)data, 2);
		LL_GPIO_ResetOutputPin(SPI4_NSS_GPIO_Port, SPI4_NSS_Pin);

		tmp[ADC_VOLTAGE] = (float)((AD7980_FSR_CENTER - data[ADC_VOLTAGE])*AD7980_LSB);
		tmp[ADC_CURRENT] = (float)((AD7980_FSR_CENTER - data[ADC_CURRENT])*AD7980_LSB);

		tmp[ADC_VOLTAGE] = tmp[ADC_VOLTAGE]*bsp.eeprom.structure.calib.ad7980[ADC_VOLTAGE].gain[volt_gain_index] + bsp.eeprom.structure.calib.ad7980[ADC_VOLTAGE].offset[volt_gain_index];
		tmp[ADC_CURRENT] = tmp[ADC_CURRENT]*bsp.eeprom.structure.calib.ad7980[ADC_CURRENT].gain[curr_gain_index] + bsp.eeprom.structure.calib.ad7980[ADC_CURRENT].offset[curr_gain_index];

		bsp.adc[ADC_VOLTAGE].meas[x] = tmp[ADC_VOLTAGE]/bsp.config.measure.gain[ADC_VOLTAGE];
		bsp.adc[ADC_CURRENT].meas[x] = tmp[ADC_VOLTAGE]/bsp.config.measure.gain[ADC_CURRENT];

		TIM_Delay_us(bsp.config.measure.delay);
	}

	bsp.state.meas_count = count;

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
