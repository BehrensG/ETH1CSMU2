/*
 * scpi_system.c
 *
 *  Created on: Mar 17, 2023
 *      Author: grzegorz
 */

#include <SCPI_Def.h>
#include <SCPI_System.h>
#include "types.h"
#include "scpi/scpi.h"
#include "EEPROM.h"
#include "HDC1080.h"

extern I2C_HandleTypeDef hi2c3;
extern struct _bsp bsp;

scpi_choice_def_t LAN_state_select[] =
{
    {"CURRent", 1},
    {"STATic", 2},
    SCPI_CHOICE_LIST_END
};

scpi_choice_def_t temperature_unit_select[] =
{
    {"C", 1},
    {"F", 2},
    {"K", 3},
    SCPI_CHOICE_LIST_END
};

scpi_choice_def_t security_state_select[] =
{
    {"OFF", 0},
    {"ON", 1},
	{"0", 0},
	{"1", 1},
    SCPI_CHOICE_LIST_END
};

scpi_choice_def_t EEPROM_state_select[] =
{
    {"RESET", 1},
    {"DEFault", 2},
    SCPI_CHOICE_LIST_END
};

/*
 * @INFO:
 * Private function to convert a IP string (format nnnn.nnnn.nnnn.nnnn) to a array of uint8_t. The conversion is need for the lwIP Ethernet function.
 *
 */

static uint8_t SCPI_StringToIP4Array(const char* ip_string, uint8_t* ip_array)
{

    /* A pointer to the next digit to process. */
    const char* start;

    start = ip_string;
    for (uint8_t i = 0; i < 4; i++)
    {
        /* The digit being processed. */
        uint8_t c;
        /* The value of this byte. */
        uint16_t n = 0;
        while (1)
        {
            c = * start;
            start++;
            if (c >= '0' && c <= '9')
            {
                n *= 10;
                n += c - '0';
            }
            /* We insist on stopping at "." if we are still parsing
               the first, second, or third numbers. If we have reached
               the end of the numbers, we will allow any character. */
            else if ((i < 3 && c == '.') || i == 3)
            {
                break;
            }
            else
            {
                return NET_STR_WRONG_FORMAT;
            }
        }
        if (n >= 256)
        {
            return NET_STR_WRONG_NUMBER;
        }
        ip_array[i] = n;
    }

    return NET_STR_OK;
}

/*
 * @INFO:
 * Private function to convert a MAC string (format xx:xx:xx:xx:xx:xx or xx-xx-xx-xx-xx-xx) to a array of uint8_t. The conversion is need for the lwIP Ethernet function.
 *
 */

static uint8_t SCPI_StringToMACArray(const char* MAC_string, uint8_t* MAC_array)
{
    uint32_t values[6];

    if(6 == sscanf(MAC_string, "%x:%x:%x:%x:%x:%x%*c",
    &values[0], &values[1], &values[2],
    &values[3], &values[4], &values[5]))
    {
        for (uint8_t i = 0; i < 6; i++)
        MAC_array[i] = (uint8_t)values[i];
    }
    else if (6 == sscanf(MAC_string, "%x-%x-%x-%x-%x-%x%*c",
    &values[0], &values[1], &values[2],
    &values[3], &values[4], &values[5]))
    {
        for (uint8_t i = 0; i < 6; i++)
        MAC_array[i] = (uint8_t)values[i];
    }
    else
    {}

    return NET_STR_OK;
}

/*
 * SYSTem:COMMunicate:LAN:IPADdress "<address>"
 *
 * @INFO:
 * Assigns a static Internet Protocol (IP) address for the instrument. If DHCP is enabled (SYSTem:COMMunicate:LAN:DHCP ON), the specified static IP address is not used.
 *
 * @PARAMETERS:
 * 				"<address>"		"nnnn.nnnn.nnnn.nnnn" - where nnnn is a number from 0-255. Default "192.168.1.126".
 *
 * @NOTE:
 * If you change this setting, you must send SYSTem:COMMunicate:LAN:UPDate to activate the new setting.
 * This setting is non-volatile; it is not changed by power cycling, a Factory Reset (*RST).
 *
 */

