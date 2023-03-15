/*
 * DDS.h
 *
 *  Created on: Mar 11, 2023
 *      Author: grzegorz
 */

#ifndef THIRD_PARTY_BSP_INC_DDS_H_
#define THIRD_PARTY_BSP_INC_DDS_H_

#include "bsp.h"

typedef enum
{
	DDS_DIV0		= 0U,
	DDS_DIV2		= 2U,
	DDS_DIV4		= 4U,
	DDS_DIV8		= 8U,
	DDS_DIV10		= 10U
} dds_clk_div_e;

#define DDS_DIV0_RES		0.0610351
#define DDS_DIV2_RES		0.0305176
#define DDS_DIV4_RES		0.0203438
#define DDS_DIV8_RES		0.0122070
#define DDS_DIV10_RES		0.0012207
#define AT_0dBV				0
#define AT_10dBV			10
#define AT_20dBV			20
#define AT_30dBV			30

BSP_StatusTypeDef DDS_SetFrequency(float freq);
void DDS_Attenuation(uint8_t attenuation);
void DDS_ClockDivider(dds_clk_div_e clk_div);

#endif /* THIRD_PARTY_BSP_INC_DDS_H_ */
