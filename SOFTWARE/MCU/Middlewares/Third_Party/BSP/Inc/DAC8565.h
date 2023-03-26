/*
 * DAC8565.h
 *
 *  Created on: Mar 26, 2023
 *      Author: grzegorz
 */

#ifndef THIRD_PARTY_BSP_INC_DAC8565_H_
#define THIRD_PARTY_BSP_INC_DAC8565_H_

#include "bsp.h"

#define DAC8565_BUFFA		0x00
#define DAC8565_BUFFB		0x02
#define DAC8565_BUFFC		0x04
#define DAC8565_BUFFD		0x06

#define DAC8565_VOUTA		0x10
#define DAC8565_VOUTB		0x12
#define DAC8565_VOUTC		0x14
#define DAC8565_VOUTD		0x16
#define DAC8565_VOUTALL		0x34

#define DAC8565_VREF		4.096
#define DAC8565_VOUT_LSB	6.25E-5


typedef enum
{
	VOUTA,
	VOUTB,
	VOUTC,
	VOUTD,
	ALL
}DAC8565_ChannelSelect;


void DAC8565_Init();
HAL_StatusTypeDef DAC8565_SetVOUT(DAC8565_ChannelSelect channel, float voltage);

#endif /* THIRD_PARTY_BSP_INC_DAC8565_H_ */