scpi_result_t SCPI_SystemCommunicateLANIPAddress(scpi_t * context)
{
	char str[16] = {0};
	uint8_t numb[4] = {0};
	size_t len = 0;
	uint8_t conv_result = 0;

	if(!SCPI_ParamCopyText(context,(char*)str, 16, &len, TRUE))
	{
		return SCPI_RES_ERR;
	}

	conv_result = SCPI_StringToIP4Array(str, numb);

	switch(conv_result)
	{
	case NET_STR_OK:
	{
		bsp.ip4.ip[0] = numb[0];
		bsp.ip4.ip[1] = numb[1];
		bsp.ip4.ip[2] = numb[2];
		bsp.ip4.ip[3] = numb[3];
	}break;
	case NET_STR_WRONG_FORMAT: SCPI_ErrorPush(context, SCPI_ERROR_DATA_TYPE_ERROR); break;
	case NET_STR_WRONG_NUMBER: SCPI_ErrorPush(context, SCPI_ERROR_NUMERIC_DATA_NOT_ALLOWED); break;
	default: return SCPI_RES_ERR; break;
	}

	return SCPI_RES_OK;
}

/*
 * SYSTem:COMMunicate:LAN:IPADdress? [{CURRent|STATic}]
 *
 * @INFO:
 * Query the IP4 address. Result is a string. Typical return "192.168.1.126"
 *
 * @PARAMETERS:
 * 				CURRent		read the value currently being used by the instrument (default)
 * 				STATic		read the value currently stored in nonvolatile memory within the instrument
 *
 * @NOTE:
 * Readout may not be the actual address used by the instrument if DHCP is enabled.
 *
 */

scpi_result_t SCPI_SystemCommunicateLANIPAddressQ(scpi_t * context)
{
	int32_t value = 0;
	char str[16] = {0};

	if(!SCPI_ParamChoice(context, LAN_state_select, &value, FALSE))
	{
		return SCPI_RES_ERR;
	}

	if(CURRENT == value)
	{
		sprintf(str, "%d.%d.%d.%d", bsp.ip4.ip[0],
									bsp.ip4.ip[1],
									bsp.ip4.ip[2],
									bsp.ip4.ip[3]);
	}
	else if(STATIC == value)
	{
		sprintf(str, "%d.%d.%d.%d", bsp.eeprom.structure.ip4.ip[0],
									bsp.eeprom.structure.ip4.ip[1],
									bsp.eeprom.structure.ip4.ip[2],
									bsp.eeprom.structure.ip4.ip[3]);
	}

	SCPI_ResultMnemonic(context, (char*)str);
	return SCPI_RES_OK;
}

/*
 * SYSTem:COMMunicate:LAN:SMASk "<mask>"
 *
 * @INFO:
 * Assigns a subnet mask for the instrument to use in determining whether a client IP address is on the same local subnet.
 *
 * @PARAMETERS:
 * 				"<mask>"	"nnnn.nnnn.nnnn.nnnn" - where nnnn is a number from 0-255. Default "255.255.255.0".
 *
 * @NOTE:
 * A value of "0.0.0.0" or "255.255.255.255" indicates that subnetting is not being used.
 * If you change this setting, you must send SYSTem:COMMunicate:LAN:UPDate to activate the new setting.
 * This setting is non-volatile; it is not changed by power cycling, a Factory Reset (*RST).
 *
 */

scpi_result_t SCPI_SystemCommunicateLANIPSmask(scpi_t * context)
{
	char str[16] = {0};
	uint8_t numb[4] = {0};
	size_t len = 0;
	uint8_t conv_result = 0;

	if(!SCPI_ParamCopyText(context,(char*)str, 16, &len, TRUE))
	{
		return SCPI_RES_ERR;
	}

	conv_result = SCPI_StringToIP4Array(str, numb);

	switch(conv_result)
	{
	case NET_STR_OK:
	{
		bsp.ip4.netmask[0] = numb[0];
		bsp.ip4.netmask[1] = numb[1];
		bsp.ip4.netmask[2] = numb[2];
		bsp.ip4.netmask[3] = numb[3];
	}break;
	case NET_STR_WRONG_FORMAT: SCPI_ErrorPush(context, SCPI_ERROR_DATA_TYPE_ERROR); break;
	case NET_STR_WRONG_NUMBER: SCPI_ErrorPush(context, SCPI_ERROR_NUMERIC_DATA_NOT_ALLOWED); break;
	default: return SCPI_RES_ERR; break;
	}

	return SCPI_RES_OK;
}

