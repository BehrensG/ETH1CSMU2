/*
 * DWT_Delay.c
 *
 *  Created on: Feb 5, 2023
 *      Author: grzegorz
 */

#include "Delay.h"
#include "main.h"          // change to whatever MCU you use

extern TIM_HandleTypeDef htim3;

void TIM_DelayInit()
{
	HAL_TIM_Base_Start(&htim3);
}

void TIM_Delay_us(uint16_t us)
{
	if(us)
	{
		__HAL_TIM_SET_COUNTER(&htim3, 0);
		while (__HAL_TIM_GET_COUNTER(&htim3) < us);
	}
}
