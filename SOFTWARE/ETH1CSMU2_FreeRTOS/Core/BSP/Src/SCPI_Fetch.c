/*
 * scpi_fetch.c
 *
 *  Created on: Mar 19, 2023
 *      Author: grzegorz
 */

#include "SCPI_Fetch.h"
#include "SCPI_Def.h"

/*
 * FETCh?
 *
 * @INFO:
 * Returns the array data which contains all of the voltage measurement data and current
 * measurement data output setting data specified by the :FORMat:ELEMents:SENSe command. The
 * data is not cleared until the :INITiate, :MEASure, or :READ command is executed.
 *
 * @PARAMETERS:
 *
 * @NOTE:
 *
 */

scpi_result_t SCPI_FetchQ(scpi_t * context)
{
	SCPI_ResultSting(context, ADC_VOLTAGE);
	SCPI_ResultSting(context, ADC_CURRENT);
	return SCPI_RES_OK;
}

/*
 * FETCh:VOLTage?
 *
 * @INFO:
 * Returns the array data which contains all of the voltage measurement data and current
 * measurement data output setting data specified by the :FORMat:ELEMents:SENSe command. The
 * data is not cleared until the :INITiate, :MEASure, or :READ command is executed.
 *
 * @PARAMETERS:
 *
 * @NOTE:
 *
 */

scpi_result_t SCPI_FetchVoltageQ(scpi_t * context)
{
	SCPI_ResultSting(context, ADC_VOLTAGE);
	return SCPI_RES_OK;
}

/*
 * FETCh:CURRent?
 *
 * @INFO:
 * Returns the array data which contains all of the voltage measurement data and current
 * measurement data output setting data specified by the :FORMat:ELEMents:SENSe command. The
 * data is not cleared until the :INITiate, :MEASure, or :READ command is executed.
 *
 * @PARAMETERS:
 *
 * @NOTE:
 *
 */

scpi_result_t SCPI_FetchCurrentQ(scpi_t * context)
{
	SCPI_ResultSting(context, ADC_CURRENT);
	return SCPI_RES_OK;
}
