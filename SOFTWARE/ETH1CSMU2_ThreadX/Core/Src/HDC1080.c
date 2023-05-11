/*
 * HDC1080.c
 *
 *  Created on: Mar 17, 2023
 *      Author: grzegorz
 */

#include "HDC1080.h"
#include <string.h>


static BSP_StatusTypeDef HDC1080_read_reg(I2C_HandleTypeDef *hi2c, uint16_t delay, uint8_t reg, uint16_t *val)
{
	uint8_t buf[2];
	BSP_StatusTypeDef  status;

	// Check argument
	if ((reg != HDC1080_TEMPERATURE) &
		  (reg != HDC1080_HUMIDITY) &
		  (reg != HDC1080_CONFIG) &
		  (reg != HDC1080_SERIAL_ID1) &
		  (reg != HDC1080_SERIAL_ID2) &
		  (reg != HDC1080_SERIAL_ID3) &
		  (reg != HDC1080_ID_MANU) &
	    (reg != HDC1080_ID_DEV) )
		return BSP_ERROR;

	buf[0] = reg;
	/* Read register */
	/* Send the read followed by address */
	status = HAL_I2C_Master_Transmit(hi2c,HDC1080_ADDR<<1,buf,1,100);
	if (status != BSP_OK)
		return status;

	HAL_Delay(delay);

	/* Receive a 2-byte result */
	status = HAL_I2C_Master_Receive(hi2c, HDC1080_ADDR<<1 | 0x01, buf, 2, 1000);
	if (status != BSP_OK)
		return status;

	/* Result */
	*val = buf[0]*256+buf[1];

	return BSP_OK;  /* Success */

}


/*
static BSP_StatusTypeDef HDC1080_write_reg(I2C_HandleTypeDef *hi2c, uint8_t reg, uint16_t val)
{
	uint8_t buf[3];
	BSP_StatusTypeDef status;

		// Check argument
	if ((reg != HDC1080_TEMPERATURE) &  // dummy write to adr 0 ... trigger measurement
		  (reg != HDC1080_CONFIG) )       // config is "writable"
		return BSP_ERROR;

	buf[0] = reg;
	buf[1] = (uint8_t)((val >> 8) & 0xff);  // msb
	buf[2] = (uint8_t)(val & 0xff); 				// lsb

	status = HAL_I2C_Master_Transmit(hi2c,HDC1080_ADDR<<1,buf,3,100);
	if (status != BSP_OK)
		return status;
  else
	  return BSP_OK;
}
*/

BSP_StatusTypeDef HDC1080_measure_temperature(I2C_HandleTypeDef *hi2c, float *temperature)
{
	BSP_StatusTypeDef status;
	float tmp = 0.0;
	uint16_t readout = 0x00;

	status = HDC1080_read_reg(hi2c, 150, HDC1080_TEMPERATURE, &readout);
	if (status != BSP_OK)
		return status;

	tmp = (float)readout;
	tmp = (tmp / 65536.0) * 165.0 - 40.0;
	*temperature = tmp;  // °C

	return BSP_OK;
}

BSP_StatusTypeDef HDC1080_measure_humidity(I2C_HandleTypeDef *hi2c, float *humidity)
{
	BSP_StatusTypeDef status;
	float tmp = 0.0;
	uint16_t readout = 0x00;


	status = HDC1080_read_reg(hi2c, 150, HDC1080_HUMIDITY, &readout);
	if (status != BSP_OK)
		return status;

	tmp = (float)readout;
	tmp = (tmp / 65536.0) * 100.0;
	if (tmp>100.0) tmp = 100.0;
	if (tmp<0) tmp = 0.0;
	*humidity = tmp;

	return BSP_OK;
}
