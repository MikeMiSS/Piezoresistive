/* USER CODE BEGIN Header */
/**
  ******************************************************************************
  * File Name          : freertos.c
  * Description        : Code for freertos applications
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

/* Includes ------------------------------------------------------------------*/
#include "FreeRTOS.h"
#include "task.h"
#include "main.h"
#include "cmsis_os.h"

/* Private includes ----------------------------------------------------------*/
/* USER CODE BEGIN Includes */
#include "spi.h"
#include "stdio.h"
#include "usart.h"
#include "queue.h"
#include "CD_Control.h"
#include "AD_Control.h"
/* USER CODE END Includes */

/* Private typedef -----------------------------------------------------------*/
/* USER CODE BEGIN PTD */

/* USER CODE END PTD */

/* Private define ------------------------------------------------------------*/
/* USER CODE BEGIN PD */
#define user_main_printf(format, ...) printf( format "\r\n", ##__VA_ARGS__)
/* USER CODE END PD */

/* Private macro -------------------------------------------------------------*/
/* USER CODE BEGIN PM */

/* USER CODE END PM */

/* Private variables ---------------------------------------------------------*/
/* USER CODE BEGIN Variables */

uint16_t RData;
uint16_t Alert;
uint16_t V_Matrix[8][8] = {0};

int fputc(int ch, FILE *f) 

{
	uint16_t temp = ch;
  HAL_UART_Transmit(&huart1, (uint8_t *)&temp, sizeof(temp), 0xffff);

  return ch;

}

osThreadId_t LEDTaskHandle;
const osThreadAttr_t LEDTask_attributes = {
  .name = "LEDTask",
  .stack_size = 128 * 4,
  .priority = (osPriority_t) osPriorityNormal,
};
void StartLEDTask(void *argument);


osThreadId_t ADTaskHandle;
const osThreadAttr_t ADTask_attributes = {
  .name = "ADTask",
  .stack_size = 128 * 4,
  .priority = (osPriority_t) osPriorityLow,
};
void StartADTask(void *argument);


osThreadId_t DataTxTaskHandle;
const osThreadAttr_t DataTxTask_attributes = {
  .name = "DataTxTask",
  .stack_size = 128 * 4,
  .priority = (osPriority_t) osPriorityNormal,
};
void DataTxTask(void *argument);

void HAL_SPI_TxRxCpltCallback(SPI_HandleTypeDef *hspi);

QueueHandle_t myDataQueue01Handle;

/* USER CODE END Variables */
/* Definitions for defaultTask */
osThreadId_t defaultTaskHandle;
const osThreadAttr_t defaultTask_attributes = {
  .name = "defaultTask",
  .stack_size = 128 * 4,
  .priority = (osPriority_t) osPriorityNormal,
};

/* Private function prototypes -----------------------------------------------*/
/* USER CODE BEGIN FunctionPrototypes */

/* USER CODE END FunctionPrototypes */

void StartDefaultTask(void *argument);

void MX_FREERTOS_Init(void); /* (MISRA C 2004 rule 8.1) */

/**
  * @brief  FreeRTOS initialization
  * @param  None
  * @retval None
  */
void MX_FREERTOS_Init(void) {
  /* USER CODE BEGIN Init */

  /* USER CODE END Init */

  /* USER CODE BEGIN RTOS_MUTEX */
  /* add mutexes, ... */
  /* USER CODE END RTOS_MUTEX */

  /* USER CODE BEGIN RTOS_SEMAPHORES */
  /* add semaphores, ... */
  /* USER CODE END RTOS_SEMAPHORES */

  /* USER CODE BEGIN RTOS_TIMERS */
  /* start timers, add new ones, ... */
  /* USER CODE END RTOS_TIMERS */

  /* USER CODE BEGIN RTOS_QUEUES */
	myDataQueue01Handle = xQueueCreate(64, sizeof(uint16_t));
  /* add queues, ... */
  /* USER CODE END RTOS_QUEUES */

  /* Create the thread(s) */
  /* creation of defaultTask */
  defaultTaskHandle = osThreadNew(StartDefaultTask, NULL, &defaultTask_attributes);

  /* USER CODE BEGIN RTOS_THREADS */
	LEDTaskHandle = osThreadNew(StartLEDTask, NULL, &LEDTask_attributes);
	ADTaskHandle = osThreadNew(StartADTask, NULL, &ADTask_attributes);
	DataTxTaskHandle = osThreadNew(DataTxTask, NULL, &DataTxTask_attributes);
  /* add threads, ... */
  /* USER CODE END RTOS_THREADS */

  /* USER CODE BEGIN RTOS_EVENTS */
  /* add events, ... */
  /* USER CODE END RTOS_EVENTS */

}

/* USER CODE BEGIN Header_StartDefaultTask */
/**
  * @brief  Function implementing the defaultTask thread.
  * @param  argument: Not used
  * @retval None
  */
/* USER CODE END Header_StartDefaultTask */
void StartDefaultTask(void *argument)
{
  /* USER CODE BEGIN StartDefaultTask */
  /* Infinite loop */
  for(;;)
  {
    osDelay(1);
  }
  /* USER CODE END StartDefaultTask */
}

/* Private application code --------------------------------------------------*/
/* USER CODE BEGIN Application */
  /* LED test */
void StartLEDTask(void *argument)
{
  for(;;)
  {
		HAL_GPIO_WritePin(LED_GPIO_Port, LED_Pin, GPIO_PIN_RESET);
		osDelay(100);
		HAL_GPIO_WritePin(LED_GPIO_Port, LED_Pin, GPIO_PIN_SET);
		osDelay(100);
  }
}

/* AD code */
void StartADTask(void *argument)
{
	uint8_t CD_Channel = 0;
	uint16_t cmd[2] = {0x0000, 0x1800};
  for(;;)
  {
		CD_Control(CD_Channel);
		for(int i = 0; i < 8; i++){
			CONV_Start();
			CONV_End();
			osDelay(1);
			SPI_CS_Enable();
			HAL_SPI_TransmitReceive_DMA(&hspi1, (uint8_t *)&cmd[0], (uint8_t*)&RData, 1);
			SPI_CS_Disable();
			osDelay(1);
			user_main_printf("%d",i);
			if(RData && 0x0400 != 0 ){
				SPI_CS_Enable();
				HAL_SPI_Transmit_DMA(&hspi1, (uint8_t *)&cmd[1], 1);
				HAL_SPI_Receive_DMA(&hspi1, (uint8_t*)&Alert, 1);
				SPI_CS_Disable();
				osDelay(1);
			}
		}
		CD_Channel += 1;
		if(CD_Channel > 7)
			CD_Channel = 0;
  }
}


void DataTxTask(void *argument)
{
	BaseType_t status;
	uint16_t msg;
	for(;;)
	{
		status = xQueueReceive(myDataQueue01Handle, &msg, portMAX_DELAY);
		if(status == pdPASS){
			user_main_printf("The ADC data is %d", msg);
		}
		else
			user_main_printf("No data");
	}
}

void HAL_SPI_TxRxCpltCallback(SPI_HandleTypeDef *hspi){
	
	RData <<= 4;
	RData >>= 4;
	/*xQueueSend(myDataQueue01Handle, &RData, 0);*/
}

/* USER CODE END Application */

