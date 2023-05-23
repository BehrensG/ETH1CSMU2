/*
 * ADS8681.h
 *
 *  Created on: Feb 5, 2023
 *      Author: grzegorz
 */

#ifndef THIRD_PARTY_BSP_INC_ADS8681_H_
#define THIRD_PARTY_BSP_INC_ADS8681_H_

#include "BSP.h"

#define DEVICE_ID_REG 		0x00
#define RST_PWRCTL_REG		0x04
#define SDI_CTL_REG			0x08
#define SDO_CTL_REG			0x0C
#define DATAOUT_CTL_REG		0x10
#define RANGE_SEL_REG		0x14
#define ALARM_REG			0x20
#define ALARM_H_TH_REG		0x24
#define ALARM_L_TH_REG		0x28

#define CLEAR_HWORD			0xC0
#define READ_HWORD			0xC8
#define READ_BYTE			0x48
#define WRITE_HWORD			0xD0
#define WRITE_MSB			0xD2
#define WRITE_LSB			0xD4
#define SET_HWORD			0xD8

#define ADS8681_ID1			0x01
#define ADS8681_ID2			0x02
#define ADS8681_ID3			0x03
#define ADS8681_EXT_VREF 	4.096
#define ADS8681_FSR_CENTER	0x8000

#define ADS8681_RANGE_3VREF		0x00
#define ADS8681_RANGE_2_5VREF	0x01
#define ADS8681_RANGE_1_5VREF	0x02
#define ADS8681_RANGE_1_25VREF	0x03
#define ADS8681_RANGE_0_625VREF	0x04
#define ADC_COUNT				2

#define SPI_TIMEOUT			5000
#define SPI_MAX_DELAY		10000

BSP_StatusTypeDef ADS8681_Init();
BSP_StatusTypeDef ADS8681_RawData(uint16_t* raw_data);
BSP_StatusTypeDef ADS8681_SetRange(uint8_t* range);
HAL_StatusTypeDef ADS8681_ReadData(uint16_t count);

#endif /* THIRD_PARTY_BSP_INC_ADS8681_H_ */
