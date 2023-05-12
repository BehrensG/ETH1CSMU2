/*
 * scpi_system.h
 *
 *  Created on: Mar 17, 2023
 *      Author: grzegorz
 */

#ifndef THIRD_PARTY_BSP_INC_SCPI_SYSTEM_H_
#define THIRD_PARTY_BSP_INC_SCPI_SYSTEM_H_

#include "scpi/scpi.h"

#define SECURITY_ON 1
#define SECURITY_OFF 0
#define CURRENT 0
#define STATIC 1
#define DEFAULT 2
#define NET_STR_WRONG_FORMAT 1
#define NET_STR_WRONG_NUMBER 2
#define NET_STR_OK 0
#define ETH_PORT_MAX_VAL 65535

enum e_mcu
{
	MCU1 = 1,
	MCU2,
	MCU3
};

enum e_temp_units
{
	CELSIUS = 1,
	FAHRENHEIT,
	KELVIN
};

enum e_eeprom_states
{
	EEPROM_RESET = 1,
	EEPROM_DEFAULT,
};

scpi_result_t SCPI_SystemCommunicateLANDHCP(scpi_t * context);
scpi_result_t SCPI_SystemCommunicateLANDHCPQ(scpi_t * context);
scpi_result_t SCPI_SystemCommunicateLANIPAddress(scpi_t * context);
scpi_result_t SCPI_SystemCommunicateLANIPAddressQ(scpi_t * context);
scpi_result_t SCPI_SystemCommunicateLANIPSmask(scpi_t * context);
scpi_result_t SCPI_SystemCommunicateLANIPSmaskQ(scpi_t * context);
scpi_result_t SCPI_SystemCommunicateLANGateway(scpi_t * context);
scpi_result_t SCPI_SystemCommunicateLANGatewayQ(scpi_t * context);
scpi_result_t SCPI_SystemCommunicateLANMAC(scpi_t * context);
scpi_result_t SCPI_SystemCommunicateLANMACQ(scpi_t * context);
scpi_result_t SCPI_SystemCommunicateLANPort(scpi_t * context);
scpi_result_t SCPI_SystemCommunicateLANPortQ(scpi_t * context);
scpi_result_t SCPI_SystemCommunicationLanUpdate(scpi_t * context);
scpi_result_t SCPI_SystemSecureState(scpi_t * context);
scpi_result_t SCPI_SystemSecureStateQ(scpi_t * context);
scpi_result_t SCPI_SystemTemperatureQ(scpi_t * context);
scpi_result_t SCPI_SystemTemperatureUnit(scpi_t * context);
scpi_result_t  SCPI_SystemTemperatureUnitQ(scpi_t * context);
scpi_result_t SCPI_SystemHumidityQ(scpi_t * context);
scpi_result_t SCPI_SystemServiceEEPROM(scpi_t * context);
scpi_result_t SCPI_SystemServiceID(scpi_t * context);

#endif /* THIRD_PARTY_BSP_INC_SCPI_SYSTEM_H_ */
