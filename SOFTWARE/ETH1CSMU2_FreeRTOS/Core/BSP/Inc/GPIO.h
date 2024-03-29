/*
 * GPIO.h
 *
 *  Created on: Mar 10, 2023
 *      Author: grzegorz
 */

#ifndef THIRD_PARTY_BSP_INC_GPIO_H_
#define THIRD_PARTY_BSP_INC_GPIO_H_

#include "BSP.h"
#include "74HC595.h"

#define GPIO_ON		1
#define GPIO_OFF	0

typedef enum
{
	CXN_NONE = 0,
	CXN_REL1,
	CXN_REL2,
	CXN_REL3,
	CXN_REL4,
	CXN_REL5,
	CXN_REL6
}cxn_gpio_select;

typedef enum
{
	DG419_NONE = 0,
	DG419_SIGN_SEL,
	DG419_VOLT_MEAS,
	DG419_VOLT_MEAS_SENS,
	DG419_VOLT_ZERO,
	DG419_CURR_ZERO,
	DG419_ADC1_SEL,
	DG419_ADC2_SEL
}dg419_gpio_select;



typedef enum
{
	AQY212_CURR_RANGE_200uA = 0,
	AQY212_CURR_RANGE_2mA,
	AQY212_CURR_RANGE_20mA,
	AQY212_CURR_RANGE_200mA
}aqy212_switch;

typedef enum
{
	DG444_GAIN_NONE = 0,
	DG444_GAIN_VOLT,
	DG444_GAIN_CURR
}dg444_gain_select;

void CXN_Relays_Control(cxn_gpio_select gpio, uint8_t state);
void CXN_Relays_AllOff();
void DG419_Switch(dg419_gpio_select dg419, uint8_t state);
void DG444_Switch(dg444_gain_select dg444, uint8_t gain);
void AQY212_Switch(aqy212_switch aqy212);

#endif /* THIRD_PARTY_BSP_INC_GPIO_H_ */