/*
 * SYSTem:COMMunicate:LAN:SMASk? [{CURRent|STATic}]
 *
 * @INFO:
 * Query IP4 subnet mask. Result is a string. Typical return "255.255.255.0".
 *
 * @PARAMETERS:
 * 				CURRent		read the value currently being used by the instrument (default)
 * 				STATic		read the value currently stored in nonvolatile memory within the instrument
 *
 * @NOTE:
 * Readout may not be the actual mask used by the instrument if DHCP is enabled.
 *
 */

scpi_result_t SCPI_SystemCommunicateLANIPSmaskQ(scpi_t * context)
{
	int32_t value = 0;
	char str[16] = {0};

	if(!SCPI_ParamChoice(context, LAN_state_select, &value, FALSE))
	{
		value = CURRENT;
	}
	if(CURRENT == value)
	{
		sprintf(str, "%d.%d.%d.%d", bsp.ip4.netmask[0],
									bsp.ip4.netmask[1],
									bsp.ip4.netmask[2],
									bsp.ip4.netmask[3]);
	}
	else if(STATIC == value)
	{
		sprintf(str, "%d.%d.%d.%d", bsp.eeprom.structure.ip4.netmask[0],
									bsp.eeprom.structure.ip4.netmask[1],
									bsp.eeprom.structure.ip4.netmask[2],
									bsp.eeprom.structure.ip4.netmask[3]);
	}
	SCPI_ResultMnemonic(context, (char*)str);

	return SCPI_RES_OK;
}

/*
 * SYSTem:COMMunicate:LAN:GATEway "<gateway>"
 *
 * @INFO:
 * Assigns a gateway address for the instrument. A gateway IP refers to a device on a network which sends local network traffic to other networks.
 *
 * @PARAMETERS:
 * 				"<gateway>"	"nnnn.nnnn.nnnn.nnnn" - where nnnn is a number from 0-255. Default "192.168.1.1".
 *
 * @NOTE:
 * If you change this setting, you must send SYSTem:COMMunicate:LAN:UPDate to activate the new setting.
 *
 */

scpi_result_t SCPI_SystemCommunicateLANGateway(scpi_t * context)
{
	char gateway_str[16] = {0};
	uint8_t gateway_numb[4] = {0};
	size_t len = 0;
	uint8_t conv_result = 0;

	if(!SCPI_ParamCopyText(context,gateway_str, 16, &len, TRUE))
	{
		return SCPI_RES_ERR;
	}

	conv_result = SCPI_StringToIP4Array(gateway_str, gateway_numb);

	switch(conv_result)
	{
		case NET_STR_OK:
		{
			bsp.ip4.gateway[0] = gateway_numb[0];
			bsp.ip4.gateway[1] = gateway_numb[1];
			bsp.ip4.gateway[2] = gateway_numb[2];
			bsp.ip4.gateway[3] = gateway_numb[3];
		}break;
		case NET_STR_WRONG_FORMAT: SCPI_ErrorPush(context, SCPI_ERROR_DATA_TYPE_ERROR); break;
		case NET_STR_WRONG_NUMBER: SCPI_ErrorPush(context, SCPI_ERROR_NUMERIC_DATA_NOT_ALLOWED); break;
		default: return SCPI_RES_ERR; break;
	}

	return SCPI_RES_OK;
}

/*
 * SYSTem:COMMunicate:LAN:GATEway? [{CURRent|STATic}]
 *
 * @INFO:
 * Query the gateway address. Typical return "192.168.1.1".
 *
 */

