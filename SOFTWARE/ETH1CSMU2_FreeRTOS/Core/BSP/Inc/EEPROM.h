/*
 * eeporm.h
 *
 *  Created on: Feb 10, 2023
 *      Author: grzegorz
 */

#ifndef THIRD_PARTY_BSP_INC_EEPROM_H_
#define THIRD_PARTY_BSP_INC_EEPROM_H_


#include "BSP.h"
#include "EE24.h"


#define EEPROM_ADDRESS 0xA0U
#define EEPROM_SIZE 0xFFU


BSP_StatusTypeDef EEPROM_Erase(void);
BSP_StatusTypeDef EEPROM_Write(bsp_eeprom_union_t *union_data, size_t size);
BSP_StatusTypeDef EEPROM_Read(bsp_eeprom_union_t *union_data, size_t size);
BSP_StatusTypeDef EEPROM_Status(void);

#endif /* THIRD_PARTY_BSP_INC_EEPROM_H_ */
