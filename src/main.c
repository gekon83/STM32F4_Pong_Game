/**
  ******************************************************************************
  * @file    main.c
  * @author  Ac6
  * @version V1.0
  * @date    01-December-2013
  * @brief   Default main function.
  ******************************************************************************
*/

#include "stm32f4xx.h"
#include "main.h"

void MX_GPIO_Init(void);

void delay (int time)
{
	for (int i=0; i<time*570; ++i) {}
}

int main(void)
{
	HAL_Init();

	__HAL_RCC_GPIOD_CLK_ENABLE();

	MX_GPIO_Init();


	while(1)
	{
		HAL_GPIO_WritePin(GPIOD, LED_Green_Pin, GPIO_PIN_SET);
		delay(300);
		HAL_GPIO_WritePin(GPIOD, LED_Orange_Pin, GPIO_PIN_SET);
		delay(300);
		HAL_GPIO_WritePin(GPIOD, LED_Red_Pin, GPIO_PIN_SET);
		delay(300);
		HAL_GPIO_WritePin(GPIOD, LED_Blue_Pin, GPIO_PIN_SET);
		delay(300);
		HAL_GPIO_WritePin(GPIOD, LED_Green_Pin, GPIO_PIN_RESET);
		delay(600);
		HAL_GPIO_WritePin(GPIOD, LED_Orange_Pin, GPIO_PIN_RESET);
		delay(600);
		HAL_GPIO_WritePin(GPIOD, LED_Red_Pin, GPIO_PIN_RESET);
		delay(600);
		HAL_GPIO_WritePin(GPIOD, LED_Blue_Pin, GPIO_PIN_RESET);
		delay(600);
	}
}
//-----------------------------------
void MX_GPIO_Init(void)
{
	GPIO_InitTypeDef gpio;

	/*Configure LED GPIO*/
	gpio.Pin = LED_Green_Pin | LED_Orange_Pin | LED_Red_Pin | LED_Blue_Pin;
	gpio.Mode = GPIO_MODE_OUTPUT_PP;
	gpio.Pull = GPIO_NOPULL;
	gpio.Speed = GPIO_SPEED_FREQ_LOW;
	HAL_GPIO_Init(LED_GPIO_Port, &gpio);
}
//-----------------------------------