scpi_result_t SCPI_SystemCommunicateLANGatewayQ(scpi_t * context)
{
	int32_t value = 0;
	char str[16] = {0};

	if(!SCPI_ParamChoice(context, LAN_state_select, &value, FALSE))
	{
		value = CURRENT;
	}
	if(CURRENT == value)
	{

		sprintf(str, "%d.%d.%d.%d", bsp.ip4.gateway[0],
									bsp.ip4.gateway[1],
									bsp.ip4.gateway[2],
									bsp.ip4.gateway[3]);
	}
	else if(STATIC == value)
	{
		sprintf(str, "%d.%d.%d.%d", bsp.eeprom.structure.ip4.gateway[0],
									bsp.eeprom.structure.ip4.gateway[1],
									bsp.eeprom.structure.ip4.gateway[2],
									bsp.eeprom.structure.ip4.gateway[3]);
	}

	SCPI_ResultMnemonic(context, (char*)str);

	return SCPI_RES_OK;
}

/*
 * SYSTem:COMMunicate:LAN:MAC "<MAC_address>"
 *
 * @INFO:
 * Assign a new MAC address to the device.
 *
 * @PARAMETERS:
 * 				"<MAC_address>"	"nn:nn:nn:nn:nn:nn" or "nn-nn-nn-nn-nn-nn" - where nn is a number from 00-FF.
 *
 * @NOTE:
 * To use this function the device must be first unlocked using the SYSTem:SECure:STATe command.
 *
 */

scpi_result_t SCPI_SystemCommunicateLANMAC(scpi_t * context)
{
	uint8_t str[18] = {0};
	uint8_t numb[6] = {0};
	size_t len = 0;
	uint8_t conv_result = 0;

	if(bsp.security.status)
	{
		SCPI_ErrorPush(context, SCPI_ERROR_SERVICE_MODE_SECURE);
		return SCPI_RES_ERR;
	}

	if(!SCPI_ParamCopyText(context,(char*)str, 18, &len, TRUE))
	{
		return SCPI_RES_ERR;
	}

	conv_result = SCPI_StringToMACArray(str, numb);

	switch(conv_result)
	{
		case NET_STR_OK:
		{
			bsp.ip4.MAC[0] = numb[0];
			bsp.ip4.MAC[1] = numb[1];
			bsp.ip4.MAC[2] = numb[2];
			bsp.ip4.MAC[3] = numb[3];
			bsp.ip4.MAC[4] = numb[4];
			bsp.ip4.MAC[5] = numb[5];
		}break;
		case NET_STR_WRONG_FORMAT: SCPI_ErrorPush(context, SCPI_ERROR_DATA_TYPE_ERROR); break;
		case NET_STR_WRONG_NUMBER: SCPI_ErrorPush(context, SCPI_ERROR_NUMERIC_DATA_NOT_ALLOWED); break;
		default: return SCPI_RES_ERR; break;
	}

	return SCPI_RES_OK;
}

/*
 * SYSTem:COMMunicate:LAN:MAC?
 *
 * @INFO:
 * Query the device MAC address. The default value is "00:80:E1:00:00:00".
 *
 */

scpi_result_t SCPI_SystemCommunicateLANMACQ(scpi_t * context)
{
	char str[18] = {0};

	if(!bsp.default_cfg)
	{
		sprintf(str, "%02x:%02x:%02x:%02x:%02x:%02x",	bsp.ip4.MAC[0],
														bsp.ip4.MAC[1],
														bsp.ip4.MAC[2],
														bsp.ip4.MAC[3],
														bsp.ip4.MAC[4],
														bsp.ip4.MAC[5]);
	}
	else
	{
		sprintf(str, "%02x:%02x:%02x:%02x:%02x:%02x",	bsp.eeprom.structure.ip4.MAC[0],
														bsp.eeprom.structure.ip4.MAC[1],
														bsp.eeprom.structure.ip4.MAC[2],
														bsp.eeprom.structure.ip4.MAC[3],
														bsp.eeprom.structure.ip4.MAC[4],
														bsp.eeprom.structure.ip4.MAC[5]);
	}

	SCPI_ResultMnemonic(context, (char*)str);

	return SCPI_RES_OK;
}

