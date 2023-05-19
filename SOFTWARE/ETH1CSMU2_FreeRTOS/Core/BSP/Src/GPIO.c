
#include "GPIO.h"

extern struct bsp_t bsp;

void CXN_Relays_Control(cxn_gpio_select gpio, uint8_t state)
{
	switch(gpio)
	{
		case CXN_REL1: (GPIO_ON == state) ? LL_GPIO_SetOutputPin(CXN_REL1_GPIO_Port, CXN_REL1_Pin) : LL_GPIO_ResetOutputPin(CXN_REL1_GPIO_Port, CXN_REL1_Pin); break;
		case CXN_REL2: (GPIO_ON == state) ? LL_GPIO_SetOutputPin(CXN_REL2_GPIO_Port, CXN_REL2_Pin) : LL_GPIO_ResetOutputPin(CXN_REL2_GPIO_Port, CXN_REL2_Pin); break;
		case CXN_REL3: (GPIO_ON == state) ? LL_GPIO_SetOutputPin(CXN_REL3_GPIO_Port, CXN_REL3_Pin) : LL_GPIO_ResetOutputPin(CXN_REL3_GPIO_Port, CXN_REL3_Pin); break;
		case CXN_REL4: (GPIO_ON == state) ? LL_GPIO_SetOutputPin(CXN_REL4_GPIO_Port, CXN_REL4_Pin) : LL_GPIO_ResetOutputPin(CXN_REL4_GPIO_Port, CXN_REL4_Pin); break;
		case CXN_REL5: (GPIO_ON == state) ? LL_GPIO_SetOutputPin(CXN_REL5_GPIO_Port, CXN_REL5_Pin) : LL_GPIO_ResetOutputPin(CXN_REL5_GPIO_Port, CXN_REL5_Pin); break;
		case CXN_REL6: (GPIO_ON == state) ? LL_GPIO_SetOutputPin(CXN_REL6_GPIO_Port, CXN_REL6_Pin) : LL_GPIO_ResetOutputPin(CXN_REL6_GPIO_Port, CXN_REL6_Pin); break;
		case CXN_NONE: ; break;
	}
}

void CXN_Relays_AllOff()
{
	LL_GPIO_ResetOutputPin(CXN_REL1_GPIO_Port, CXN_REL1_Pin);
	LL_GPIO_ResetOutputPin(CXN_REL2_GPIO_Port, CXN_REL2_Pin);
	LL_GPIO_ResetOutputPin(CXN_REL3_GPIO_Port, CXN_REL3_Pin);
	LL_GPIO_ResetOutputPin(CXN_REL4_GPIO_Port, CXN_REL4_Pin);
	LL_GPIO_ResetOutputPin(CXN_REL5_GPIO_Port, CXN_REL5_Pin);
	LL_GPIO_ResetOutputPin(CXN_REL6_GPIO_Port, CXN_REL6_Pin);
}


void DG419_Switch(dg419_gpio_select dg419, uint8_t state)
{
	uint8_t shift_reg[2];

	shift_reg[SR0] = bsp.sn74hc595.shift_reg[SR0];
	shift_reg[SR1] = bsp.sn74hc595.shift_reg[SR1];

	switch(dg419)
	{
		case DG419_SIGN_SEL: (state)? (shift_reg[SR1] &= ~(SR1_SIGN_SEL)) : (shift_reg[SR1] |= SR1_SIGN_SEL); break;
		case DG419_VOLT_MEAS: (state)? (shift_reg[SR1] |= SR1_VMEAS_SEL) : (shift_reg[SR1] &= ~(SR1_VMEAS_SEL)); break;
		case DG419_VOLT_MEAS_SENS: (state)? (shift_reg[SR1] &= ~(SR1_VMEAS_SEL)) : (shift_reg[SR1] |= SR1_VMEAS_SEL); break;
		case DG419_VOLT_ZERO: (state)? (shift_reg[SR0] &= ~(SR0_V_AZ)) : (shift_reg[SR0] |= SR0_V_AZ); break;
		case DG419_CURR_ZERO: (state)? (shift_reg[SR0] &= ~(SR0_C_AZ)) : (shift_reg[SR0] |= SR0_C_AZ); break;
		case DG419_ADC1_SEL: (state)? (shift_reg[SR1] |= SR1_ADC_SEL) : (shift_reg[SR1] &= ~(SR1_ADC_SEL)); break;
		case DG419_ADC2_SEL: (state)? (shift_reg[SR1] &= ~(SR1_ADC_SEL)) : (shift_reg[SR1] |= SR1_ADC_SEL); break;
		case DG419_NONE: ; break;
	}

	bsp.sn74hc595.shift_reg[SR0] = shift_reg[SR0];
	bsp.sn74hc595.shift_reg[SR1] = shift_reg[SR1];

	SN74HC595_Update(shift_reg);
}

