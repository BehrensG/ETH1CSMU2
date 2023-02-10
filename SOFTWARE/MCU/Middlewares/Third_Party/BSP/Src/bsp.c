/*
 * bsp.c
 *
 *  Created on: Feb 10, 2023
 *      Author: grzegorz
 */

#include <string.h>

#include "bsp.h"
#include "scpi_def.h"
#include "eeprom.h"

struct _bsp bsp;

static void BSP_Init_Common()
{

	bsp.trigger.delay = 0;
	bsp.trigger.in_slope = POS;
	bsp.trigger.out_slope = POS;
	bsp.trigger.source = TRG_IMM;
	bsp.trigger.count = 0;
	bsp.data_format = DATA_FORMAT_ASCII;
	bsp.security.status = 1;

}

void BSP_Init_DefualtEEPROM()
{
	bsp.eeprom.structure.ip4.MAC[0] = MAC_0;
	bsp.eeprom.structure.ip4.MAC[1] = MAC_1;
	bsp.eeprom.structure.ip4.MAC[2] = MAC_2;
	bsp.eeprom.structure.ip4.MAC[3] = MAC_3;
	bsp.eeprom.structure.ip4.MAC[4] = MAC_4;
	bsp.eeprom.structure.ip4.MAC[5] = MAC_5;

	bsp.eeprom.structure.ip4.gateway[0] = GATEWAY_ADDRESS_0;
	bsp.eeprom.structure.ip4.gateway[1] = GATEWAY_ADDRESS_1;
	bsp.eeprom.structure.ip4.gateway[2] = GATEWAY_ADDRESS_2;
	bsp.eeprom.structure.ip4.gateway[3] = GATEWAY_ADDRESS_3;

	bsp.eeprom.structure.ip4.ip[0] = IP_ADDRESS_0;
	bsp.eeprom.structure.ip4.ip[1] = IP_ADDRESS_1;
	bsp.eeprom.structure.ip4.ip[2] = IP_ADDRESS_2;
	bsp.eeprom.structure.ip4.ip[3] = IP_ADDRESS_3;

	bsp.eeprom.structure.ip4.netmask[0] = NETMASK_ADDRESS_0;
	bsp.eeprom.structure.ip4.netmask[1] = NETMASK_ADDRESS_1;
	bsp.eeprom.structure.ip4.netmask[2] = NETMASK_ADDRESS_2;
	bsp.eeprom.structure.ip4.netmask[3] = NETMASK_ADDRESS_3;


	bsp.eeprom.structure.calib_adc[0].gain = (float)1.0;
	bsp.eeprom.structure.calib_adc[0].offset = (float)0.0;
	bsp.eeprom.structure.calib_adc[0].valid = TRUE;
	bsp.eeprom.structure.calib_adc[1].gain = (float)1.0;
	bsp.eeprom.structure.calib_adc[1].offset = (float)0.0;
	bsp.eeprom.structure.calib_adc[1].valid = TRUE;
	bsp.eeprom.structure.calib_adc[2].gain = (float)1.0;
	bsp.eeprom.structure.calib_adc[2].offset = (float)0.0;
	bsp.eeprom.structure.calib_adc[2].valid = TRUE;

	strncpy(bsp.eeprom.structure.service_password, PASSWORD, PASSWORD_LENGTH);
	strncpy(bsp.eeprom.structure.info.manufacturer, SCPI_IDN1, SCPI_MANUFACTURER_STRING_LENGTH);
	strncpy(bsp.eeprom.structure.info.device, SCPI_IDN2, SCPI_DEVICE_STRING_LENGTH);
	strncpy(bsp.eeprom.structure.info.serial_number, SCPI_IDN4, SCPI_SERIALNUMBER_STRING_LENGTH);
	strncpy(bsp.eeprom.structure.info.software_version, SCPI_IDN3, SCPI_SOFTWAREVERSION_STRING_LENGTH);
	memset(bsp.eeprom.structure.calib_string, 0, sizeof(bsp.eeprom.structure.calib_string));

}

static void BSP_Init_IP4Current()
{
	bsp.ip4.MAC[0] = bsp.eeprom.structure.ip4.MAC[0];
	bsp.ip4.MAC[1] = bsp.eeprom.structure.ip4.MAC[1];
	bsp.ip4.MAC[2] = bsp.eeprom.structure.ip4.MAC[2];
	bsp.ip4.MAC[3] = bsp.eeprom.structure.ip4.MAC[3];
	bsp.ip4.MAC[4] = bsp.eeprom.structure.ip4.MAC[4];
	bsp.ip4.MAC[5] = bsp.eeprom.structure.ip4.MAC[5];

	bsp.ip4.gateway[0] = bsp.eeprom.structure.ip4.gateway[0];
	bsp.ip4.gateway[1] = bsp.eeprom.structure.ip4.gateway[1];
	bsp.ip4.gateway[2] = bsp.eeprom.structure.ip4.gateway[2];
	bsp.ip4.gateway[3] = bsp.eeprom.structure.ip4.gateway[3];

	bsp.ip4.ip[0] = bsp.eeprom.structure.ip4.ip[0];
	bsp.ip4.ip[1] = bsp.eeprom.structure.ip4.ip[1];
	bsp.ip4.ip[2] = bsp.eeprom.structure.ip4.ip[2];
	bsp.ip4.ip[3] = bsp.eeprom.structure.ip4.ip[3];

	bsp.ip4.netmask[0] = bsp.eeprom.structure.ip4.netmask[0];
	bsp.ip4.netmask[1] = bsp.eeprom.structure.ip4.netmask[1];
	bsp.ip4.netmask[2] = bsp.eeprom.structure.ip4.netmask[2];
	bsp.ip4.netmask[3] = bsp.eeprom.structure.ip4.netmask[3];
}

BSP_StatusTypeDef BSP_Init()
{
	BSP_StatusTypeDef eeprom_status;

	BSP_Init_Common();

	if(!(LL_GPIO_ReadInputPort(MCU_DEFAULT_GPIO_Port) & MCU_DEFAULT_Pin))
	{
		BSP_Init_DefualtEEPROM();
		BSP_Init_IP4Current();
		bsp.default_cfg = 1;
	}
	else
	{
		eeprom_status = EEPROM_Status();

		switch (eeprom_status)
		{
			case BSP_EEPROM_EMPTY:
			{
				BSP_Init_DefualtEEPROM();
				eeprom_status = EEPROM_Write(&bsp.eeprom, EEPROM_CFG_SIZE);
				eeprom_status = EEPROM_Read(&bsp.eeprom, EEPROM_CFG_SIZE);
				if(BSP_OK == eeprom_status)
				{
					BSP_Init_IP4Current();
					bsp.default_cfg = 0;
				}; break;
			}
			case BSP_OK:
			{
				eeprom_status = EEPROM_Read(&bsp.eeprom, EEPROM_CFG_SIZE);
				if(BSP_OK == eeprom_status)
				{
					BSP_Init_IP4Current();
					bsp.default_cfg = 0;
				}; break;
			}
			default:
			{
				BSP_Init_DefualtEEPROM();
				BSP_Init_IP4Current();
				bsp.default_cfg = 1;
			}; break;
		}

	}

	return eeprom_status;
}
