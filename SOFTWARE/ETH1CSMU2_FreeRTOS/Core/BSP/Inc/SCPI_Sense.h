/*
 * scpi_sense.h
 *
 *  Created on: Mar 19, 2023
 *      Author: grzegorz
 */

#ifndef THIRD_PARTY_BSP_INC_SCPI_SENSE_H_
#define THIRD_PARTY_BSP_INC_SCPI_SENSE_H_

#include "scpi/scpi.h"
#include "main.h"


scpi_result_t SCPI_SenseFunctionOn(scpi_t* context);
scpi_result_t SCPI_SenseFunctionOnQ(scpi_t* context);
scpi_result_t SCPI_SenseSelectADC(scpi_t* context);
scpi_result_t SCPI_SenseSelectADCQ(scpi_t* context);
scpi_result_t SCPI_SenseCount(scpi_t* context);
scpi_result_t SCPI_SenseCountQ(scpi_t* context);
scpi_result_t SCPI_SenseVoltageGain(scpi_t* context);
scpi_result_t SCPI_SenseVoltageGainQ(scpi_t* context);
scpi_result_t SCPI_SenseCurrentGain(scpi_t* context);
scpi_result_t SCPI_SenseCurrentGainQ(scpi_t* context);
scpi_result_t SCPI_SenseMeasureDelay(scpi_t* context);
scpi_result_t SCPI_SenseMeasureDelayQ(scpi_t* context);
scpi_result_t SCPI_SenseVoltageListMeasureQ(scpi_t* context);

#endif /* THIRD_PARTY_BSP_INC_SCPI_SENSE_H_ */
