/*
 * ADS8681.c
 *
 *  Created on: Feb 5, 2023
 *      Author: grzegorz
 */

#include "Delay.h"
#include "ADS8681.h"
#include "main.h"



double ADS8681_LSB[5] = {0.000375000, 0.000312500, 0.000187500, 0.000156250, 0.000078125};

extern SPI_HandleTypeDef hspi1;
extern struct bsp_t bsp;

static BSP_StatusTypeDef ADS8681_SetID();
static BSP_StatusTypeDef ADS8681_SetDataOutput();
static BSP_StatusTypeDef ADS8681_WriteLSB(uint8_t* cmd, uint8_t* reg, uint8_t* data);
static BSP_StatusTypeDef ADS8681_WriteHWORD(uint8_t* cmd, uint8_t* reg, uint16_t* data);
static BSP_StatusTypeDef ADS8681_ReadLSB(uint8_t* data);
static void ADS8681_ConvertionTime();

static BSP_StatusTypeDef BSP_SPI1_Receive(uint32_t* buffer, uint32_t size, uint32_t timeout)
{
	uint16_t rx_tmp[4];

		HAL_SPI_Receive(&hspi1, rx_tmp, 4, timeout);
		buffer[0] = rx_tmp[3] << 16 | rx_tmp[2];
		buffer[1] = rx_tmp[1] << 16 | rx_tmp[0];

    return BSP_OK;
}


void ADS8681_RangeSelect(float voltage)
{
	BSP_StatusTypeDef status = BSP_OK;
	float abs_voltage = fabs(voltage);
	uint8_t range[2] = {0,0};

	if(abs_voltage <= (float)2.5)
	{
		range[0] = bsp.ads8681[ADC_VOLTAGE].range = ADS8681_RANGE_0_625VREF;
	}
	else if (abs_voltage <= (float)5.0)
	{
		range[0] = bsp.ads8681[ADC_VOLTAGE].range = ADS8681_RANGE_1_25VREF;
	}
	else if (abs_voltage <= (float)6.0)
	{
		range[0] = bsp.ads8681[ADC_VOLTAGE].range = ADS8681_RANGE_1_5VREF;
	}
	else if (abs_voltage <= (float)10.0)
	{
		range[0] = bsp.ads8681[ADC_VOLTAGE].range = ADS8681_RANGE_2_5VREF;
	}
	else
	{
		range[0] = bsp.ads8681[ADC_VOLTAGE].range = ADS8681_RANGE_3VREF;
	}

	status = ADS8681_SetRange(range);

}

static BSP_StatusTypeDef BSP_SPI1_Transmit(uint32_t* buffer, uint32_t size, uint32_t timeout)
{
	uint16_t tx_tmp[4];
	tx_tmp[3] = (uint16_t) buffer[0];
	tx_tmp[2] = (uint16_t)(buffer[0] >> 16);
	tx_tmp[1] = (uint16_t) buffer[1];
	tx_tmp[0] = (uint16_t)(buffer[1] >> 16);

	HAL_SPI_Transmit(&hspi1, tx_tmp, 4, timeout);

    return BSP_OK;
}

