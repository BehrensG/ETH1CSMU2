/*
 * DWT_Delay.h
 *
 *  Created on: Feb 5, 2023
 *      Author: grzegorz
 */

#ifndef THIRD_PARTY_BSP_INC_DWT_DELAY_H_
#define THIRD_PARTY_BSP_INC_DWT_DELAY_H_

#include <stdint.h>

#define DWT_DELAY_NEWBIE 0

void DWT_Init(void);
void DWT_Delay_us(uint32_t us);
void DWT_Delay_ns(uint32_t ns);

#endif /* THIRD_PARTY_BSP_INC_DWT_DELAY_H_ */
