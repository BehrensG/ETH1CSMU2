/*
 * FGEN.h
 *
 *  Created on: Mar 11, 2023
 *      Author: grzegorz
 */

#ifndef THIRD_PARTY_BSP_INC_FGEN_H_
#define THIRD_PARTY_BSP_INC_FGEN_H_

#include "BSP.h"

typedef enum
{
	FGEN_DIV0		= 0U,
	FGEN_DIV2		= 2U,
	FGEN_DIV4		= 4U,
	FGEN_DIV8		= 8U,
	FGEN_DIV10		= 10U
} dds_clk_div_e;

#define FGEN_DIV0_RES		0.0610351
#define FGEN_DIV2_RES		0.0305176
#define FGEN_DIV4_RES		0.0203438
#define FGEN_DIV8_RES		0.0122070
#define FGEN_DIV10_RES		0.0012207
#define AT_0dBV				0
#define AT_10dBV			10
#define AT_20dBV			20
#define AT_30dBV			30

#define FGEN_OFFSET_MAX		6.0
#define FGEN_AMPL_MAX		9.6


BSP_StatusTypeDef FGEN_SetFrequency(float freq);
BSP_StatusTypeDef FGEN_SetAmplitude(float amplitude);
BSP_StatusTypeDef FGEN_SetOffset(float offset);
BSP_StatusTypeDef FGEN_Init();

void FGEN_Attenuation(uint8_t attenuation);
void FGEN_ClockDivider(dds_clk_div_e clk_div);

#endif /* THIRD_PARTY_BSP_INC_FGEN_H_ */