HAL_StatusTypeDef ADS8681_ReadData(uint16_t count)
{
	HAL_StatusTypeDef status = HAL_OK;
	uint32_t rx_data[2] = {0x00,0x00};
	uint16_t data[2] = {0x00, 0x00};
	float tmp[2] = {0.0, 0.0};
	uint8_t volt_gain_index = 0, curr_gain_index = 0;

	volt_gain_index = bsp.config.measure.gain_index[ADC_VOLTAGE];
	curr_gain_index = bsp.config.measure.gain_index[ADC_CURRENT];

	for(uint16_t x = 0; x < count; x++)
	{
		LL_GPIO_ResetOutputPin(SPI1_NSS_GPIO_Port, SPI1_NSS_Pin);

		//ADS8681_ConvertionTime();
		TIM_Delay_us(1);

		LL_GPIO_SetOutputPin(SPI1_NSS_GPIO_Port, SPI1_NSS_Pin);

		LL_GPIO_ResetOutputPin(SPI1_NSS_GPIO_Port, SPI1_NSS_Pin);
		status = BSP_SPI1_Receive(rx_data, 2, 1000);
		LL_GPIO_SetOutputPin(SPI1_NSS_GPIO_Port, SPI1_NSS_Pin);

		data[0] = (uint16_t)(rx_data[0]);
		data[1] = (uint16_t)(rx_data[1]);

		tmp[ADC_VOLTAGE] = (float)((data[ADC_VOLTAGE] - ADS8681_FSR_CENTER)*ADS8681_LSB[bsp.ads8681[ADC_VOLTAGE].range]);
		tmp[ADC_CURRENT] = (float)((data[ADC_CURRENT] - ADS8681_FSR_CENTER)*ADS8681_LSB[bsp.ads8681[ADC_CURRENT].range]);

		tmp[ADC_VOLTAGE] = tmp[ADC_VOLTAGE]*bsp.eeprom.structure.calib.ads8681[ADC_VOLTAGE].gain[volt_gain_index];
		tmp[ADC_CURRENT] = tmp[ADC_CURRENT]*bsp.eeprom.structure.calib.ads8681[ADC_CURRENT].gain[curr_gain_index];

		bsp.adc[ADC_VOLTAGE].meas[x] = tmp[ADC_VOLTAGE]/(float)(bsp.config.measure.gain[ADC_VOLTAGE]);
		bsp.adc[ADC_CURRENT].meas[x] = tmp[ADC_CURRENT]/(float)(bsp.config.measure.gain[ADC_CURRENT]);

		TIM_Delay_us(bsp.config.measure.delay);
	}

	bsp.state.meas_count = count;

	return status;
}

void ADS8681_VoltageCorrection(float* meas)
{
	HAL_StatusTypeDef status = HAL_OK;
	uint32_t rx_data[2] = {0x00,0x00};
	uint16_t data[2] = {0x00, 0x00};
	uint16_t count = 20;
	float tmp[2] = {0.0, 0.0};
	float volt_meas[count], curr_meas[count];

	uint8_t volt_gain_index = 0, curr_gain_index = 0;

	volt_gain_index = bsp.config.measure.gain_index[ADC_VOLTAGE];
	curr_gain_index = bsp.config.measure.gain_index[ADC_CURRENT];


	for(uint16_t x = 0; x < count; x++)
	{
		LL_GPIO_ResetOutputPin(SPI1_NSS_GPIO_Port, SPI1_NSS_Pin);

		//ADS8681_ConvertionTime();
		TIM_Delay_us(1);

		LL_GPIO_SetOutputPin(SPI1_NSS_GPIO_Port, SPI1_NSS_Pin);

		LL_GPIO_ResetOutputPin(SPI1_NSS_GPIO_Port, SPI1_NSS_Pin);
		status = BSP_SPI1_Receive(rx_data, 2, 1000);
		LL_GPIO_SetOutputPin(SPI1_NSS_GPIO_Port, SPI1_NSS_Pin);

		data[0] = (uint16_t)(rx_data[0]);
		data[1] = (uint16_t)(rx_data[1]);

		tmp[ADC_VOLTAGE] = (float)((data[ADC_VOLTAGE] - ADS8681_FSR_CENTER)*ADS8681_LSB[bsp.ads8681[ADC_VOLTAGE].range]);
		tmp[ADC_CURRENT] = (float)((data[ADC_CURRENT] - ADS8681_FSR_CENTER)*ADS8681_LSB[bsp.ads8681[ADC_CURRENT].range]);

		tmp[ADC_VOLTAGE] = tmp[ADC_VOLTAGE]*bsp.eeprom.structure.calib.ads8681[ADC_VOLTAGE].gain[volt_gain_index];
		tmp[ADC_CURRENT] = tmp[ADC_CURRENT]*bsp.eeprom.structure.calib.ads8681[ADC_CURRENT].gain[curr_gain_index];

		volt_meas[x] = tmp[ADC_VOLTAGE]/(float)(bsp.config.measure.gain[ADC_VOLTAGE]);
		curr_meas[x] = tmp[ADC_CURRENT]/(float)(bsp.config.measure.gain[ADC_CURRENT]);

	}

	for (uint16_t i = 0; i < count; i++)
	{
		meas[ADC_VOLTAGE] += volt_meas[i]/count;
		meas[ADC_CURRENT] += curr_meas[i]/count;
	}

}

