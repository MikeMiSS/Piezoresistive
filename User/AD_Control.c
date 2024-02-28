#include "stm32f4xx_hal.h"
#include "AD_Control.h"
#include "CD_Control.h"
#include "spi.h"
#include "cmsis_os.h"
#include "usart.h"

uint16_t cmd[2] = {0x14E8, 0x0CFF};
uint8_t TxBuf[] = "AD INIT SUCCESS";

void MX_AD_Init(void){
	CD_Enable();
	/* config register */
	SPI_CS_Enable();
	HAL_SPI_Transmit_DMA(&hspi1, (uint8_t*)&cmd[0], 1);
	SPI_CS_Disable();
	osDelay(1);
	/* channel register */
	SPI_CS_Enable();
	HAL_SPI_Transmit_DMA(&hspi1, (uint8_t *)&cmd[1],1);
	SPI_CS_Disable();
	osDelay(1);
	HAL_UART_Transmit(&huart1, TxBuf, sizeof(TxBuf), 0xffff);
}
