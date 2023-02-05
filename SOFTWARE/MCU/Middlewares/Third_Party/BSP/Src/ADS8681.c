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
extern struct _bsp bsp;

static BSP_StatusTypeDef ADS8681_Set_ID(void);
static BSP_StatusTypeDef ADS8681_Set_Data_Output(void);
static BSP_StatusTypeDef ADS8681_Write_MSB(uint8_t* cmd, uint8_t* reg, uint8_t* data);
static BSP_StatusTypeDef ADS8681_Write_LSB(uint8_t* cmd, uint8_t* reg, uint8_t* data);
static BSP_StatusTypeDef ADS8681_Write_HWORD(uint8_t* cmd, uint8_t* reg, uint16_t* data);
static BSP_StatusTypeDef ADS8681_Read_LSB(uint8_t* data);
static void ADS8681_Convertion_Time(void);



static BSP_StatusTypeDef BSP_SPI_Receive(uint32_t* buffer, uint32_t size, uint32_t timeout)
{

	uint32_t tickstart = 0;

    LL_SPI_SetTransferSize(SPI, size);
    LL_SPI_Enable(SPI);
    LL_SPI_StartMasterTransfer(SPI);

    for (uint32_t i = 0; i < size; i++)
    {
        while (LL_SPI_IsActiveFlag_TXP(SPI) == 0)
        {
        	if((((HAL_GetTick() - tickstart) >=  timeout) && (timeout != SPI_MAX_DELAY)) || (timeout == 0U))
        	{
        		return BSP_TIMEOUT;
        	}
        }

        LL_SPI_TransmitData32(SPI, 0xFFFFFFFF);
    }


    for (uint32_t i = 0; i < size; i++)
    {
        while (LL_SPI_IsActiveFlag_RXWNE(SPI) == 0);
        buffer[i] = LL_SPI_ReceiveData32(SPI);
    }

    while (LL_SPI_IsActiveFlag_EOT(SPI) == 0)
    {
    	if((((HAL_GetTick() - tickstart) >=  timeout) && (timeout != SPI_MAX_DELAY)) || (timeout == 0U))
    	{
    		return BSP_TIMEOUT;
    	}
    }

    LL_SPI_ClearFlag_EOT(SPI);
    LL_SPI_ClearFlag_TXTF(SPI);
    LL_SPI_SuspendMasterTransfer(SPI);
    LL_SPI_Disable(SPI);

    return BSP_OK;
}

static BSP_StatusTypeDef BSP_SPI_Transmit(uint32_t* buffer, uint32_t size, uint32_t timeout)
{

	uint32_t tickstart = 0;

	uint32_t rx_buffer[ADC_COUNT];

    LL_SPI_SetTransferSize(SPI, size);
    LL_SPI_Enable(SPI);
    LL_SPI_StartMasterTransfer(SPI);

    for (uint32_t i = 0; i < size; i++)
    {
        while (LL_SPI_IsActiveFlag_TXP(SPI) == 0);
        LL_SPI_TransmitData32(SPI, buffer[i]);
    }

    for (uint32_t i = 0; i < size; i++)
    {
        while (LL_SPI_IsActiveFlag_RXWNE(SPI) == 0)
        {
        	if((((HAL_GetTick() - tickstart) >=  timeout) && (timeout != SPI_MAX_DELAY)) || (timeout == 0U))
        	{
        		return BSP_TIMEOUT;
        	}
        }

        rx_buffer[i] = LL_SPI_ReceiveData32(SPI);
    }

    while (LL_SPI_IsActiveFlag_EOT(SPI) == 0)
    {
    	if((((HAL_GetTick() - tickstart) >=  timeout) && (timeout != SPI_MAX_DELAY)) || (timeout == 0U))
    	{
    		return BSP_TIMEOUT;
    	}
    }

    LL_SPI_ClearFlag_EOT(SPI);
    LL_SPI_ClearFlag_TXTF(SPI);
    LL_SPI_SuspendMasterTransfer(SPI);
    LL_SPI_Disable(SPI);

    return BSP_OK;
}

