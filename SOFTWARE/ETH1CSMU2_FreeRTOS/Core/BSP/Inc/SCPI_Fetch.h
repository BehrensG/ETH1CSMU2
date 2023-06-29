/*
 * scpi_fetch.h
 *
 *  Created on: Mar 19, 2023
 *      Author: grzegorz
 */

#ifndef THIRD_PARTY_BSP_INC_SCPI_FETCH_H_
#define THIRD_PARTY_BSP_INC_SCPI_FETCH_H_

#include "BSP.h"
#include "scpi/scpi.h"
#include "cmsis_os.h"

scpi_result_t SCPI_FetchQ(scpi_t* context);
scpi_result_t SCPI_FetchVoltageQ(scpi_t* context);
scpi_result_t SCPI_FetchCurrentQ(scpi_t* context);

#endif /* THIRD_PARTY_BSP_INC_SCPI_FETCH_H_ */