void AQY212_Switch(aqy212_switch aqy212)
{
	switch(aqy212)
	{
		case AQY212_CURR_RANGE_200uA:
			{
				LL_GPIO_SetOutputPin(MCU_CURR_SENS_1kR_GPIO_Port, MCU_CURR_SENS_1kR_Pin);
				LL_GPIO_ResetOutputPin(MCU_CURR_SENS_100R_GPIO_Port, MCU_CURR_SENS_100R_Pin);
				LL_GPIO_ResetOutputPin(MCU_CURR_SENS_10R_GPIO_Port, MCU_CURR_SENS_10R_Pin);
				LL_GPIO_ResetOutputPin(MCU_CURR_SENS_1R_GPIO_Port, MCU_CURR_SENS_1R_Pin);
			}; break;
		case AQY212_CURR_RANGE_2mA:
			{
				LL_GPIO_SetOutputPin(MCU_CURR_SENS_100R_GPIO_Port, MCU_CURR_SENS_100R_Pin);
				LL_GPIO_ResetOutputPin(MCU_CURR_SENS_1kR_GPIO_Port, MCU_CURR_SENS_1kR_Pin);
				LL_GPIO_ResetOutputPin(MCU_CURR_SENS_10R_GPIO_Port, MCU_CURR_SENS_10R_Pin);
				LL_GPIO_ResetOutputPin(MCU_CURR_SENS_1R_GPIO_Port, MCU_CURR_SENS_1R_Pin);
			}; break;
		case AQY212_CURR_RANGE_20mA:
			{
				LL_GPIO_SetOutputPin(MCU_CURR_SENS_10R_GPIO_Port, MCU_CURR_SENS_10R_Pin);
				LL_GPIO_ResetOutputPin(MCU_CURR_SENS_100R_GPIO_Port, MCU_CURR_SENS_100R_Pin);
				LL_GPIO_ResetOutputPin(MCU_CURR_SENS_1kR_GPIO_Port, MCU_CURR_SENS_1kR_Pin);
				LL_GPIO_ResetOutputPin(MCU_CURR_SENS_1R_GPIO_Port, MCU_CURR_SENS_1R_Pin);
			}; break;
		case AQY212_CURR_RANGE_200mA:
			{
				LL_GPIO_SetOutputPin(MCU_CURR_SENS_1R_GPIO_Port, MCU_CURR_SENS_1R_Pin);
				LL_GPIO_ResetOutputPin(MCU_CURR_SENS_100R_GPIO_Port, MCU_CURR_SENS_100R_Pin);
				LL_GPIO_ResetOutputPin(MCU_CURR_SENS_10R_GPIO_Port, MCU_CURR_SENS_10R_Pin);
				LL_GPIO_ResetOutputPin(MCU_CURR_SENS_1kR_GPIO_Port, MCU_CURR_SENS_1kR_Pin);
			}; break;
	}
}

void DG444_Switch(dg444_gain_select dg444, uint8_t gain)
{
	uint8_t shift_reg[2];

	shift_reg[SR0] = bsp.sn74hc595.shift_reg[SR0];
	shift_reg[SR1] = bsp.sn74hc595.shift_reg[SR1];

	switch(dg444)
	{
		case DG444_GAIN_VOLT:
							if (1 == gain)
							{
								shift_reg[SR0] |= SR0_V_G1;
								shift_reg[SR0] &= ~(SR0_V_G10);
								shift_reg[SR0] &= ~(SR0_V_G100);
							}
							else if (10 == gain)
							{
								shift_reg[SR0] |= SR0_V_G10;
								shift_reg[SR0] &= ~(SR0_V_G1);
								shift_reg[SR0] &= ~(SR0_V_G100);
							}
							else if (100 == gain)
							{
								shift_reg[SR0] |= SR0_V_G100;
								shift_reg[SR0] &= ~(SR0_V_G1);
								shift_reg[SR0] &= ~(SR0_V_G10);
							}; break;
		case DG444_GAIN_CURR:
							if (1 == gain)
							{
								shift_reg[SR0] |= SR0_C_G1;
								shift_reg[SR0] &= ~(SR0_C_G10);
								shift_reg[SR0] &= ~(SR0_C_G100);
							}
							else if (10 == gain)
							{
								shift_reg[SR0] |= SR0_C_G10;
								shift_reg[SR0] &= ~(SR0_C_G1);
								shift_reg[SR0] &= ~(SR0_C_G100);
							}
							else if (100 == gain)
							{
								shift_reg[SR0] |= SR0_C_G100;
								shift_reg[SR0] &= ~(SR0_C_G1);
								shift_reg[SR0] &= ~(SR0_C_G10);
							}; break;
		case DG444_GAIN_NONE: ; break;
	}

	bsp.sn74hc595.shift_reg[SR0] = shift_reg[SR0];
	bsp.sn74hc595.shift_reg[SR1] = shift_reg[SR1];

	SN74HC595_Update(shift_reg);
}
