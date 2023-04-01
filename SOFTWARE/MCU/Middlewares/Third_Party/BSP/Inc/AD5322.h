/*
 * AD5322.h
 *
 *  Created on: Mar 16, 2023
 *      Author: grzegorz
 */

#ifndef THIRD_PARTY_BSP_INC_AD5322_H_
#define THIRD_PARTY_BSP_INC_AD5322_H_

#include "bsp.h"

#define AD5322_VOUTA_LSB		3.0517578125E-4
#define AD5322_VOUTB_LSB		6.103515625E-4

#define AD5322_VOLTB_REF		2.5
#define AD5322_VOLTA_REF		1.25
#define AD5322_OFFSET_ERR		0.02
#define AD5322_VOLTA_GAIN		8
#define AD5322_VOLTB_GAIN		9.6 // U915 gain

#define AD5322_VOLTA_MAX_VAL	9.6
#define AD5322_VOLTB_MAX_VAL	12 // U915 gain


#define AD5322_DACB_ENABLE		0x8000


HAL_StatusTypeDef AD5322_Init();
HAL_StatusTypeDef AD5322_SetVOUTA(float voltage);
HAL_StatusTypeDef AD5322_SetVOUTB(float voltage);


#endif /* THIRD_PARTY_BSP_INC_AD5322_H_ */
