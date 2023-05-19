/*
 * MAX5217.h
 *
 *  Created on: Mar 12, 2023
 *      Author: grzegorz
 */

#ifndef THIRD_PARTY_BSP_INC_MAX5217_H_
#define THIRD_PARTY_BSP_INC_MAX5217_H_

#include "BSP.h"

#define MAX5217_LSB		3.814697265625E-5
#define VOLT_DIV		100
#define VOLT_MID		1.25

#define	MAX5217_ADDR	0x38

#define CODE_LOAD		0x01
#define	CODE			0x02
#define LOAD			0x03
#define CODE_LOAD_M		0x05
#define CODE_M			0x06
#define USER_CONFIG		0x08
#define SW_RESET		0x09
#define SW_CLEAR		0x0A

void MAX5217_Init();
HAL_StatusTypeDef MAX5217_SetVoltage(float voltage);


#endif /* THIRD_PARTY_BSP_INC_MAX5217_H_ */
