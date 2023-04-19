/*
 * 74HC595.h
 *
 *  Created on: Mar 10, 2023
 *      Author: grzegorz
 */

#ifndef THIRD_PARTY_BSP_INC_74HC595_H_
#define THIRD_PARTY_BSP_INC_74HC595_H_

#include <BSP.h>

#define number_of_registers    2

typedef enum
{
  LOW595 = 0,
  HIGH595
}PinState595;

typedef enum
{
  LOW = 0,
  HIGH
}bool_t;


#define	SR0_C_G100		0x01
#define	SR0_C_G1		0x02
#define	SR0_C_G10		0x04
#define	SR0_V_AZ		0x08
#define	SR0_V_G100		0x10
#define	SR0_V_G1		0x20
#define	SR0_V_G10		0x40
#define	SR0_C_AZ		0x80

#define	SR1_MCU_ENA		0x01
#define	SR1_VMEAS_SEL	0x02
#define	SR1_SIGN_SEL	0x04
#define SR1_ATT_A0		0x08
#define SR1_ATT_A1		0x10
#define SR1_FGEN_LPF	0x20
#define SR_ADC_SEL		0x40

#define	SR_INVERT_MASK	0xFF

#define SR0				0
#define SR1				1

void SerialDataPinSet(PinState595 state);
void ClockPinSet(PinState595 state);
void LatchPinSet(PinState595 state);
void SN74HC595_Clear(uint8_t* shift_reg);
void SN74HC595_SetAll(bool_t val, uint8_t* shift_reg);
void SN74HC595_SetPin(int32_t index, bool_t val, uint8_t* shift_reg);
void SN74HC595_Update(uint8_t* shift_reg);
void SN74HC595_Init();


#endif /* THIRD_PARTY_BSP_INC_74HC595_H_ */
