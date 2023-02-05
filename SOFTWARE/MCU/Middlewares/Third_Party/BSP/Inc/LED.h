/*
 * LED.h
 *
 *  Created on: Feb 5, 2023
 *      Author: grzegorz
 */

#ifndef THIRD_PARTY_BSP_INC_LED_H_
#define THIRD_PARTY_BSP_INC_LED_H_

#include "main.h"

enum e_led
{
	LED_IDLE,
	LED_BUSY,
	LED_ERROR,
	LED_DEFUALT,
};

#define BLUE 2
#define RED 1
#define GREEN 0

#endif /* THIRD_PARTY_BSP_INC_LED_H_ */
