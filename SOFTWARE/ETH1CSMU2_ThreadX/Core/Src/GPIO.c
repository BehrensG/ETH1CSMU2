
#include "GPIO.h"

void CXN_Relays_Control(gpio_state gpio, uint8_t state)
{
	switch(gpio)
	{
		case CXN_REL1: (GPIO_ON == state) ? LL_GPIO_SetOutputPin(CXN_REL1_GPIO_Port, CXN_REL1_Pin) : LL_GPIO_ResetOutputPin(CXN_REL1_GPIO_Port, CXN_REL1_Pin); break;
		case CXN_REL2: (GPIO_ON == state) ? LL_GPIO_SetOutputPin(CXN_REL2_GPIO_Port, CXN_REL2_Pin) : LL_GPIO_ResetOutputPin(CXN_REL2_GPIO_Port, CXN_REL2_Pin); break;
		case CXN_REL3: (GPIO_ON == state) ? LL_GPIO_SetOutputPin(CXN_REL3_GPIO_Port, CXN_REL3_Pin) : LL_GPIO_ResetOutputPin(CXN_REL3_GPIO_Port, CXN_REL3_Pin); break;
		case CXN_REL4: (GPIO_ON == state) ? LL_GPIO_SetOutputPin(CXN_REL4_GPIO_Port, CXN_REL4_Pin) : LL_GPIO_ResetOutputPin(CXN_REL4_GPIO_Port, CXN_REL4_Pin); break;
		case CXN_REL5: (GPIO_ON == state) ? LL_GPIO_SetOutputPin(CXN_REL5_GPIO_Port, CXN_REL5_Pin) : LL_GPIO_ResetOutputPin(CXN_REL5_GPIO_Port, CXN_REL5_Pin); break;
		case CXN_REL6: (GPIO_ON == state) ? LL_GPIO_SetOutputPin(CXN_REL6_GPIO_Port, CXN_REL6_Pin) : LL_GPIO_ResetOutputPin(CXN_REL6_GPIO_Port, CXN_REL6_Pin); break;
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


void AQY212_Photomos(gpio_state gpio, uint8_t state)
{
}
