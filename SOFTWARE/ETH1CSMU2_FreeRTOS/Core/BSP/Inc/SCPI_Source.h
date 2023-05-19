/*
 * scpi_source.h
 *
 *  Created on: Mar 19, 2023
 *      Author: grzegorz
 */

#ifndef THIRD_PARTY_BSP_INC_SCPI_SOURCE_H_
#define THIRD_PARTY_BSP_INC_SCPI_SOURCE_H_

#include "BSP.h"
#include "cmsis_os.h"
#include "scpi/scpi.h"

#define SOURCE_DC_MAX_VAL				12.0f
#define SOURCE_DC_MIN_VAL				-12.0f
#define SOURCE_DC_DEF_VAL				0.0f

#define SOURCE_FGEN_MIN_FREQ			1.0f
#define SOURCE_FGEN_MAX_FREQ			100000.0f
#define SOURCE_FGEN_DEF_FREQ			1000.0f

#define SOURCE_SINE_MAX_VAL				12.0f
#define SOURCE_SINE_MIN_VAL				0.0f
#define SOURCE_SINE_DEF_VAL				1.0f
#define SOURCE_SINE_OFFSET_DEF_VAL		0.0f

#define CURR_RANGE_200uA				2E-4f
#define CURR_RANGE_2mA					2E-3f
#define CURR_RANGE_20mA					2E-2f
#define CURR_RANGE_200mA				2E-1f


scpi_result_t SCPI_SourceCurrentRange(scpi_t* context);
scpi_result_t SCPI_SourceCurrentRangeQ(scpi_t* context);
scpi_result_t SCPI_SourceCurrentRangeAuto(scpi_t* context);

scpi_result_t SCPI_SourceRelayOutput(scpi_t* context);
scpi_result_t SCPI_SourceRelayOutputQ(scpi_t* context);

scpi_result_t SCPI_SourceVoltageMode(scpi_t* context);
scpi_result_t SCPI_SourceVoltageModeQ(scpi_t* context);

scpi_result_t SCPI_SourceVoltageDCImmediate(scpi_t * context);
scpi_result_t SCPI_SourceVoltageDCImmediateQ(scpi_t * context);

scpi_result_t SCPI_SourceVoltageFgenImmediate(scpi_t * context);
scpi_result_t SCPI_SourceVoltageFgenImmediateQ(scpi_t * context);

scpi_result_t SCPI_SourceVoltageListLoad(scpi_t * context);
scpi_result_t SCPI_SourceVoltageListLoadQ(scpi_t * context);
scpi_result_t SCPI_SourceVoltagePointsQ(scpi_t * context);
scpi_result_t SCPI_SourceVoltageListAppend(scpi_t * context);
scpi_result_t SCPI_SourceVoltageListPointsQ(scpi_t * context);
scpi_result_t SCPI_SourceVoltageListStart(scpi_t * context);
scpi_result_t SCPI_SourceVoltageListStop(scpi_t * context);
scpi_result_t SCPI_SourceVoltageListDelay(scpi_t * context);

#endif /* THIRD_PARTY_BSP_INC_SCPI_SOURCE_H_ */
