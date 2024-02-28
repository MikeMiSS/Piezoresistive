/* USER CODE BEGIN Header */
/**
  ******************************************************************************
  * @file           : main.h
  * @brief          : Header for main.c file.
  *                   This file contains the common defines of the application.
  ******************************************************************************
  * @attention
  *
  * Copyright (c) 2024 STMicroelectronics.
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
#include "stm32f4xx_hal.h"

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
#define CD_E_Pin GPIO_PIN_3
#define CD_E_GPIO_Port GPIOC
#define CD_A0_Pin GPIO_PIN_1
#define CD_A0_GPIO_Port GPIOA
#define CD_A1_Pin GPIO_PIN_2
#define CD_A1_GPIO_Port GPIOA
#define CD_A2_Pin GPIO_PIN_3
#define CD_A2_GPIO_Port GPIOA
#define SPI1_CS_Pin GPIO_PIN_4
#define SPI1_CS_GPIO_Port GPIOA
#define AD_RESET_Pin GPIO_PIN_7
#define AD_RESET_GPIO_Port GPIOE
#define AD_CONV_Pin GPIO_PIN_8
#define AD_CONV_GPIO_Port GPIOE
#define AD_ALERT_Pin GPIO_PIN_9
#define AD_ALERT_GPIO_Port GPIOE
#define LED_Pin GPIO_PIN_8
#define LED_GPIO_Port GPIOD

/* USER CODE BEGIN Private defines */
#define SPI_CS_Enable() HAL_GPIO_WritePin(SPI1_CS_GPIO_Port, SPI1_CS_Pin, GPIO_PIN_SET)
#define SPI_CS_Disable() HAL_GPIO_WritePin(SPI1_CS_GPIO_Port, SPI1_CS_Pin, GPIO_PIN_RESET)

/* USER CODE END Private defines */

#ifdef __cplusplus
}
#endif

#endif /* __MAIN_H */
