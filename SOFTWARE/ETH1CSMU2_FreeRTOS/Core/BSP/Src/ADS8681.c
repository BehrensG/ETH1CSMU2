/*
 * ADS8681.c
 *
 *  Created on: Feb 5, 2023
 *      Author: grzegorz
 */

#include "ADS8681.h"
#include "main.h"
#include "DWT_Delay.h"

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

		HAL_SPI_Receive(&hspi1, rx_tmp, 4, 10000);
		buffer[0] = rx_tmp[0] << 16 | rx_tmp[1];
		buffer[1] = rx_tmp[2] << 16 | rx_tmp[3];

    return BSP_OK;
}

static BSP_StatusTypeDef BSP_SPI1_Transmit(uint32_t* buffer, uint32_t size, uint32_t timeout)
{
	uint16_t tx_tmp[4];
	tx_tmp[0] = (uint16_t) buffer[0];
	tx_tmp[1] = (uint16_t)(buffer[0] >> 16);
	tx_tmp[2] = (uint16_t) buffer[1];
	tx_tmp[3] = (uint16_t)(buffer[1] >> 16);

	HAL_SPI_Transmit(&hspi1, tx_tmp, 4, 10000);

    return BSP_OK;
}

BSP_StatusTypeDef ADS8681_RawData(uint16_t* raw_data)
{
	BSP_StatusTypeDef status = BSP_OK;

	uint32_t rx_data[2];

	LL_GPIO_ResetOutputPin(SPI1_NSS_GPIO_Port, SPI1_NSS_Pin);

	ADS8681_ConvertionTime();

	LL_GPIO_SetOutputPin(SPI1_NSS_GPIO_Port, SPI1_NSS_Pin);

	LL_GPIO_ResetOutputPin(SPI1_NSS_GPIO_Port, SPI1_NSS_Pin);
	status = BSP_SPI1_Receive(rx_data, 2, 10000);
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

	range[0] = bsp.ads8681[0].range = ADS8681_RANGE_3VREF;
	range[1] = bsp.ads8681[1].range = ADS8681_RANGE_3VREF;

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

	DWT_Delay_us(10);

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

	HAL_Delay(1);

	cmd[0] = READ_BYTE;
	cmd[1] = READ_BYTE;

	reg[0] = DEVICE_ID_REG + 0x02;
	reg[1] = DEVICE_ID_REG + 0x02;

	tx_data[0] = 0x00;
	tx_data[1] = 0x00;

	status = ADS8681_WriteLSB(cmd, reg, tx_data);
	if(BSP_OK != status) return status;

	HAL_Delay(1);

	status = ADS8681_ReadLSB(rx_data);
	if(BSP_OK != status) return status;

	tx_data[1] = ADS8681_ID1;
	tx_data[0] = ADS8681_ID2;

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
	status = BSP_SPI1_Receive(rx_data, 2,10000);
	LL_GPIO_SetOutputPin(SPI1_NSS_GPIO_Port, SPI1_NSS_Pin);


	data[0] = rx_data[0] >> 24;
	data[1] = rx_data[1] >> 24;

	return status;

}

static BSP_StatusTypeDef ADS8681_WriteHWORD(uint8_t* cmd, uint8_t* reg, uint16_t* data)
{

	BSP_StatusTypeDef status = BSP_OK;
	uint32_t tx_data[2] = {0x00000000,0x00000000};

	tx_data[0] = cmd[0] << 24 | reg[0] << 16 | (data[0] & 0x0000FFFF);
	tx_data[1] = cmd[1] << 24 | reg[1] << 16 | (data[1] & 0x0000FFFF);

	LL_GPIO_ResetOutputPin(SPI1_NSS_GPIO_Port, SPI1_NSS_Pin);
	//status = HAL_SPI_Transmit(&hspi3, (uint8_t*)tx_data, 2, 1000);
	status = BSP_SPI1_Transmit(tx_data, 2, 10000);
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
	status = BSP_SPI1_Transmit(tx_data, 2, 10000);
	LL_GPIO_SetOutputPin(SPI1_NSS_GPIO_Port, SPI1_NSS_Pin);

	return status;
}


static void ADS8681_ConvertionTime()
{
    uint32_t startTick = DWT->CYCCNT,
             delayTicks = 1 * (SystemCoreClock/15000000);

    while (DWT->CYCCNT - startTick < delayTicks);
}

