/*
 * bsp.c
 *
 *  Created on: Feb 10, 2023
 *      Author: grzegorz
 */

#include <BSP.h>
#include <string.h>
#include <SCPI_Def.h>

#include "EEPROM.h"

struct bsp_t bsp;
bsp_eeprom_union_t eeprom_default;

static void BSP_Init_Common()
{

	bsp.trigger.delay = 0;
	bsp.trigger.in_slope = POS;
	bsp.trigger.out_slope = POS;
	bsp.trigger.source = TRG_IMM;
	bsp.trigger.count = 0;
	bsp.data_format = DATA_FORMAT_ASCII;
	bsp.security.status = 1;
	bsp.sn74hc595.shift_reg[0] = 0;
	bsp.sn74hc595.shift_reg[1] = 0;

	bsp.config.dc.gain = 3;
	bsp.config.dc.value = 0.0;

	bsp.config.fgen.gain = 2;
	bsp.config.fgen.offset = 0.0;
	bsp.config.fgen.amplitude = 0.0;
	bsp.config.fgen.frequency = 0.0;

	bsp.config.list.delay = 0;

	bsp.config.measure.enable = 0;

	bsp.config.curr_range.value = 0.2f;
	bsp.config.curr_range.index = 3;
	bsp.config.curr_range.resistor = 1.0;

	for(uint8_t x = 0; x < MAXROW; x++)
	{
		bsp.config.relay.state[x] = 0;
	}

	bsp.config.mode = DC;

	bsp.config.dc.range_index = 2;
	bsp.config.dc.range[0] = 0.1;
	bsp.config.dc.range[1] = 1;
	bsp.config.dc.range[2] = 10;

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

	bsp.eeprom.structure.calib.ad7980[0].gain[0] = 1.0;
	bsp.eeprom.structure.calib.ad7980[0].gain[1] = 1.0;
	bsp.eeprom.structure.calib.ad7980[0].gain[2] = 1.0;

	bsp.eeprom.structure.calib.ad7980[1].gain[0] = 1.0;
	bsp.eeprom.structure.calib.ad7980[1].gain[1] = 1.0;
	bsp.eeprom.structure.calib.ad7980[1].gain[2] = 1.0;

	bsp.eeprom.structure.calib.ads8681[0].gain[0] = 1.0;
	bsp.eeprom.structure.calib.ads8681[0].gain[1] = 1.0;
	bsp.eeprom.structure.calib.ads8681[0].gain[2] = 1.0;

	bsp.eeprom.structure.calib.ads8681[1].gain[0] = 1.0;
	bsp.eeprom.structure.calib.ads8681[1].gain[1] = 1.0;
	bsp.eeprom.structure.calib.ads8681[1].gain[2] = 1.0;

	bsp.eeprom.structure.calib.count = 0;

	bsp.eeprom.structure.calib.dac8565.vout_a[0] = 1.0;
	bsp.eeprom.structure.calib.dac8565.vout_a[1] = 1.0;
	bsp.eeprom.structure.calib.dac8565.vout_a[2] = 1.0;

	bsp.eeprom.structure.calib.dac8565.offset_a[0] = 0.0027;
	bsp.eeprom.structure.calib.dac8565.offset_a[1] = 0.002;
	bsp.eeprom.structure.calib.dac8565.offset_a[2] = 0.0;

	bsp.eeprom.structure.calib.dac8565.vout_b[0] = 1.0;
	bsp.eeprom.structure.calib.dac8565.vout_b[1] = 1.0;
	bsp.eeprom.structure.calib.dac8565.vout_b[2] = 1.0;

	bsp.eeprom.structure.calib.dac8565.offset_b[0] = -0.0002;
	bsp.eeprom.structure.calib.dac8565.offset_b[1] = 0.0;
	bsp.eeprom.structure.calib.dac8565.offset_b[2] = 0.0;

	bsp.eeprom.structure.calib.dac8565.zero_offset = 0.0;

	bsp.eeprom.structure.calib.dac8565.vout_c[0] = 1.0;
	bsp.eeprom.structure.calib.dac8565.vout_c[1] = 1.0;
	bsp.eeprom.structure.calib.dac8565.vout_c[2] = 1.0;

	bsp.eeprom.structure.calib.dac8565.vout_d[0] = 1.0;
	bsp.eeprom.structure.calib.dac8565.vout_d[1] = 1.0;
	bsp.eeprom.structure.calib.dac8565.vout_d[2] = 1.0;

	bsp.eeprom.structure.calib.fgen.amplitude_gain = 1.0;
	bsp.eeprom.structure.calib.fgen.offset_gain = 1.0;
	bsp.eeprom.structure.calib.fgen.zero_offset = 0.0;

	strncpy(bsp.eeprom.structure.service.password, PASSWORD, STRING_LENGTH);
	strncpy(bsp.eeprom.structure.info.serial_number, SCPI_IDN4, STRING_LENGTH);
	strncpy(bsp.eeprom.structure.info.software_version, SCPI_IDN3, STRING_LENGTH);
	memset(bsp.eeprom.structure.calib.string, 0, sizeof(bsp.eeprom.structure.calib.string));

	eeprom_default = bsp.eeprom;

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
	BSP_Init_DefualtEEPROM();

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

