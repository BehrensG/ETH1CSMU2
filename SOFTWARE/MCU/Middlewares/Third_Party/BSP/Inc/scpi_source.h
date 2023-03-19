/*
 * scpi_source.h
 *
 *  Created on: Mar 19, 2023
 *      Author: grzegorz
 */

#ifndef THIRD_PARTY_BSP_INC_SCPI_SOURCE_H_
#define THIRD_PARTY_BSP_INC_SCPI_SOURCE_H_

#include "scpi/scpi.h"
#include "cmsis_os.h"
#include "bsp.h"

scpi_result_t SCPI_SourceCurrentRange(scpi_t* context);
scpi_result_t SCPI_SourceCurrentRangeQ(scpi_t* context);
scpi_result_t SCPI_SourceCurrentRangeAuto(scpi_t* context);
scpi_result_t SCPI_SourceRelayOutput(scpi_t* context);
scpi_result_t SCPI_SourceRelayOutputQ(scpi_t* context);
scpi_result_t SCPI_SourceFunctionMode(scpi_t* context);
scpi_result_t SCPI_SourceFunctionModeQ(scpi_t* context);

#endif /* THIRD_PARTY_BSP_INC_SCPI_SOURCE_H_ */
