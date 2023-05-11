/*
 * scpi_sense.h
 *
 *  Created on: Mar 19, 2023
 *      Author: grzegorz
 */

#ifndef THIRD_PARTY_BSP_INC_SCPI_SENSE_H_
#define THIRD_PARTY_BSP_INC_SCPI_SENSE_H_

#include "scpi/scpi.h"

scpi_result_t SCPI_SenseCurrentDCProtectionLevelPositive(scpi_t* context);
scpi_result_t SCPI_SenseCurrentDCProtectionLevelPositiveQ(scpi_t* context);
scpi_result_t SCPI_SenseCurrentDCProtectionLevelNegative(scpi_t* context);
scpi_result_t SCPI_SenseCurrentDCProtectionLevelNegativeQ(scpi_t* context);

#endif /* THIRD_PARTY_BSP_INC_SCPI_SENSE_H_ */