BSP_StatusTypeDef ADS8681_Raw_Data(uint16_t* raw_data)
{
	BSP_StatusTypeDef status = BSP_OK;

	uint32_t rx_data[ADC_COUNT];

	LL_GPIO_ResetOutputPin(MCU_nCS_GPIO_Port, MCU_nCS_Pin);
	//ADS8681_Convertion_Time();
	delay100NS_ASM(5);
	LL_GPIO_SetOutputPin(MCU_nCS_GPIO_Port, MCU_nCS_Pin);

	LL_GPIO_ResetOutputPin(MCU_nCS_GPIO_Port, MCU_nCS_Pin);
	status = BSP_SPI_Receive(rx_data, ADC_COUNT, SPI_TIMEOUT);
	LL_GPIO_SetOutputPin(MCU_nCS_GPIO_Port, MCU_nCS_Pin);

	if(BSP_OK != status)
	{
		return status;
	}
	else
	{
		raw_data[0] = (uint16_t)(rx_data[2] >> 16);
		raw_data[1] = (uint16_t)(rx_data[1] >> 16);
		raw_data[2] = (uint16_t)(rx_data[0] >> 16);

		return BSP_OK;
	}

}


BSP_StatusTypeDef ADS8681_Init(void)
{
	BSP_StatusTypeDef status = BSP_OK;
	uint8_t range[ADC_COUNT] = {0,0,0};

	status = ADS8681_Set_ID();
	if(BSP_OK != status) return status;

	range[0] = bsp.adc[0].range = ADS8681_RANGE_3VREF;
	range[1] = bsp.adc[1].range = ADS8681_RANGE_3VREF;
	range[2] = bsp.adc[2].range = ADS8681_RANGE_3VREF;

	status = ADS8681_Set_Data_Output();
	if(BSP_OK != status) return status;

	status = ADS8681_Set_Range(range);
	if(BSP_OK != status) return status;

	return BSP_OK;
}

static BSP_StatusTypeDef ADS8681_Set_Data_Output(void)
{

	uint8_t cmd[ADC_COUNT] = {0,0,0};
	uint8_t reg[ADC_COUNT] = {0,0,0};
	uint16_t tx_hword[ADC_COUNT] = {0,0,0};

	cmd[0] = WRITE_HWORD;
	cmd[1] = WRITE_HWORD;
	cmd[2] = WRITE_HWORD;

	reg[0] = DATAOUT_CTL_REG;
	reg[1] = DATAOUT_CTL_REG;
	reg[2] = DATAOUT_CTL_REG;

	tx_hword[0] = 0x7D08;
	tx_hword[1] = 0x7D08;
	tx_hword[2] = 0x7D08;

	return ADS8681_Write_HWORD(cmd, reg, tx_hword);

}


BSP_StatusTypeDef ADS8681_Set_Range(uint8_t range[])
{
	uint8_t cmd[ADC_COUNT]={0,0,0};
	uint8_t reg[ADC_COUNT]={0,0,0};
	uint8_t tx_data[ADC_COUNT]={0,0,0};
	uint8_t rx_data[ADC_COUNT]={0,0,0};

	BSP_StatusTypeDef status = BSP_OK;

	cmd[0] = WRITE_LSB;
	cmd[1] = WRITE_LSB;
	cmd[2] = WRITE_LSB;

	reg[0] = RANGE_SEL_REG;
	reg[1] = RANGE_SEL_REG;
	reg[2] = RANGE_SEL_REG;

	tx_data[2] = range[2];
	tx_data[1] = range[1];
	tx_data[0] = range[0];

	status = ADS8681_Write_LSB(cmd, reg, tx_data);
	if(BSP_OK != status) return status;


	delayUS_ASM(10);

	return BSP_OK;
}

static BSP_StatusTypeDef ADS8681_Set_ID(void)
{
	uint8_t cmd[ADC_COUNT]={0,0,0};
	uint8_t reg[ADC_COUNT]={0,0,0};
	uint8_t tx_data[ADC_COUNT]={0,0,0};
	uint8_t rx_data[ADC_COUNT]={0,0,0};

	BSP_StatusTypeDef status = BSP_OK;

	cmd[0] = WRITE_LSB;
	cmd[1] = WRITE_LSB;
	cmd[2] = WRITE_LSB;

	reg[0] = DEVICE_ID_REG + 0x02;
	reg[1] = DEVICE_ID_REG + 0x02;
	reg[2] = DEVICE_ID_REG + 0x02;

	tx_data[2] = ADS8681_ID1;
	tx_data[1] = ADS8681_ID2;
	tx_data[0] = ADS8681_ID3;

	status = ADS8681_Write_LSB(cmd, reg, tx_data);
	if(BSP_OK != status) return status;

	delayUS_ASM(1);

	cmd[0] = READ_BYTE;
	cmd[1] = READ_BYTE;
	cmd[2] = READ_BYTE;

	reg[0] = DEVICE_ID_REG + 0x02;
	reg[1] = DEVICE_ID_REG + 0x02;
	reg[2] = DEVICE_ID_REG + 0x02;

	tx_data[0] = 0x00;
	tx_data[1] = 0x00;
	tx_data[2] = 0x00;

	status = ADS8681_Write_LSB(cmd, reg, tx_data);
	if(BSP_OK != status) return status;

	delayUS_ASM(1);

	status = ADS8681_Read_LSB(rx_data);
	if(BSP_OK != status) return status;

	tx_data[2] = ADS8681_ID1;
	tx_data[1] = ADS8681_ID2;
	tx_data[0] = ADS8681_ID3;

	for (uint8_t x = 0; x < ADC_COUNT; x++)
	{
		if(rx_data[x] != tx_data[x])
		{
			return BSP_ADC_CONFIG_ERROR;
		}
	}

	return BSP_OK;
}


