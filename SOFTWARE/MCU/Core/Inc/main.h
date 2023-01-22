/* USER CODE BEGIN Header */
/**
  ******************************************************************************
  * @file           : main.h
  * @brief          : Header for main.c file.
  *                   This file contains the common defines of the application.
  ******************************************************************************
  * @attention
  *
  * Copyright (c) 2022 STMicroelectronics.
  * All rights reserved.
  *
  * This software is licensed under terms that can be found in the LICENSE file
  * in the root directory of this software component.
  * If no LICENSE file comes with this software, it is provided AS-IS.
  *
  ******************************************************************************
  */
/* USER CODE END Header */

/* Define to prevent recursive inclusion -------------------------------------*/
#ifndef __MAIN_H
#define __MAIN_H

#ifdef __cplusplus
extern "C" {
#endif

/* Includes ------------------------------------------------------------------*/
#include "stm32f7xx_hal.h"

/* Private includes ----------------------------------------------------------*/
/* USER CODE BEGIN Includes */

/* USER CODE END Includes */

/* Exported types ------------------------------------------------------------*/
/* USER CODE BEGIN ET */

/* USER CODE END ET */

/* Exported constants --------------------------------------------------------*/
/* USER CODE BEGIN EC */

/* USER CODE END EC */

/* Exported macro ------------------------------------------------------------*/
/* USER CODE BEGIN EM */

/* USER CODE END EM */

/* Exported functions prototypes ---------------------------------------------*/
void Error_Handler(void);

/* USER CODE BEGIN EFP */

/* USER CODE END EFP */

/* Private defines -----------------------------------------------------------*/
#define DDS_nDIV10_Pin GPIO_PIN_13
#define DDS_nDIV10_GPIO_Port GPIOC
#define DDS_DIV8_Pin GPIO_PIN_14
#define DDS_DIV8_GPIO_Port GPIOC
#define DDS_DIV4_Pin GPIO_PIN_15
#define DDS_DIV4_GPIO_Port GPIOC
#define DDS_DIV2_Pin GPIO_PIN_0
#define DDS_DIV2_GPIO_Port GPIOF
#define LED_BLUE_Pin GPIO_PIN_2
#define LED_BLUE_GPIO_Port GPIOB
#define LED_RED_Pin GPIO_PIN_11
#define LED_RED_GPIO_Port GPIOF
#define LED_GREEN_Pin GPIO_PIN_12
#define LED_GREEN_GPIO_Port GPIOF
#define TRIG_IN_Pin GPIO_PIN_7
#define TRIG_IN_GPIO_Port GPIOE
#define TRIG_OUT_Pin GPIO_PIN_8
#define TRIG_OUT_GPIO_Port GPIOE
#define TRIG_EN_Pin GPIO_PIN_9
#define TRIG_EN_GPIO_Port GPIOE
#define MCU_DEFAULT_Pin GPIO_PIN_10
#define MCU_DEFAULT_GPIO_Port GPIOE
#define CXN_REL6_Pin GPIO_PIN_12
#define CXN_REL6_GPIO_Port GPIOE
#define CXN_REL5_Pin GPIO_PIN_13
#define CXN_REL5_GPIO_Port GPIOE
#define CXN_REL4_Pin GPIO_PIN_14
#define CXN_REL4_GPIO_Port GPIOE
#define CXN_REL3_Pin GPIO_PIN_15
#define CXN_REL3_GPIO_Port GPIOE
#define CXN_REL2_Pin GPIO_PIN_10
#define CXN_REL2_GPIO_Port GPIOB
#define CXN_REL1_Pin GPIO_PIN_11
#define CXN_REL1_GPIO_Port GPIOB
#define MCU_nTDS_Pin GPIO_PIN_9
#define MCU_nTDS_GPIO_Port GPIOD
#define MCU_nISNK_Pin GPIO_PIN_10
#define MCU_nISNK_GPIO_Port GPIOD
#define MCU_nISRC_Pin GPIO_PIN_11
#define MCU_nISRC_GPIO_Port GPIOD
#define SR_OUT_Pin GPIO_PIN_14
#define SR_OUT_GPIO_Port GPIOD
#define SR_LAT_Pin GPIO_PIN_15
#define SR_LAT_GPIO_Port GPIOD
#define SR_CLK_Pin GPIO_PIN_2
#define SR_CLK_GPIO_Port GPIOG
#define SR_DAT_Pin GPIO_PIN_3
#define SR_DAT_GPIO_Port GPIOG
#define EEPROM_WP_Pin GPIO_PIN_4
#define EEPROM_WP_GPIO_Port GPIOG
#define DAC1_nRST_Pin GPIO_PIN_11
#define DAC1_nRST_GPIO_Port GPIOA
#define DAC1_LDAC_Pin GPIO_PIN_12
#define DAC1_LDAC_GPIO_Port GPIOA
#define ADC1_RVS1_Pin GPIO_PIN_0
#define ADC1_RVS1_GPIO_Port GPIOD
#define ADC1_RVS2_Pin GPIO_PIN_1
#define ADC1_RVS2_GPIO_Port GPIOD
#define DAC2_nLDAC_Pin GPIO_PIN_12
#define DAC2_nLDAC_GPIO_Port GPIOG
/* USER CODE BEGIN Private defines */

/* USER CODE END Private defines */

#ifdef __cplusplus
}
#endif

#endif /* __MAIN_H */