/*
 * SYSTem:COMMunicate:LAN:PORT <numeric_value>
 *
 * @INFO:
 * Set the TCP/IP port number.
 *
 * @PARAMETERS:
 * 				<numeric_value>		port value. Valid values are 0 - 65535. Default value is 2000.
 *
 * @NOTE:
 * If you change this setting, you must send SYSTem:COMMunicate:LAN:UPDate to activate the new setting.
 *
 */

scpi_result_t SCPI_SystemCommunicateLANPort(scpi_t * context)
{
    uint32_t port = 0;

    if(!SCPI_ParamUInt32(context, &port, TRUE))
    {
        return SCPI_RES_ERR;
    }

    if(port > ETH_PORT_MAX_VAL)
    {
        SCPI_ErrorPush(context, SCPI_ERROR_TOO_MANY_DIGITS);
        return SCPI_RES_ERR;
    }


    bsp.ip4.port = (uint16_t)port;

	return SCPI_RES_OK;
}

/*
 * SYSTem:COMMunicate:LAN:PORT?
 *
 * @INFO:
 * Query the TCP/IP port number. Typical result 2000.
 *
 */

scpi_result_t SCPI_SystemCommunicateLANPortQ(scpi_t * context)
{
	int32_t value = 0;

	if(!SCPI_ParamChoice(context, LAN_state_select, &value, TRUE))
	{
		return SCPI_RES_ERR;
	}

	if(CURRENT == value)
	{
		SCPI_ResultUInt16(context,bsp.ip4.port);
	}
	else if(STATIC == value)
	{
		SCPI_ResultUInt16(context,bsp.eeprom.structure.ip4.port);
	}

	return SCPI_RES_OK;
}

/*
 * SYSTem:COMMunicate:LAN:UPDate
 *
 * @INFO:
 * Stores any changes made to the LAN settings into non-volatile memory.
 *
 * @NOTE:
 * This command must be sent after changing the settings for DHCP, gateway, hostname, IP address, subnet mask.
 *
 */

scpi_result_t SCPI_SystemCommunicationLanUpdate(scpi_t * context)
{

	if(bsp.security.status)
	{
		SCPI_ErrorPush(context, SCPI_ERROR_SERVICE_MODE_SECURE);
		return SCPI_RES_ERR;
	}

	bsp.eeprom.structure.ip4.MAC[0] = bsp.ip4.MAC[0];
	bsp.eeprom.structure.ip4.MAC[1] = bsp.ip4.MAC[1];
	bsp.eeprom.structure.ip4.MAC[2] = bsp.ip4.MAC[2];
	bsp.eeprom.structure.ip4.MAC[3] = bsp.ip4.MAC[3];
	bsp.eeprom.structure.ip4.MAC[4] = bsp.ip4.MAC[4];
	bsp.eeprom.structure.ip4.MAC[5] = bsp.ip4.MAC[5];

	bsp.eeprom.structure.ip4.gateway[0] = bsp.ip4.gateway[0];
	bsp.eeprom.structure.ip4.gateway[1] = bsp.ip4.gateway[1];
	bsp.eeprom.structure.ip4.gateway[2] = bsp.ip4.gateway[2];
	bsp.eeprom.structure.ip4.gateway[3] = bsp.ip4.gateway[3];

	bsp.eeprom.structure.ip4.ip[0] = bsp.ip4.ip[0];
	bsp.eeprom.structure.ip4.ip[1] = bsp.ip4.ip[1];
	bsp.eeprom.structure.ip4.ip[2] = bsp.ip4.ip[2];
	bsp.eeprom.structure.ip4.ip[3] = bsp.ip4.ip[3];

	bsp.eeprom.structure.ip4.netmask[0] = bsp.ip4.netmask[0];
	bsp.eeprom.structure.ip4.netmask[1] = bsp.ip4.netmask[1];
	bsp.eeprom.structure.ip4.netmask[2] = bsp.ip4.netmask[2];
	bsp.eeprom.structure.ip4.netmask[3] = bsp.ip4.netmask[3];

	if(BSP_OK == EEPROM_Write(&bsp.eeprom,EEPROM_CFG_SIZE))
	{
		return SCPI_RES_OK;
	}
	else
	{
		SCPI_ErrorPush(context, SCPI_ERROR_SYSTEM_ERROR);
		return SCPI_RES_ERR;
	}

}

