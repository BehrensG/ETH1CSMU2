/*
 * eeprom.c
 *
 *  Created on: Feb 10, 2023
 *      Author: grzegorz
 */


#include <math.h>
#include <stdio.h>
#include <stdlib.h>

#include "eeprom.h"

void EEPROM_WriteProtect(GPIO_PinState state);


BSP_StatusTypeDef EEPROM_Erase()
{

	EEPROM_WriteProtect(GPIO_PIN_SET);

	if(ee24_isConnected(EEPROM_ADDRESS))
	{
		if(ee24_eraseChip(EEPROM_ADDRESS))
		{
			EEPROM_WriteProtect(GPIO_PIN_RESET);
			return BSP_OK;
		}
		else
		{
			EEPROM_WriteProtect(GPIO_PIN_RESET);
			return BSP_EEPROM_WRITE_ERROR;
		}
	}
	else
	{
		EEPROM_WriteProtect(GPIO_PIN_RESET);
		return BSP_EEPROM_NO_CONNECTION;
	}


}

void EEPROM_WriteProtect(GPIO_PinState state)
{
	if(GPIO_PIN_SET == state)
	{
		LL_GPIO_SetOutputPin(EEPROM_WP_GPIO_Port, EEPROM_WP_Pin);
	} else if (GPIO_PIN_RESET == state)
	{
		LL_GPIO_ResetOutputPin(EEPROM_WP_GPIO_Port, EEPROM_WP_Pin);
	}

}

BSP_StatusTypeDef EEPROM_Write(bsp_eeprom_union_t* union_data, size_t size)
{
	uint8_t tx_data = EEPROM_WRITE_DONE;


	EEPROM_WriteProtect(GPIO_PIN_RESET);
	if(ee24_isConnected(EEPROM_ADDRESS))
	{

		if(ee24_write(EEPROM_ADDRESS, 0, union_data->bytes, size))
		{

			if(ee24_write(EEPROM_ADDRESS, EEPROM_END, &tx_data, 1))
			{
				EEPROM_WriteProtect(GPIO_PIN_SET);
				return BSP_OK;
			}
			else
			{
				EEPROM_WriteProtect(GPIO_PIN_SET);
				return BSP_EEPROM_WRITE_ERROR;
			}

		}
		else
		{
			EEPROM_WriteProtect(GPIO_PIN_SET);
			return BSP_EEPROM_WRITE_ERROR;
		}

	}
	else
	{
		EEPROM_WriteProtect(GPIO_PIN_SET);
		return BSP_EEPROM_NO_CONNECTION;
	}
}

BSP_StatusTypeDef EEPROM_Read(bsp_eeprom_union_t* union_data, size_t size)
{
	EEPROM_WriteProtect(GPIO_PIN_RESET);

	if(ee24_isConnected(EEPROM_ADDRESS))
	{
		if(ee24_read(EEPROM_ADDRESS, 0, union_data->bytes, size))
		{
			EEPROM_WriteProtect(GPIO_PIN_SET);
			return BSP_OK;
		}
		else
		{
			EEPROM_WriteProtect(GPIO_PIN_SET);
			return BSP_EEPROM_READ_ERROR;
		}

	}
	else
	{
		EEPROM_WriteProtect(GPIO_PIN_SET);
		return BSP_EEPROM_NO_CONNECTION;
	}
}

BSP_StatusTypeDef EEPROM_Status()
{
	uint8_t rx_data = 0;

	EEPROM_WriteProtect(GPIO_PIN_RESET);

	if(ee24_isConnected(EEPROM_ADDRESS))
	{
		if(ee24_read(EEPROM_ADDRESS, EEPROM_END, &rx_data, 1))
		{
			if(EEPROM_WRITE_DONE == rx_data)
			{
				EEPROM_WriteProtect(GPIO_PIN_SET);
				return BSP_OK;
			}
			else
			{
				EEPROM_WriteProtect(GPIO_PIN_SET);
				return BSP_EEPROM_EMPTY;
			}

		}
		else
		{
			EEPROM_WriteProtect(GPIO_PIN_SET);
			return BSP_EEPROM_READ_ERROR;
		}

	}
	else
	{
		EEPROM_WriteProtect(GPIO_PIN_SET);
		return BSP_EEPROM_NO_CONNECTION;
	}
}