BSP_StatusTypeDef ADS8681_RawData(uint16_t* raw_data)
{
	BSP_StatusTypeDef status = BSP_OK;

	uint32_t rx_data[2];

	LL_GPIO_ResetOutputPin(SPI1_NSS_GPIO_Port, SPI1_NSS_Pin);

	ADS8681_ConvertionTime();

	LL_GPIO_SetOutputPin(SPI1_NSS_GPIO_Port, SPI1_NSS_Pin);

	LL_GPIO_ResetOutputPin(SPI1_NSS_GPIO_Port, SPI1_NSS_Pin);
	status = BSP_SPI1_Receive(rx_data, 2, 1000);
	LL_GPIO_SetOutputPin(SPI1_NSS_GPIO_Port, SPI1_NSS_Pin);

	if(BSP_OK != status)
	{
		return status;
	}
	else
	{
		raw_data[0] = (uint16_t)(rx_data[1] >> 16);
		raw_data[1] = (uint16_t)(rx_data[0] >> 16);

		return BSP_OK;
	}

}


BSP_StatusTypeDef ADS8681_Init()
{
	BSP_StatusTypeDef status = BSP_OK;
	uint8_t range[2] = {0,0};

	status = ADS8681_SetID();
	if(BSP_OK != status) return status;

	range[0] = bsp.ads8681[ADC_VOLTAGE].range = ADS8681_RANGE_3VREF;
	range[1] = bsp.ads8681[ADC_CURRENT].range = ADS8681_RANGE_3VREF;

	status = ADS8681_SetDataOutput();
	if(BSP_OK != status) return status;

	status = ADS8681_SetRange(range);

	return status;
}

static BSP_StatusTypeDef ADS8681_SetDataOutput()
{

	uint8_t cmd[2];
	uint8_t reg[2];
	uint16_t tx_hword[2];

	cmd[0] = WRITE_HWORD;
	cmd[1] = WRITE_HWORD;

	reg[0] = DATAOUT_CTL_REG;
	reg[1] = DATAOUT_CTL_REG;

	tx_hword[0] = 0x7D08;
	tx_hword[1] = 0x7D08;

	return ADS8681_WriteHWORD(cmd, reg, tx_hword);

}


BSP_StatusTypeDef ADS8681_SetRange(uint8_t* range)
{
	BSP_StatusTypeDef status = BSP_OK;
	uint8_t cmd[2]={0,0};
	uint8_t reg[2]={0,0};
	uint8_t tx_data[2]={0,0};

	cmd[0] = WRITE_LSB;
	cmd[1] = WRITE_LSB;

	reg[0] = RANGE_SEL_REG;
	reg[1] = RANGE_SEL_REG;

	tx_data[1] = range[1];
	tx_data[0] = range[0];

	status = ADS8681_WriteLSB(cmd, reg, tx_data);
	if(BSP_OK != status){return status;}

	TIM_Delay_us(10);

	return status;
}

static BSP_StatusTypeDef ADS8681_SetID()
{
	uint8_t cmd[2]={0,0};
	uint8_t reg[2]={0,0};
	uint8_t tx_data[2]={0,0};
	uint8_t rx_data[2]={0,0};

	BSP_StatusTypeDef status = BSP_OK;

	cmd[0] = WRITE_LSB;
	cmd[1] = WRITE_LSB;

	reg[0] = DEVICE_ID_REG + 0x02;
	reg[1] = DEVICE_ID_REG + 0x02;

	tx_data[1] = ADS8681_ID1;
	tx_data[0] = ADS8681_ID2;

	status = ADS8681_WriteLSB(cmd, reg, tx_data);
	if(BSP_OK != status) return status;

	TIM_Delay_us(1000);

	cmd[0] = READ_BYTE;
	cmd[1] = READ_BYTE;

	reg[0] = DEVICE_ID_REG + 0x02;
	reg[1] = DEVICE_ID_REG + 0x02;

	tx_data[0] = 0x00;
	tx_data[1] = 0x00;

	status = ADS8681_WriteLSB(cmd, reg, tx_data);
	if(BSP_OK != status) return status;

	TIM_Delay_us(1000);

	status = ADS8681_ReadLSB(rx_data);
	if(BSP_OK != status) return status;

	tx_data[0] = ADS8681_ID1;
	tx_data[1] = ADS8681_ID2;

	for (uint8_t x = 0; x < 2; x++)
	{
		if(rx_data[x] != tx_data[x])
		{
			return BSP_ADC_CONFIG_ERROR;
		}
	}

	return BSP_OK;
}


