/*
 * bsp.h
 *
 *  Created on: Feb 10, 2023
 *      Author: grzegorz
 */

#ifndef THIRD_PARTY_BSP_INC_BSP_H_
#define THIRD_PARTY_BSP_INC_BSP_H_

#include "main.h"

#define MAXROW 6    /* maximum number of rows */
#define MAXCOL 1    /* maximum number of columns */
#define MAXDIM 1    /* maximum number of dimensions */

/*************************************** ETHERNET ***************************************/

#define IP_ADDRESS_0 192
#define IP_ADDRESS_1 168
#define IP_ADDRESS_2 1
#define IP_ADDRESS_3 123

#define NETMASK_ADDRESS_0 255
#define NETMASK_ADDRESS_1 255
#define NETMASK_ADDRESS_2 255
#define NETMASK_ADDRESS_3 0

#define GATEWAY_ADDRESS_0 192
#define GATEWAY_ADDRESS_1 168
#define GATEWAY_ADDRESS_2 1
#define GATEWAY_ADDRESS_3 1

#define MAC_0 0x00
#define MAC_1 0x80
#define MAC_2 0xE1
#define MAC_3 0x00
#define MAC_4 0x00
#define MAC_5 0x00

#define TCPIP_DEFAULT_PORT 2000

typedef enum
{
  BSP_OK       				= 0x00U,
  BSP_ERROR    				= 0x01U,
  BSP_BUSY     				= 0x02U,
  BSP_TIMEOUT  				= 0x03U,
  BSP_ADC_CONFIG_ERROR 		= 0x04U,
  BSP_EEPROM_EMPTY 			= 0x05U,
  BSP_EEPROM_MAX_SIZE 		= 0x06U,
  BSP_EEPROM_NO_CONNECTION 	= 0x07U,
  BSP_EEPROM_WRITE_ERROR 	= 0x08U,
  BSP_EEPROM_READ_ERROR 	= 0x09U,
  BSP_MODULE_MISSING		= 0x0AU,
  BSP_CALIB_OUT_OF_RANGE	= 0x0BU
} BSP_StatusTypeDef;

#define EEPROM_CFG_SIZE 	120
#define STRING_LENGTH 		16

#define PASSWORD "ETH1CSMU2"

#pragma pack(push, 1)

// size 64
typedef struct bsp_scpi_info
{
	int8_t manufacturer[STRING_LENGTH];
	int8_t device[STRING_LENGTH];
	int8_t serial_number[STRING_LENGTH];
	int8_t software_version[STRING_LENGTH];

}bsp_scpi_info_t;

// size 20
typedef struct bsp_ip4_lan
{
	uint8_t ip[4];
	uint8_t netmask[4];
	uint8_t gateway[4];
	uint8_t MAC[6];
	uint16_t port;

}bsp_ip4_lan_t;

typedef union bsp_eeprom_union
{
	struct data
	{
		// Size 20
		bsp_ip4_lan_t ip4;
		// Size 64
		bsp_scpi_info_t info;
		// Size 16
		int8_t password[STRING_LENGTH];
		// Size 16
		int8_t calib_string[STRING_LENGTH];
		// Size 4
		uint32_t calib_count;

	}structure;
	uint8_t bytes[EEPROM_CFG_SIZE];

}bsp_eeprom_union_t;

#pragma pack(pop)

// size 17
typedef struct bsp_security
{
	uint8_t status;

}bsp_security_t;


typedef struct bsp_trigger
{

	uint8_t in_slope;
	uint8_t out_slope;
	uint32_t delay;
	uint8_t source;
	uint32_t count;

}bsp_trigger_t;

typedef struct bsp_temperature
{
	uint8_t unit;

}bsp_temperature_t;

typedef struct _bsp_config_relay
{
	uint8_t state[MAXROW];

}bsp_config_relay_t;

typedef struct _bsp_config
{
	float frequency;
	float voltage;
	uint16_t volt_gain;
	uint8_t volt_gain_index;
	uint16_t curr_gain;
	uint8_t curr_gain_index;
	uint32_t resistor_value;
	uint8_t resistor_index;
	uint8_t adc_select;
	uint8_t function;
	bsp_config_relay_t relay;
	uint8_t format1;
	uint8_t format2;

}bsp_config_t;

typedef struct _bsp_dds
{
	uint8_t divider;
}bsp_dds_t;

typedef struct _bsp_adc_ads8681
{
	float zero_offset;
	uint8_t range;
}bsp_adc_ads8681_t;

typedef struct _bsp_sn74hc595_t
{
	uint8_t shift_reg[2];
}bsp_sn74hc595_t;

struct _bsp
{
	bsp_eeprom_union_t eeprom;
	bsp_trigger_t trigger;
	bsp_security_t security;
	bsp_temperature_t temperature;
	bsp_ip4_lan_t ip4;
	uint8_t default_cfg;
	uint8_t data_format;
	bsp_config_t config;
	bsp_dds_t dds;
	bsp_adc_ads8681_t ads8681[2];
	bsp_sn74hc595_t sn74hc595;
};

enum trigger_enum
{
	TRG_IMM = 1,
	TRG_EXT = 2,
	TRG_BUS = 3,
	TRG_OUT = 4
};

enum trigger_slope_enum
{
	POS = 1,
	NEG = 2
};

enum format_data_enum
{
	DATA_FORMAT_ASCII = 0,
	DATA_FORMAT_REAL = 1
};

#endif /* THIRD_PARTY_BSP_INC_BSP_H_ */
