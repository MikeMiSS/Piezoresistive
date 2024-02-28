#include "CD_Control.h"
#include "stm32f4xx_hal.h"
#include "gpio.h"

#define Channel_0() do{HAL_GPIO_WritePin(CD_A0_GPIO_Port, CD_A0_Pin, GPIO_PIN_RESET);HAL_GPIO_WritePin(CD_A1_GPIO_Port, CD_A1_Pin, GPIO_PIN_RESET);HAL_GPIO_WritePin(CD_A2_GPIO_Port, CD_A2_Pin, GPIO_PIN_RESET);}while(0)
#define Channel_1() do{HAL_GPIO_WritePin(CD_A0_GPIO_Port, CD_A0_Pin, GPIO_PIN_SET);HAL_GPIO_WritePin(CD_A1_GPIO_Port, CD_A1_Pin, GPIO_PIN_RESET);HAL_GPIO_WritePin(CD_A2_GPIO_Port, CD_A2_Pin, GPIO_PIN_RESET);}while(0)
#define Channel_2() do{HAL_GPIO_WritePin(CD_A0_GPIO_Port, CD_A0_Pin, GPIO_PIN_RESET);HAL_GPIO_WritePin(CD_A1_GPIO_Port, CD_A1_Pin, GPIO_PIN_SET);HAL_GPIO_WritePin(CD_A2_GPIO_Port, CD_A2_Pin, GPIO_PIN_RESET);}while(0)
#define Channel_3() do{HAL_GPIO_WritePin(CD_A0_GPIO_Port, CD_A0_Pin, GPIO_PIN_RESET);HAL_GPIO_WritePin(CD_A1_GPIO_Port, CD_A1_Pin, GPIO_PIN_SET);HAL_GPIO_WritePin(CD_A2_GPIO_Port, CD_A2_Pin, GPIO_PIN_SET);}while(0)
#define Channel_4() do{HAL_GPIO_WritePin(CD_A0_GPIO_Port, CD_A0_Pin, GPIO_PIN_SET);HAL_GPIO_WritePin(CD_A1_GPIO_Port, CD_A1_Pin, GPIO_PIN_RESET);HAL_GPIO_WritePin(CD_A2_GPIO_Port, CD_A2_Pin, GPIO_PIN_RESET);}while(0)
#define Channel_5() do{HAL_GPIO_WritePin(CD_A0_GPIO_Port, CD_A0_Pin, GPIO_PIN_SET);HAL_GPIO_WritePin(CD_A1_GPIO_Port, CD_A1_Pin, GPIO_PIN_RESET);HAL_GPIO_WritePin(CD_A2_GPIO_Port, CD_A2_Pin, GPIO_PIN_SET);}while(0)
#define Channel_6() do{HAL_GPIO_WritePin(CD_A0_GPIO_Port, CD_A0_Pin, GPIO_PIN_SET);HAL_GPIO_WritePin(CD_A1_GPIO_Port, CD_A1_Pin, GPIO_PIN_SET);HAL_GPIO_WritePin(CD_A2_GPIO_Port, CD_A2_Pin, GPIO_PIN_RESET);}while(0)
#define Channel_7() do{HAL_GPIO_WritePin(CD_A0_GPIO_Port, CD_A0_Pin, GPIO_PIN_SET);HAL_GPIO_WritePin(CD_A1_GPIO_Port, CD_A1_Pin, GPIO_PIN_SET);HAL_GPIO_WritePin(CD_A2_GPIO_Port, CD_A2_Pin, GPIO_PIN_SET);}while(0)


void CD_Enable(void){
	HAL_GPIO_WritePin(CD_E_GPIO_Port, CD_E_Pin, GPIO_PIN_RESET);
}
	
void CD_Disable(void){
	HAL_GPIO_WritePin(CD_E_GPIO_Port, CD_E_Pin, GPIO_PIN_SET);
}

void CD_Control(uint8_t Channel){
	switch(Channel){
		case 0:
			Channel_0();
			break;
		case 1:
			Channel_1();
			break;
		case 2:
			Channel_2();
			break;
		case 3:
			Channel_3();
			break;
		case 4:
			Channel_4();
			break;
		case 5:
			Channel_5();
			break;
		case 6:
			Channel_6();
			break;
		case 7:
			Channel_7();
			break;
		default:
			break;
	}
}
