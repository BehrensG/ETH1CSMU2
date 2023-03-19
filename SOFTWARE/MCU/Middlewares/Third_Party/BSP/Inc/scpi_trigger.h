/*
 * scpi_trigger.h
 *
 *  Created on: Mar 17, 2023
 *      Author: grzegorz
 */

#ifndef THIRD_PARTY_BSP_INC_SCPI_TRIGGER_H_
#define THIRD_PARTY_BSP_INC_SCPI_TRIGGER_H_

#include "scpi/scpi.h"
#include "cmsis_os.h"
#include "bsp.h"

#define SLOPE_POS 1
#define SLOPE_NEG 2

enum e_trigger_source
{
	TRIG_IMM = 1,
	TRIG_EXT,
	TRIG_BUS,
	TRIG_OUT
};

scpi_result_t SCPI_TriggerDelay(scpi_t* context);
scpi_result_t SCPI_TriggerDelayQ(scpi_t* context);
scpi_result_t SCPI_TriggerImmediate(scpi_t* context);
scpi_result_t SCPI_TriggerSource(scpi_t* context);
scpi_result_t SCPI_TriggerSourceQ(scpi_t* context);
scpi_result_t SCPI_TriggerOutput(scpi_t* context);
scpi_result_t SCPI_TriggerSlope(scpi_t* context);
scpi_result_t SCPI_TriggerSlopeQ(scpi_t* context);
scpi_result_t SCPI_TriggerOutputSlope(scpi_t* context);
scpi_result_t SCPI_TriggerOutputSlopeQ(scpi_t* context);
scpi_result_t SCPI_TRG(scpi_t* context);

#endif /* THIRD_PARTY_BSP_INC_SCPI_TRIGGER_H_ */
