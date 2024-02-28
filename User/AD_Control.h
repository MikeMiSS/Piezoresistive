#ifndef __AD_Control_H__
#define __AD_Control_H__

#ifdef __cplusplus
extern "C" {
#endif

/* Includes ------------------------------------------------------------------*/
#include "stm32f4xx_hal.h"
#include "spi.h"
#include "main.h"

/* USER CODE BEGIN Includes */

/* USER CODE END Includes */

/* USER CODE BEGIN Private defines */
#define CONV_Start() HAL_GPIO_WritePin(AD_CONV_GPIO_Port, AD_CONV_Pin, GPIO_PIN_RESET)
#define CONV_End() HAL_GPIO_WritePin(AD_CONV_GPIO_Port, AD_CONV_Pin, GPIO_PIN_SET)
/* USER CODE END Private defines */

/* USER CODE BEGIN Prototypes */
void MX_AD_Init(void);
/* USER CODE END Prototypes */

#ifdef __cplusplus
}
#endif
#endif /*__AD_Control_H__ */