static BSP_StatusTypeDef ADS8681_ReadLSB(uint8_t* data)
{

	BSP_StatusTypeDef status = BSP_OK;
	uint32_t rx_data[2] = {0x00000000,0x00000000};

	LL_GPIO_ResetOutputPin(SPI1_NSS_GPIO_Port, SPI1_NSS_Pin);
	//status = HAL_SPI_Receive(&hspi3, (uint8_t*)rx_data, 2, 1000);
	status = BSP_SPI1_Receive(rx_data, 2,1000);
	LL_GPIO_SetOutputPin(SPI1_NSS_GPIO_Port, SPI1_NSS_Pin);


	data[0] = rx_data[0] >> 24;
	data[1] = rx_data[1] >> 24;

	return status;

}

static BSP_StatusTypeDef ADS8681_WriteHWORD(uint8_t* cmd, uint8_t* reg, uint16_t* data)
{

	BSP_StatusTypeDef status = BSP_OK;
	uint16_t tx_data[4] = {0x00000000,0x00000000};

	tx_data[0] = cmd[0] << 8 | reg[0];
	tx_data[1] = data[0] & 0x0000FFFF;
	tx_data[2] = cmd[1] << 8 | reg[1];
	tx_data[3] = data[1] & 0x0000FFFF;

	LL_GPIO_ResetOutputPin(SPI1_NSS_GPIO_Port, SPI1_NSS_Pin);
	//status = HAL_SPI_Transmit(&hspi3, (uint8_t*)tx_data, 2, 1000);
	status = BSP_SPI1_Transmit(tx_data, 4, 1000);
	LL_GPIO_SetOutputPin(SPI1_NSS_GPIO_Port, SPI1_NSS_Pin);

	return status;
}


/*
static BSP_StatusTypeDef ADS8681_WriteMSB(uint8_t* cmd, uint8_t* reg, uint8_t* data)
{
	BSP_StatusTypeDef status = BSP_OK;
	uint32_t tx_data[2] = {0x00000000,0x00000000};


	tx_data[0] = cmd[0] << 24 | reg[0] << 16 | (data[0] & 0x000000FF);
	tx_data[1] = cmd[1] << 24 | reg[1] << 16 | (data[1] & 0x000000FF);


	LL_GPIO_ResetOutputPin(SPI1_NSS_GPIO_Port, SPI1_NSS_Pin);
	//status = HAL_SPI_Transmit(&hspi3, (uint8_t*)tx_data, 2, 1000);
	status = BSP_SPI1_Transmit(tx_data, 2,10000);
	LL_GPIO_SetOutputPin(SPI1_NSS_GPIO_Port, SPI1_NSS_Pin);

	return status;
}
*/

static BSP_StatusTypeDef ADS8681_WriteLSB(uint8_t* cmd, uint8_t* reg, uint8_t* data)
{

	BSP_StatusTypeDef status = BSP_OK;
	uint32_t tx_data[2] = {0x00000000,0x00000000};

	tx_data[0] = cmd[0] << 24 | reg[0] << 16 | (data[0] & 0x000000FF);
	tx_data[1] = cmd[1] << 24 | reg[1] << 16 | (data[1] & 0x000000FF);

	LL_GPIO_ResetOutputPin(SPI1_NSS_GPIO_Port, SPI1_NSS_Pin);
	//status = HAL_SPI_Transmit(&hspi3, (uint8_t*)tx_data, 2, 1000);
	status = BSP_SPI1_Transmit(tx_data, 2, 1000);
	LL_GPIO_SetOutputPin(SPI1_NSS_GPIO_Port, SPI1_NSS_Pin);

	return status;
}


static void ADS8681_ConvertionTime()
{
    uint32_t startTick = DWT->CYCCNT,
             delayTicks = 1 * (SystemCoreClock/15000000);

    while (DWT->CYCCNT - startTick < delayTicks);
}

