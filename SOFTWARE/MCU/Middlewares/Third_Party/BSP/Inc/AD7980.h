/*
 * AD7980.h
 *
 *  Created on: Apr 18, 2023
 *      Author: grzegorz
 */

#ifndef THIRD_PARTY_BSP_INC_AD7980_H_
#define THIRD_PARTY_BSP_INC_AD7980_H_

#include "bsp.h"

#define AD7980_VOLT_CH		0
#define AD7980_CURR_CH		1

#define AD7980_FSR_CENTER	0x8000
#define AD7980_LSB			7.62939453125E-5

HAL_StatusTypeDef AD7980_ReadData(uint16_t* rx_data);
float* AD7980_RXDataToVoltage(uint16_t* rx_data);


#endif /* THIRD_PARTY_BSP_INC_AD7980_H_ */
