/*
 * 74HC595.c
 *
 *  Created on: Mar 10, 2023
 *      Author: grzegorz
 */


#include "74HC595.h"

extern struct _bsp bsp;

void SN74HC595_Delay()
{
	HAL_Delay(1);
}

//IO init
void SN74HC595_Init()
{
	uint8_t shift_reg[2];
	bsp.sn74hc595.shift_reg[SR0] = SR0_V_G1 | SR0_C_G1| SR0_V_AZ;
	bsp.sn74hc595.shift_reg[SR1] = SR1_VMEAS_SEL | SR1_ATT_A0 | SR1_ATT_A1 | SR1_SIGN_SEL;

	shift_reg[SR0] = bsp.sn74hc595.shift_reg[SR0];
	shift_reg[SR1] = bsp.sn74hc595.shift_reg[SR1];

	SN74HC595_Update(shift_reg);

}

void SN74HC595_Update(uint8_t* shift_reg)
{
    int8_t i , j;
    LatchPinSet(LOW595);
    shift_reg[0] ^=SR_INVERT_MASK;
    shift_reg[1] ^=SR_INVERT_MASK;

    //iterate through the registers
    for(i = number_of_registers- 1; i >=  0; i--)
    {
        for(j = 8 - 1; j >=  0; j--)
        {
            ClockPinSet(LOW595);
            int val = shift_reg[i] & (1 << j);
            SerialDataPinSet((PinState595)val);
			SN74HC595_Delay();
            ClockPinSet(HIGH595);
        }
    }
		SN74HC595_Delay();
		LatchPinSet(HIGH595);
}

void SN74HC595_SetPin(int32_t index, bool_t val, uint8_t* shift_reg)
{
	int8_t byteIndex = index / 8;
	int8_t bitIndex = index % 8;
    uint8_t current_byte = shift_reg[byteIndex];

    current_byte &= ~(1 << bitIndex);   //clear the bit need to be set
    current_byte |= val << bitIndex;    //set the bit

    shift_reg[byteIndex] = current_byte;
}

void SN74HC595_SetAll(bool_t val, uint8_t* shift_reg)
{
	int8_t i;
    //set all register pins to val
    for(i = number_of_registers * 8 - 1; i >=  0; i--)
    {
        SN74HC595_SetPin(i, val, shift_reg);
    }
    SN74HC595_Update(shift_reg);
}

void SN74HC595_Clear(uint8_t* shift_reg){
    SN74HC595_SetAll(LOW, shift_reg);
}

void LatchPinSet(PinState595 state)
{
	if(GPIO_PIN_RESET == state)
	{
		LL_GPIO_ResetOutputPin(SR_LAT_GPIO_Port, SR_LAT_Pin);
	}else
	{
		LL_GPIO_SetOutputPin(SR_LAT_GPIO_Port, SR_LAT_Pin);
	}

   // HAL_GPIO_WritePin(SR_LAT_GPIO_Port, SR_LAT_Pin, (GPIO_PinState)state);
}

void ClockPinSet(PinState595 state)
{
	if(GPIO_PIN_RESET == state)
	{
		LL_GPIO_ResetOutputPin(SR_CLK_GPIO_Port, SR_CLK_Pin);
	}else
	{
		LL_GPIO_SetOutputPin(SR_CLK_GPIO_Port, SR_CLK_Pin);
	}
   // HAL_GPIO_WritePin(SR_CLK_GPIO_Port, SR_CLK_Pin, (GPIO_PinState)state);
}

void SerialDataPinSet(PinState595 state)
{
	if(GPIO_PIN_RESET == state)
	{
		LL_GPIO_ResetOutputPin(SR_DAT_GPIO_Port, SR_DAT_Pin);
	}else
	{
		LL_GPIO_SetOutputPin(SR_DAT_GPIO_Port, SR_DAT_Pin);
	}
   // HAL_GPIO_WritePin(SR_DAT_GPIO_Port, SR_DAT_Pin, (GPIO_PinState)state);
}
