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

#define MAX_PART_SAMPLES 1000

static void ResultSting(scpi_t * context, uint8_t index)
{
	uint32_t part = 0, rest = 0;
	uint32_t start = 0;
	part = bsp.config.measure.count/MAX_PART_SAMPLES;
	rest = bsp.config.measure.count % MAX_PART_SAMPLES;

	for(uint8_t x = 0 ; x < part; x++)
	{
		SCPI_ResultCharacters(context, TCP_Package(bsp.adc[index].meas, start, MAX_PART_SAMPLES), TCP_PACKGE_SIZE);
		start += MAX_PART_SAMPLES;
	}
	if(rest)
	{
		SCPI_ResultCharacters(context, TCP_Package(bsp.adc[index].meas, start, rest), TCP_PACKGE_SIZE);
	}

}

scpi_result_t SCPI_MeasureQ(scpi_t * context)
{
	if((DC == bsp.config.mode) || (AC == bsp.config.mode))
	{
		if(SELECT_ADC1 == bsp.config.measure.adc_type)
		{
			ADS8681_ReadData(bsp.config.measure.count);
			ResultSting(context, ADC_VOLTAGE);
			ResultSting(context, ADC_CURRENT);
		}
		else if(SELECT_ADC2 == bsp.config.measure.adc_type)
		{
			AD7980_ReadData(bsp.config.measure.count);
			ResultSting(context, ADC_VOLTAGE);
			ResultSting(context, ADC_CURRENT);
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
	if((DC == bsp.config.mode) || (AC == bsp.config.mode))
	{
		if(SELECT_ADC1 == bsp.config.measure.adc_type)
		{
			ADS8681_ReadData(bsp.config.measure.count);
			ResultSting(context, ADC_CURRENT);
		}
		else if(SELECT_ADC2 == bsp.config.measure.adc_type)
		{
			AD7980_ReadData(bsp.config.measure.count);
			ResultSting(context, ADC_CURRENT);
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
	if((DC == bsp.config.mode) || (AC == bsp.config.mode))
	{
		if(SELECT_ADC1 == bsp.config.measure.adc_type)
		{
			ADS8681_ReadData(bsp.config.measure.count);
			ResultSting(context, ADC_VOLTAGE);
		}
		else if(SELECT_ADC2 == bsp.config.measure.adc_type)
		{
			AD7980_ReadData(bsp.config.measure.count);
			ResultSting(context, ADC_VOLTAGE);
		}
		else
		{
			return SCPI_RES_ERR;
		}
	}

	return SCPI_RES_OK;
}
