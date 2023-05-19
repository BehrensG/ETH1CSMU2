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

static uint8_t SET_DCRange(float value)
{

	for(uint8_t x = 0; x < 3; x++)
	{
		if((bsp.config.dc.range[2] >= value) && (bsp.config.dc.range[1] < value))
		{
			return 2;
		}
		else if((bsp.config.dc.range[1] >= value) && (bsp.config.dc.range[0] < value))
		{
			return 1;
		}
		else if((bsp.config.dc.range[0] >= value))
		{
			return 0;
		}
		else
		{
			return 2;
		}

	}
}

scpi_result_t SCPI_CalibrationVoltageDCValue(scpi_t* context)
{
	float dc_calib = 0.0, dc_min = 0.0, dc_max = 0.0;
	uint8_t index;

	if(!SCPI_ParamFloat(context, &dc_calib, TRUE))
	{
		return SCPI_RES_ERR;
	}

	if(bsp.config.dc.value > 0.0)
	{
		dc_max = bsp.config.dc.value + bsp.config.dc.value*0.05;
		dc_min = bsp.config.dc.value - bsp.config.dc.value*0.05;

		if((dc_max >= dc_calib) && (dc_min <= dc_calib))
		{
			index = SET_DCRange(fabs(dc_calib));
			bsp.eeprom.structure.calib.dac8565.vout_a[index] = fabs(bsp.config.dc.value/dc_calib);
		}
	}
	else if(bsp.config.dc.value < 0.0)
	{
		dc_max = bsp.config.dc.value - bsp.config.dc.value*0.05;
		dc_min = bsp.config.dc.value + bsp.config.dc.value*0.05;

		if((dc_max >= dc_calib) && (dc_min <= dc_calib))
		{
			index = SET_DCRange(fabs(dc_calib));
			bsp.eeprom.structure.calib.dac8565.vout_b[index] = fabs(bsp.config.dc.value/dc_calib);
		}
	}
	else if(0.0 == bsp.config.dc.value)
	{
		dc_max = 0.001;
		dc_min = -0.001;

		if((dc_max >= dc_calib) && (dc_min <= dc_calib))
		{
			//bsp.eeprom.structure.calib.dac8565.zero_offset = -1.0*dc_calib;
		}

	}


	return SCPI_RES_OK;
}

scpi_result_t SCPI_CalibrationFGENOffsetValue(scpi_t* context)
{
	return SCPI_RES_OK;
}

scpi_result_t SCPI_CalibrationFGENAmplitudeValue(scpi_t* context)
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