/*
 * SYSTem:SECure:STATe {ON|OFF|1|0} "<password>"
 *
 * @INFO:
 * Enables or disables device configuration protection. If the protection is disabled the user can reset the EEPROM of all MCU on the PCB,
 * change the device information and enable the calibration function.
 *
 * @PARAMETERS:
 * 				ON or 1			Enable device protection.
 * 				OFF or 0		Disable device protection.
 * 				"<password>"	Password string. The default password is "ETH1CLCR1". Max. password lenght is PASSWORD_LENGTH.
 *
 */

scpi_result_t SCPI_SystemSecureState(scpi_t * context)
{
	int32_t state = 0;
	int8_t password_read[STRING_LENGTH] = {0};
	size_t length = 0;
	int8_t* password_reference = bsp.eeprom.structure.service.password;

	if(!SCPI_ParamChoice(context, security_state_select, &state, TRUE))
	{
		return SCPI_RES_ERR;
	}

	if(!SCPI_ParamCopyText(context, (char*)password_read, STRING_LENGTH, &length, TRUE))
	{
		return SCPI_RES_ERR;
	}

	if(!strcmp((const char*)password_read, (const char*)password_reference))
	{
		bsp.security.status = state;
		return SCPI_RES_ERR;
	}
	else
	{
		SCPI_ErrorPush(context, SCPI_ERROR_SERVICE_INVALID_PASSWORD);
		return SCPI_RES_ERR;
	}

	return SCPI_RES_OK;
}

/*
 * SYSTem:SECure:STATe?
 *
 * @INFO:
 * Query the device security state. Returns 1 or 0.
 *
 */

scpi_result_t SCPI_SystemSecureStateQ(scpi_t * context)
{
	SCPI_ResultUInt8(context, bsp.security.status);
	return SCPI_RES_OK;
}

/*
 * SYSTem:TEMPerature?
 *
 * @INFO:
 * Returns the instrument's internal temperature. The temperature format depends on the selected unit (celsius, kelvin or fahrenheit).
 *
 */

scpi_result_t SCPI_SystemTemperatureQ(scpi_t * context)
{
	float temperature = 0.0;

	HDC1080_measure_temperature(&hi2c3, &temperature);

	switch(bsp.temperature.unit)
	{
		case CELSIUS: break;
		case FAHRENHEIT: temperature = (temperature*1.8)+32; break;
		case KELVIN: temperature += 273.15; break;
	}

	SCPI_ResultUInt8(context, (uint8_t)temperature);

	return SCPI_RES_OK;
}

/*
 * SYSTem:TEMPerature:UNIT
 *
 * @INFO:
 * Set the temperature unit.
 *
 * @PARAMETERS:
 * 				C	celsius
 * 				F	fahrenheit
 * 				K	kelvin
 *
 */

scpi_result_t SCPI_SystemTemperatureUnit(scpi_t * context)
{
	int32_t param = 0;

    if(!SCPI_ParamChoice(context, temperature_unit_select, &param, TRUE))
    {
        return SCPI_RES_ERR;
    }

    bsp.temperature.unit = param;

	return SCPI_RES_OK;
}

/*
 * SYSTem:TEMPerature:UNIT?
 *
 * @INFO:
 * Query the temperature unit. Result can be C, K or F.
 *
 */

scpi_result_t SCPI_SystemTemperatureUnitQ(scpi_t * context)
{
	switch(bsp.temperature.unit)
	{
		case CELSIUS: SCPI_ResultText(context, "C");break;
		case FAHRENHEIT: SCPI_ResultText(context, "F");break;
		case KELVIN: SCPI_ResultText(context, "K");break;
	}

	return SCPI_RES_OK;
}

/*
 * SYSTem:HUMIdity?
 *
 * @INFO:
 * Readout the device internal humidity as percentage value.
 *
 */

