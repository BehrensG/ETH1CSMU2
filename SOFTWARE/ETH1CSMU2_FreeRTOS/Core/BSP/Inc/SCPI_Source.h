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


scpi_result_t SCPI_SourceCurrentRange(scpi_t* context);
scpi_result_t SCPI_SourceCurrentRangeQ(scpi_t* context);
scpi_result_t SCPI_SourceCurrentRangeAuto(scpi_t* context);

scpi_result_t SCPI_SourceRelayOutput(scpi_t* context);
scpi_result_t SCPI_SourceRelayOutputQ(scpi_t* context);

scpi_result_t SCPI_SourceVoltageMode(scpi_t* context);
scpi_result_t SCPI_SourceVoltageModeQ(scpi_t* context);

scpi_result_t SCPI_SourceVoltageLevelDCImmediate(scpi_t * context);
scpi_result_t SCPI_SourceVoltageLevelDCImmediateQ(scpi_t * context);

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