static BSP_StatusTypeDef ADS8681_Read_LSB(uint8_t* data)
{

	BSP_StatusTypeDef status = BSP_OK;
	uint32_t rx_data[ADC_COUNT] = {0x00000000,0x00000000,0x00000000};

	LL_GPIO_ResetOutputPin(MCU_nCS_GPIO_Port, MCU_nCS_Pin);
	status = BSP_SPI_Receive(rx_data, ADC_COUNT, SPI_TIMEOUT);
	LL_GPIO_SetOutputPin(MCU_nCS_GPIO_Port, MCU_nCS_Pin);

	if(BSP_OK != status) return status;

	data[0] = rx_data[0] >> 24;
	data[1] = rx_data[1] >> 24;
	data[2] = rx_data[2] >> 24;

	return BSP_OK;
}

static BSP_StatusTypeDef ADS8681_Write_HWORD(uint8_t* cmd, uint8_t* reg, uint16_t* data)
{

	BSP_StatusTypeDef status = BSP_OK;
	uint32_t tx_data[ADC_COUNT] = {0x00000000,0x00000000,0x00000000};

	tx_data[0] = cmd[0] << 24 | reg[0] << 16 | (data[0] & 0x0000FFFF);
	tx_data[1] = cmd[1] << 24 | reg[1] << 16 | (data[1] & 0x0000FFFF);
	tx_data[2] = cmd[2] << 24 | reg[2] << 16 | (data[2] & 0x0000FFFF);

	LL_GPIO_ResetOutputPin(MCU_nCS_GPIO_Port, MCU_nCS_Pin);
	status = BSP_SPI_Transmit(tx_data, ADC_COUNT, SPI_TIMEOUT);
	LL_GPIO_SetOutputPin(MCU_nCS_GPIO_Port, MCU_nCS_Pin);

	return status;
}

static BSP_StatusTypeDef ADS8681_Write_MSB(uint8_t* cmd, uint8_t* reg, uint8_t* data)
{

	BSP_StatusTypeDef status = BSP_OK;
	uint32_t tx_data[ADC_COUNT] = {0x00000000,0x00000000,0x00000000};

	tx_data[0] = cmd[0];
	tx_data[1] = reg[0];
	tx_data[2] = 0x00;
	tx_data[3] = data[0];

	tx_data[0] = cmd[0] << 24 | reg[0] << 16 | (data[0] & 0x000000FF);
	tx_data[1] = cmd[1] << 24 | reg[1] << 16 | (data[1] & 0x000000FF);
	tx_data[2] = cmd[2] << 24 | reg[2] << 16 | (data[2] & 0x000000FF);

	LL_GPIO_ResetOutputPin(MCU_nCS_GPIO_Port, MCU_nCS_Pin);
	status = BSP_SPI_Transmit(tx_data, ADC_COUNT, SPI_TIMEOUT);
	LL_GPIO_SetOutputPin(MCU_nCS_GPIO_Port, MCU_nCS_Pin);

	return status;
}

static BSP_StatusTypeDef ADS8681_Write_LSB(uint8_t* cmd, uint8_t* reg, uint8_t* data)
{

	BSP_StatusTypeDef status = BSP_OK;
	uint32_t tx_data[ADC_COUNT] = {0x00000000,0x00000000,0x00000000};

	tx_data[0] = cmd[0] << 24 | reg[0] << 16 | (data[0] & 0x000000FF);
	tx_data[1] = cmd[1] << 24 | reg[1] << 16 | (data[1] & 0x000000FF);
	tx_data[2] = cmd[2] << 24 | reg[2] << 16 | (data[2] & 0x000000FF);


	LL_GPIO_ResetOutputPin(MCU_nCS_GPIO_Port, MCU_nCS_Pin);
	status = BSP_SPI_Transmit(tx_data, ADC_COUNT, SPI_TIMEOUT);
	LL_GPIO_SetOutputPin(MCU_nCS_GPIO_Port, MCU_nCS_Pin);

	return status;
