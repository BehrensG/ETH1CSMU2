/*
 * scpi_measure.h
 *
 *  Created on: Mar 19, 2023
 *      Author: grzegorz
 */

#ifndef THIRD_PARTY_BSP_INC_SCPI_MEASURE_H_
#define THIRD_PARTY_BSP_INC_SCPI_MEASURE_H_

#include "scpi/scpi.h"
#include "cmsis_os.h"
#include "bsp.h"

scpi_result_t SCPI_MeasureQ(scpi_t * context);
scpi_result_t SCPI_MeasureCurrentQ(scpi_t * context);
scpi_result_t SCPI_MeasureVoltageQ(scpi_t * context);

#endif /* THIRD_PARTY_BSP_INC_SCPI_MEASURE_H_ */
