/*
 * scpi_fetch.h
 *
 *  Created on: Mar 19, 2023
 *      Author: grzegorz
 */

#ifndef THIRD_PARTY_BSP_INC_SCPI_FETCH_H_
#define THIRD_PARTY_BSP_INC_SCPI_FETCH_H_

#include "scpi/scpi.h"
#include "cmsis_os.h"
#include "bsp.h"

scpi_result_t SCPI_FetchQ(scpi_t* context);
scpi_result_t SCPI_FetchArrayQ(scpi_t* context);
scpi_result_t SCPI_FetchArrayVoltageQ(scpi_t* context);
scpi_result_t SCPI_FetchArrayCurrentQ(scpi_t* context);

#endif /* THIRD_PARTY_BSP_INC_SCPI_FETCH_H_ */
