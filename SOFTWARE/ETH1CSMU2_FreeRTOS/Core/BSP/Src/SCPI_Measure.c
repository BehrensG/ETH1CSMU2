/*
 * scpi_measure.c
 *
 *  Created on: Mar 19, 2023
 *      Author: grzegorz
 */

#include "SCPI_Measure.h"
#include "TCP_Package.h"
#include "AD7980.h"
#include "ADS8681.h"

extern struct bsp_t bsp;

scpi_result_t SCPI_MeasureQ(scpi_t * context)
{
	if((DC == bsp.config.mode) && (AC == bsp.config.mode))
	{
		if(SELECT_ADC1 == bsp.config.measure.adc_type)
		{
			ADS8681_ReadData(bsp.config.measure.count);
			SCPI_ResultCharacters(context, TCP_Package(bsp.adc[ADC_VOLTAGE].meas, 0, TCP_PACKGE_SIZE), TCP_PACKGE_SIZE);
			SCPI_ResultCharacters(context, TCP_Package(bsp.adc[ADC_CURRENT].meas, 0, TCP_PACKGE_SIZE), TCP_PACKGE_SIZE);
		}
		else if(SELECT_ADC2 == bsp.config.measure.adc_type)
		{
			AD7980_ReadData(bsp.config.measure.count);
			SCPI_ResultCharacters(context, TCP_Package(bsp.adc[ADC_VOLTAGE].meas, 0, TCP_PACKGE_SIZE), TCP_PACKGE_SIZE);
			SCPI_ResultCharacters(context, TCP_Package(bsp.adc[ADC_CURRENT].meas, 0, TCP_PACKGE_SIZE), TCP_PACKGE_SIZE);
		}
		else
		{
			return SCPI_RES_ERR;
		}
	}

	return SCPI_RES_OK;
}

scpi_result_t SCPI_MeasureCurrentQ(scpi_t * context)
{
	if((DC == bsp.config.mode) && (AC == bsp.config.mode))
	{
		if(SELECT_ADC1 == bsp.config.measure.adc_type)
		{
			ADS8681_ReadData(bsp.config.measure.count);
			SCPI_ResultCharacters(context, TCP_Package(bsp.adc[ADC_CURRENT].meas, 0, TCP_PACKGE_SIZE), TCP_PACKGE_SIZE);
		}
		else if(SELECT_ADC2 == bsp.config.measure.adc_type)
		{
			AD7980_ReadData(bsp.config.measure.count);
			SCPI_ResultCharacters(context, TCP_Package(bsp.adc[ADC_CURRENT].meas, 0, TCP_PACKGE_SIZE), TCP_PACKGE_SIZE);
		}
		else
		{
			return SCPI_RES_ERR;
		}
	}

	return SCPI_RES_OK;
}

scpi_result_t SCPI_MeasureVoltageQ(scpi_t * context)
{
	if((DC == bsp.config.mode) && (AC == bsp.config.mode))
	{
		if(SELECT_ADC1 == bsp.config.measure.adc_type)
		{
			ADS8681_ReadData(bsp.config.measure.count);
			SCPI_ResultCharacters(context, TCP_Package(bsp.adc[ADC_VOLTAGE].meas, 0, TCP_PACKGE_SIZE), TCP_PACKGE_SIZE);
		}
		else if(SELECT_ADC2 == bsp.config.measure.adc_type)
		{
			AD7980_ReadData(bsp.config.measure.count);
			SCPI_ResultCharacters(context, TCP_Package(bsp.adc[ADC_VOLTAGE].meas, 0, TCP_PACKGE_SIZE), TCP_PACKGE_SIZE);
		}
		else
		{
			return SCPI_RES_ERR;
		}
	}

	return SCPI_RES_OK;
}
