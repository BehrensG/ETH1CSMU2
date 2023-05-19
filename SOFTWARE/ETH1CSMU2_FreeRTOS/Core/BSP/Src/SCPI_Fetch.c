/*
 * scpi_fetch.c
 *
 *  Created on: Mar 19, 2023
 *      Author: grzegorz
 */

#include "SCPI_Fetch.h"


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
	return SCPI_RES_OK;
}

/*
 * FETCh:ARRay?
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

scpi_result_t SCPI_FetchArrayQ(scpi_t * context)
{
	return SCPI_RES_OK;
}

/*
 * FETCh:ARRay:VOLTage?
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

scpi_result_t SCPI_FetchArrayVoltageQ(scpi_t * context)
{
	return SCPI_RES_OK;
}

/*
 * FETCh:ARRay:CURRent?
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

scpi_result_t SCPI_FetchArrayCurrentQ(scpi_t * context)
{
	return SCPI_RES_OK;
}
