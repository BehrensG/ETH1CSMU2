/*
 * SCPI_Calibration.c
 *
 *  Created on: May 19, 2023
 *      Author: grzegorz
 */

#include "SCPI_Calibration.h"
#include <math.h>

extern struct bsp_t bsp;

scpi_result_t SCPI_CalibrationVoltageADC1Value(scpi_t* context)
{
	return SCPI_RES_OK;
}

scpi_result_t SCPI_CalibrationVoltageADC2Value(scpi_t* context)
{
	return SCPI_RES_OK;
}

scpi_result_t SCPI_CalibrationCurrentADC1Value(scpi_t* context)
{
	return SCPI_RES_OK;
}

scpi_result_t SCPI_CalibrationCurrentADC2Value(scpi_t* context)
{
	return SCPI_RES_OK;
}



scpi_result_t SCPI_CalibrationVoltageDCValue(scpi_t* context)
{
	float dc_calib = 0.0, dc_min = 0.0, dc_max = 0.0;
	uint8_t index;

	if(!SCPI_ParamFloat(context, &dc_calib, TRUE))
	{
		return SCPI_RES_ERR;
	}

	if(bsp.config.dc.voltage.value > 0.0)
	{
		dc_max = bsp.config.dc.voltage.value + bsp.config.dc.voltage.value*0.1;
		dc_min = bsp.config.dc.voltage.value - bsp.config.dc.voltage.value*0.1;

		if((dc_max >= dc_calib) && (dc_min <= dc_calib))
		{
			index = bsp.config.dc.voltage.index;
			bsp.eeprom.structure.calib.dac8565.vout_a[index] = fabs(bsp.config.dc.voltage.value/dc_calib);
		}
	}
	else if(bsp.config.dc.voltage.value < 0.0)
	{
		dc_max = bsp.config.dc.voltage.value - bsp.config.dc.voltage.value*0.1;
		dc_min = bsp.config.dc.voltage.value + bsp.config.dc.voltage.value*0.1;

		if((dc_max >= dc_calib) && (dc_min <= dc_calib))
		{
			index = bsp.config.dc.voltage.index;
			bsp.eeprom.structure.calib.dac8565.vout_b[index] = fabs(bsp.config.dc.voltage.value/dc_calib);
		}
	}
	else if(0.0 == bsp.config.dc.voltage.value)
	{
		dc_max = 0.01;
		dc_min = -0.01;

		if((dc_max >= dc_calib) && (dc_min <= dc_calib))
		{
			//bsp.eeprom.structure.calib.dac8565.zero_offset = -1.0*dc_calib;
		}

	}


	return SCPI_RES_OK;
}

scpi_result_t SCPI_CalibrationCurrentDCValue(scpi_t* context)
{
	float dc_calib = 0.0, dc_min = 0.0, dc_max = 0.0;
	uint8_t index, mode;
	mode = bsp.config.dc.current.mode;

	if(!SCPI_ParamFloat(context, &dc_calib, TRUE))
	{
		return SCPI_RES_ERR;
	}

	if(bsp.config.dc.current.value[mode] > 0.0)
	{
		dc_max = bsp.config.dc.current.value[mode] + bsp.config.dc.current.value[mode]*3;
		dc_min = bsp.config.dc.current.value[mode] - bsp.config.dc.current.value[mode]*3;

		if((dc_max >= dc_calib) && (dc_min <= dc_calib))
		{
			index = bsp.config.dc.current.index[mode];

			if(CURR_POS == mode)
			{
				bsp.eeprom.structure.calib.dac8565.vout_d[index] = fabs(bsp.config.dc.current.value[mode]/dc_calib);
			}
			else
			{
				bsp.eeprom.structure.calib.dac8565.vout_c[index] = fabs(bsp.config.dc.current.value[mode]/dc_calib);
			}

		}
	}

	return SCPI_RES_OK;
}

scpi_result_t SCPI_CalibrationACOffsetValue(scpi_t* context)
{
	return SCPI_RES_OK;
}

scpi_result_t SCPI_CalibrationACAmplitudeValue(scpi_t* context)
{
	return SCPI_RES_OK;
}


scpi_result_t SCPI_CalibrationStateQ(scpi_t* context)
{

	return SCPI_RES_OK;
}

scpi_result_t SCPI_CalibrationStore(scpi_t* context)
{
	if(bsp.security.status)
	{
		SCPI_ErrorPush(context, SCPI_ERROR_SERVICE_MODE_SECURE);
		return SCPI_RES_ERR;
	}
	bsp.eeprom.structure.calib.count++;
	if(BSP_OK != EEPROM_Write(&bsp.eeprom, EEPROM_CFG_SIZE))
	{
		SCPI_ErrorPush(context, SCPI_ERROR_SYSTEM_ERROR);
		return SCPI_RES_ERR;
	}

	return SCPI_RES_OK;
}

scpi_result_t SCPI_CalibrationCountQ(scpi_t* context)
{
	SCPI_ResultUInt32(context, bsp.eeprom.structure.calib.count);
	return SCPI_RES_OK;
}