scpi_result_t SCPI_SystemHumidityQ(scpi_t * context)
{
	float humidity = 0.0;

	HDC1080_measure_humidity(&hi2c3, &humidity);
	SCPI_ResultUInt8(context,(uint8_t)humidity);

	return SCPI_RES_OK;
}

/*
 * SYSTem:SERVice:EEPROM {RESET|DEFault}
 *
 * @INFO:
 * Modify the EEPROM memory.
 *
 * @PARAMETERS:
 * 				RESET		Overwrite EEPROM memory with 0xFF.
 * 				DEFault		Overwrite EEPROM memory with device default values.
 *
 * @NOTE:
 * To use this function the device must be first unlocked using the SYSTem:SECure:STATe command.
 *
 */

scpi_result_t SCPI_SystemServiceEEPROM(scpi_t * context)
{
	int32_t select = 0;

	if(!SCPI_ParamChoice(context, EEPROM_state_select, &select, TRUE))
	{
		return SCPI_RES_ERR;
	}

	if(!bsp.security.status)
	{
		SCPI_ErrorPush(context, SCPI_ERROR_SERVICE_MODE_SECURE);
		return SCPI_RES_ERR;
	}

	if(RESET == select)
	{
		if(BSP_OK != EEPROM_Erase())
		{
			SCPI_ErrorPush(context, SCPI_ERROR_SYSTEM_ERROR);
			return SCPI_RES_ERR;
		}
	}
	else if(DEFAULT == select)
	{
		if(BSP_OK != EEPROM_Write(&bsp.eeprom, EEPROM_CFG_SIZE))
		{
			SCPI_ErrorPush(context, SCPI_ERROR_SYSTEM_ERROR);
			return SCPI_RES_ERR;
		}
	}


	return SCPI_RES_OK;
}

/*
 * SYSTem:SERVice:ID "<manufacturer>" "<device>" "<software_version>" "<serial_number>"
 *
 * @INFO:
 * Configure the device information, readout using the *IDN? command.
 *
 * @PARAMETERS:
 * 				"<manufacturer>"		Manufacturer string. Max. length is SCPI_MANUFACTURER_STRING_LENGTH.
 * 				"<device>"				Device name string. Max. length SCPI_MANUFACTURER_STRING_LENGTH.
 * 				"<software_version>"	Software version string. Max. length SCPI_SOFTWAREVERSION_STRING_LENGTH.
 * 				"<serial_number>"		Serial number string. Max. length SCPI_SERIALNUMBER_STRING_LENGTH.
 *
 * @NOTE:
 * To use this function the device must be first unlocked using the SYSTem:SECure:STATe command.
 *
 */

scpi_result_t SCPI_SystemServiceID(scpi_t * context)
{
	char buffer[256];
	size_t len;

	if(!bsp.security.status)
	{
		SCPI_ErrorPush(context, SCPI_ERROR_SERVICE_MODE_SECURE);
		return SCPI_RES_ERR;
	}

	if(!SCPI_ParamCopyText(context, buffer, STRING_LENGTH, &len, TRUE))
	{
		buffer[0]='\0';
		return SCPI_RES_ERR;
	}

	if(!SCPI_ParamCopyText(context, buffer, STRING_LENGTH, &len, TRUE))
	{
		buffer[0]='\0';
		return SCPI_RES_ERR;
	}

	if(!SCPI_ParamCopyText(context, buffer, STRING_LENGTH, &len, TRUE))
	{
		buffer[0]='\0';
		return SCPI_RES_ERR;
	}

	if(!SCPI_ParamCopyText(context, buffer, STRING_LENGTH, &len, TRUE))
	{
		buffer[0]='\0';
		return SCPI_RES_ERR;
	}

	strncpy(bsp.eeprom.structure.info.software_version,buffer,STRING_LENGTH);
	strncpy(bsp.eeprom.structure.info.serial_number,buffer,STRING_LENGTH);

	if(BSP_OK != EEPROM_Write(&bsp.eeprom, EEPROM_CFG_SIZE))
	{
		SCPI_ErrorPush(context, SCPI_ERROR_SYSTEM_ERROR);
		return SCPI_RES_ERR;
	}

	return SCPI_RES_OK;
}

