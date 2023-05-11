/*
 * AD9834.c
 *
 *  Created on: Mar 11, 2023
 *      Author: grzegorz
 */


#include "AD9834.h"

uint16_t reg_config = 0x0000;

extern SPI_HandleTypeDef hspi3;

inline static void SelectChip()
{
	LL_GPIO_ResetOutputPin(SPI3_NSS_GPIO_Port, SPI3_NSS_Pin);
}

inline static void ReleaseChip()
{
	LL_GPIO_SetOutputPin(SPI3_NSS_GPIO_Port, SPI3_NSS_Pin);
}

inline static void SetBit(uint16_t mask) {
  reg_config |= mask;
}

inline static void ClrBit(uint16_t mask) {
  reg_config &= (0xFFFF ^ mask);
}

BSP_StatusTypeDef AD9834_Init()
{
	BSP_StatusTypeDef status = BSP_OK;
	//SelectChip();
	uint16_t tx_data[7];

	SetBit(B28);
	SetBit(RESET);

	tx_data[0] = reg_config;
	tx_data[1] = FREQ0_ADDR;
	tx_data[2] = FREQ0_ADDR;
	tx_data[3] = FREQ1_ADDR;
	tx_data[4] = FREQ1_ADDR;
	tx_data[5] = PHASE0_ADDR;
	tx_data[6] = PHASE1_ADDR;

	SelectChip();
	status = HAL_SPI_Transmit(&hspi3, (uint8_t*)tx_data, 7, SPI3_TIMEOUT);
	ReleaseChip();
	HAL_Delay(20);

	return status;
}

BSP_StatusTypeDef AD9834_SetPhase(uint16_t word12)
{
	BSP_StatusTypeDef status = BSP_OK;
	uint16_t tmp = 0;

	word12 &= 0x0FFF;
	tmp = PHASE0_ADDR | word12;
	ClrBit(PSEL);

	SelectChip();

	status = HAL_SPI_Transmit(&hspi3, (uint8_t*)tmp, 1, SPI3_TIMEOUT);
	status = HAL_SPI_Transmit(&hspi3, (uint8_t*)reg_config, 1, SPI3_TIMEOUT);

	ReleaseChip();

	return status;
}

BSP_StatusTypeDef AD9834_Stop()
{
	BSP_StatusTypeDef status = BSP_OK;

	uint16_t tx_data[1];
	ClrBit(B28);
	SetBit(RESET);
	tx_data[0] = reg_config;
	SelectChip();
	status = HAL_SPI_Transmit(&hspi3, (uint8_t*)tx_data, 1, SPI3_TIMEOUT);
	ReleaseChip();
	HAL_Delay(20);

	return status;
}

BSP_StatusTypeDef AD9834_Start()
{
	BSP_StatusTypeDef status = BSP_OK;
	uint16_t tx_data[1];
	SetBit(B28);
	ClrBit(RESET);
	tx_data[0] = reg_config;

	SelectChip();
	status = HAL_SPI_Transmit(&hspi3, (uint8_t*)tx_data, 1, SPI3_TIMEOUT);
	ReleaseChip();
	HAL_Delay(20);
	return status;
}

BSP_StatusTypeDef AD9834_SetFrequency(uint32_t freq28)
{
	BSP_StatusTypeDef status = BSP_OK;
	uint16_t msb14 = 0;
	uint16_t lsb14 = 0;
	uint16_t tx_data[3] = {0};

    lsb14 = (uint16_t) (freq28 & 0x3FFF);
    msb14 = (uint16_t) ((freq28 & 0xFFFC000) >> 14);

    lsb14 |= FREQ0_ADDR;
    msb14 |= FREQ0_ADDR;

    ClrBit(FSEL);
    SetBit(B28);
    SetBit(RESET);

    tx_data[0] = reg_config;
    tx_data[1] = lsb14;
    tx_data[2] = msb14;

    SelectChip();
	status = HAL_SPI_Transmit(&hspi3, (uint8_t*)tx_data, 3, SPI3_TIMEOUT);
	ReleaseChip();
	HAL_Delay(20);


	return status;
}
