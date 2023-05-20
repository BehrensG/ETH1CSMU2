/*
 * SCPI_Calibration.h
 *
 *  Created on: May 19, 2023
 *      Author: grzegorz
 */

#ifndef BSP_INC_SCPI_CALIBRATION_H_
#define BSP_INC_SCPI_CALIBRATION_H_

#include "scpi/scpi.h"

#include "BSP.h"
#include "EEPROM.h"

scpi_result_t SCPI_CalibrationVoltageADC1Value(scpi_t* context);
scpi_result_t SCPI_CalibrationVoltageADC2Value(scpi_t* context);
scpi_result_t SCPI_CalibrationVoltageDCValue(scpi_t* context);
scpi_result_t SCPI_CalibrationCurrentDCValue(scpi_t* context);
scpi_result_t SCPI_CalibrationACOffsetValue(scpi_t* context);
scpi_result_t SCPI_CalibrationACAmplitudeValue(scpi_t* context);
scpi_result_t SCPI_CalibrationCurrentADC1Value(scpi_t* context);
scpi_result_t SCPI_CalibrationCurrentADC2Value(scpi_t* context);
scpi_result_t SCPI_CalibrationStateQ(scpi_t* context);
scpi_result_t SCPI_CalibrationStore(scpi_t* context);
scpi_result_t SCPI_CalibrationCountQ(scpi_t* context);


#endif /* BSP_INC_SCPI_CALIBRATION_H_ */
