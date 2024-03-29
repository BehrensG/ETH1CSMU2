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

#define SOURCE_VOLT_DC_MAX_VAL			11.0f
#define SOURCE_VOLT_DC_MIN_VAL			-11.0f
#define SOURCE_VOLT_DC_DEF_VAL			0.0f
#define SOURCE_CURR_DC_MAX_VAL			0.2f
#define SOURCE_CURR_DC_MIN_VAL			0.0f
#define SOURCE_CURR_DC_DEF_VAL			0.2f

#define SOURCE_AC_MIN_FREQ				1.0f
#define SOURCE_AC_MAX_FREQ				200000.0f
#define SOURCE_AC_DEF_FREQ				1000.0f

#define SOURCE_AC_MAX_VAL				11.0f
#define SOURCE_AC_MIN_VAL				-11.0f
#define SOURCE_AC_DEF_VAL				1.0f
#define SOURCE_AC_OFFSET_DEF_VAL		0.0f

#define SOURCE_LIST_DELAY_MAX_VAL		60000 // value is in mili-seconds
#define SOURCE_LIST_DELAY_MIN_VAL		0 // value is in mili-seconds
#define SOURCE_LIST_DELAY_DEF_VAL		0 // value is in mili-seconds

#define SOURCE_LIST_START_MAX_VAL		(LIST_SIZE -1)
#define SOURCE_LIST_START_MIN_VAL		0
#define SOURCE_LIST_START_DEF_VAL		0

#define SOURCE_LIST_STOP_MAX_VAL		(LIST_SIZE-1)
#define SOURCE_LIST_STOP_MIN_VAL		1
#define SOURCE_LIST_STOP_DEF_VAL		(LIST_SIZE-1)

#define SIGN_POS						1
#define SIGN_NEG						2

scpi_result_t SCPI_SourceCurrentRange(scpi_t* context);
scpi_result_t SCPI_SourceCurrentRangeQ(scpi_t* context);
scpi_result_t SCPI_SourceCurrentRangeAuto(scpi_t* context);

scpi_result_t SCPI_Output(scpi_t* context);
scpi_result_t SCPI_OutputQ(scpi_t* context);

scpi_result_t SCPI_SourceFunctionMode(scpi_t* context);
scpi_result_t SCPI_SourceFunctionModeQ(scpi_t* context);

scpi_result_t SCPI_SourceVoltageDCImmediate(scpi_t * context);
scpi_result_t SCPI_SourceVoltageDCImmediateQ(scpi_t * context);

scpi_result_t SCPI_SourceCurrentDCPositiveImmediate(scpi_t * context);
scpi_result_t SCPI_SourceCurrentDCPositiveImmediateQ(scpi_t * context);
scpi_result_t SCPI_SourceCurrentDCNegativeImmediate(scpi_t * context);
scpi_result_t SCPI_SourceCurrentDCNegativeImmediateQ(scpi_t * context);

scpi_result_t SCPI_SourceVoltageACImmediate(scpi_t * context);
scpi_result_t SCPI_SourceVoltageACImmediateQ(scpi_t * context);
scpi_result_t SCPI_SourceVoltageACAmplitudeImmediate(scpi_t * context);
scpi_result_t SCPI_SourceVoltageACFrequencyImmediate(scpi_t * context);
scpi_result_t SCPI_SourceVoltageACOffsetImmediate(scpi_t * context);

scpi_result_t SCPI_SourceVoltageListLoad(scpi_t * context);
scpi_result_t SCPI_SourceVoltageListLoadQ(scpi_t * context);
scpi_result_t SCPI_SourceVoltagePointsQ(scpi_t * context);
scpi_result_t SCPI_SourceVoltageListAppend(scpi_t * context);
scpi_result_t SCPI_SourceVoltageListPointsQ(scpi_t * context);
scpi_result_t SCPI_SourceVoltageListStart(scpi_t * context);
scpi_result_t SCPI_SourceVoltageListStop(scpi_t * context);
scpi_result_t SCPI_SourceVoltageListDelay(scpi_t * context);
scpi_result_t SCPI_SourceVoltageListDelayQ(scpi_t * context);
scpi_result_t SCPI_SourceVoltageListMeasureEnable(scpi_t * context);
scpi_result_t SCPI_SourceVoltageListMeasureEnableQ(scpi_t * context);
scpi_result_t SCPI_SourceVoltageListImmediate(scpi_t * context);

scpi_result_t SCPI_SourceVoltageDCCorrection(scpi_t * context);
scpi_result_t SCPI_SourceVoltageDCCorrectionQ(scpi_t * context);

#endif /* THIRD_PARTY_BSP_INC_SCPI_SOURCE_H_ */
