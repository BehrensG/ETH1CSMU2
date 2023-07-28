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
#include "SCPI_Def.h"

extern struct bsp_t bsp;


scpi_result_t SCPI_MeasureQ(scpi_t * context)
{
	if((DC == bsp.config.mode) || (AC == bsp.config.mode))
	{
		if(SELECT_ADC1 == bsp.config.measure.adc_type)
		{
			ADS8681_Measure(bsp.config.measure.count);
			SCPI_ResultSting(context, ADC_VOLTAGE);
			SCPI_ResultSting(context, ADC_CURRENT);
		}
		else if(SELECT_ADC2 == bsp.config.measure.adc_type)
		{
			AD7980_Measure(bsp.config.measure.count);
			SCPI_ResultSting(context, ADC_VOLTAGE);
			SCPI_ResultSting(context, ADC_CURRENT);
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
			ADS8681_Measure(bsp.config.measure.count);
			SCPI_ResultSting(context, ADC_CURRENT);
		}
		else if(SELECT_ADC2 == bsp.config.measure.adc_type)
		{
			AD7980_Measure(bsp.config.measure.count);
			SCPI_ResultSting(context, ADC_CURRENT);
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
			ADS8681_Measure(bsp.config.measure.count);
			SCPI_ResultSting(context, ADC_VOLTAGE);
		}
		else if(SELECT_ADC2 == bsp.config.measure.adc_type)
		{
			AD7980_Measure(bsp.config.measure.count);
			SCPI_ResultSting(context, ADC_VOLTAGE);
		}
		else
		{
			return SCPI_RES_ERR;
		}
	}

	return SCPI_RES_OK;
}
