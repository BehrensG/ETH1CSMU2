/*
 * AD9834.h
 *
 *  Created on: Mar 11, 2023
 *      Author: grzegorz
 */

#ifndef THIRD_PARTY_BSP_INC_AD9834_H_
#define THIRD_PARTY_BSP_INC_AD9834_H_

#include "BSP.h"

#define B28         0x2000    /*set to true here (frequency is 28 bits wide)*/
#define HLB         0x1000    /*ignored since B28 == true*/
#define FSEL        0x0800    /*select FREQ0 or FREQ1 registers*/
#define PSEL        0x0400    /*select PHASE0 or PHASE 1 registers*/
#define PIN_SW      0x0200    /*set to false here(functions are controlled by software, not by pins)*/
#define RESET       0x0100    /*active high; set DAC to mid scale*/
#define SLEEP1      0x0080    /*active high; suspend internal clock; DAC output remains at its present value*/
#define SLEEP12     0x0040    /*set to false here (DAC is always active)*/
#define OPBITEN     0x0020    /*active high; enable the SIGN_BIT_OUT pin*/
#define SIGN_PIB    0x0010    /*configure the SIGN_BIT_OUT*/
#define DIV2        0x0008    /*set to false, not used*/
#define MODE        0x0002    /*true = triangle output, false = sinusoidal output*/

#define FREQ0_ADDR  0x4000
#define FREQ1_ADDR  0x8000
#define PHASE0_ADDR 0xC000
#define PHASE1_ADDR 0xE000

#define SPI3_TIMEOUT 2000U

BSP_StatusTypeDef AD9834_Init(void);
BSP_StatusTypeDef AD9834_SetFrequency(uint32_t freq28);
BSP_StatusTypeDef AD9834_SetPhase(uint16_t word12);
BSP_StatusTypeDef AD9834_Stop(void);
BSP_StatusTypeDef AD9834_Start(void);

#endif /* THIRD_PARTY_BSP_INC_AD9834_H_ */
