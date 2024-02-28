#ifndef __CD_Control_H__
#define __CD_Control_H__

#ifdef __cplusplus
extern "C" {
#endif

/* Includes ------------------------------------------------------------------*/
#include "stm32f4xx_hal.h"
#include "gpio.h"
#include "main.h"

/* USER CODE BEGIN Includes */

/* USER CODE END Includes */

/* USER CODE BEGIN Private defines */
/* USER CODE END Private defines */

/* USER CODE BEGIN Prototypes */
void CD_Enable(void);
void CD_Disable(void);
void CD_Control(uint8_t Channel);
/* USER CODE END Prototypes */

#ifdef __cplusplus
}
#endif
#endif /*__CD_Control_H__ */

