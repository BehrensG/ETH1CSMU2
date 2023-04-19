/*
 * GPIO.h
 *
 *  Created on: Mar 10, 2023
 *      Author: grzegorz
 */

#ifndef THIRD_PARTY_BSP_INC_GPIO_H_
#define THIRD_PARTY_BSP_INC_GPIO_H_

#include <BSP.h>

#define GPIO_ON		1
#define GPIO_OFF	0

typedef enum
{
	NONE = 0,
	CURR_SENS_1R,
	CURR_SENS_10R,
	CURR_SENS_100R,
	CURR_SENS_1kR,
	CXN_REL1,
	CXN_REL2,
	CXN_REL3,
	CXN_REL4,
	CXN_REL5,
	CXN_REL6
}gpio_state;

#endif /* THIRD_PARTY_BSP_INC_GPIO_H_ */
