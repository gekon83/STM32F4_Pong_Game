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
#include "SSD1331.h"

SPI_HandleTypeDef hspi1;
uint8_t myY = 10;
uint8_t myX = 10;
char strX[10];
char strY[10];


void MX_GPIO_Init(void);
void MX_SPI1_Init(void);

void delay (int time)
{
	for (int i=0; i<time*570; ++i) {}
}

int main(void)
{
	HAL_Init();

	// initialization
	MX_GPIO_Init();
	MX_SPI1_Init();

	// OLED setup
	ssd1331_init();
	ssd1331_clear_screen(BLACK);
	ssd1331_draw_rect(0,0,95,63,GREEN);

	while(1)
	{
		HAL_GPIO_TogglePin(LED_Blue_GPIO_Port, LED_Blue_Pin);

		// clear OLED
		ssd1331_display_string(20, 10, (const uint8_t *) strX, FONT_1608, BLACK);
		ssd1331_display_string(20, 30, (const uint8_t *) strY, FONT_1608, BLACK);
		ssd1331_draw_circle(myX,myY,5,BLACK);

		myX += 2; //96
		myY += 2; //62

		sprintf(strX, "X:%d", myX);
		sprintf(strY, "Y:%d", myY);

		ssd1331_display_string(20, 10, (const uint8_t *) strX, FONT_1608, RED);
		ssd1331_display_string(20, 30, (const uint8_t *) strY, FONT_1608, GREEN);
		ssd1331_draw_circle(myX,myY,5,YELLOW);

		//ssd1331_draw_rect(0,0,myX,myY,GREEN);

		HAL_Delay(300);

		/*
		 *
		HAL_GPIO_TogglePin(LED_Blue_GPIO_Port, LED_Blue_Pin);

		sprintf(strX, "X:%d", myX);
		sprintf(strY, "Y:%d", myY);
		ssd1331_draw_circle(myX,myY,5,YELLOW);
		//ssd1331_draw_rect(0,0,myX,myY,GREEN);
		ssd1331_display_string(20, 10, (const uint8_t *) strX, FONT_1608, RED);
		ssd1331_display_string(20, 30, (const uint8_t *) strY, FONT_1608, GREEN);
		HAL_Delay(500);
		ssd1331_display_string(20, 10, (const uint8_t *) strX, FONT_1608, BLACK);
		ssd1331_display_string(20, 30, (const uint8_t *) strY, FONT_1608, BLACK);
		ssd1331_draw_circle(myX,myY,5,BLACK);
		myX += 2; //96
		myY += 2; //62
		 */
	}
}
//-----------------------------------
void MX_GPIO_Init(void)
{
	GPIO_InitTypeDef gpio;

	/* GPIO Ports Clock Enable */
	__HAL_RCC_GPIOA_CLK_ENABLE();
	__HAL_RCC_GPIOB_CLK_ENABLE();
	__HAL_RCC_GPIOC_CLK_ENABLE();
	__HAL_RCC_GPIOD_CLK_ENABLE();
	__HAL_RCC_GPIOE_CLK_ENABLE();

	/*Configure LED GPIO*/
	gpio.Pin = LED_Green_Pin | LED_Orange_Pin | LED_Red_Pin | LED_Blue_Pin;
	gpio.Mode = GPIO_MODE_OUTPUT_PP;
	gpio.Pull = GPIO_NOPULL;
	gpio.Speed = GPIO_SPEED_FREQ_LOW;
	HAL_GPIO_Init(LED_GPIO_Port, &gpio);

	/*Configure GPIO pin Output Level */
	HAL_GPIO_WritePin(CS_GPIO_Port, CS_Pin, GPIO_PIN_RESET);
	HAL_GPIO_WritePin(DC_GPIO_Port, DC_Pin, GPIO_PIN_RESET);
	HAL_GPIO_WritePin(RES_GPIO_Port, RES_Pin, GPIO_PIN_RESET);

	/*Configure GPIO pin : CS_Pin */
	gpio.Pin = CS_Pin;
	//gpio.Pin = CS_Pin | DC_Pin | RES_Pin;
	gpio.Mode = GPIO_MODE_OUTPUT_PP;
	gpio.Pull = GPIO_NOPULL;
	gpio.Speed = GPIO_SPEED_FREQ_LOW;
	HAL_GPIO_Init(CS_GPIO_Port, &gpio);

	/*Configure GPIO pin : DC_Pin */
	gpio.Pin = DC_Pin;
	gpio.Mode = GPIO_MODE_OUTPUT_PP;
	gpio.Pull = GPIO_NOPULL;
	gpio.Speed = GPIO_SPEED_FREQ_LOW;
	HAL_GPIO_Init(DC_GPIO_Port, &gpio);

	/*Configure GPIO pin : RES_Pin */
	gpio.Pin = RES_Pin;
	gpio.Mode = GPIO_MODE_OUTPUT_PP;
	gpio.Pull = GPIO_NOPULL;
	gpio.Speed = GPIO_SPEED_FREQ_LOW;
	HAL_GPIO_Init(RES_GPIO_Port, &gpio);

    /**SPI1 GPIO Configuration
    PA5     ------> SPI1_SCK
    PA7     ------> SPI1_MOSI
    */
    gpio.Pin = SCK_Pin|MOSI_Pin;
    gpio.Mode = GPIO_MODE_AF_PP;
    gpio.Pull = GPIO_NOPULL;
    gpio.Speed = GPIO_SPEED_FREQ_VERY_HIGH;
    gpio.Alternate = GPIO_AF5_SPI1;
    HAL_GPIO_Init(GPIOA, &gpio);
}

void MX_SPI1_Init(void)
{
    __HAL_RCC_SPI1_CLK_ENABLE();

	/* SPI1 parameter configuration*/
	hspi1.Instance = SPI1;
	hspi1.Init.Mode = SPI_MODE_MASTER;
	hspi1.Init.Direction = SPI_DIRECTION_2LINES;
	hspi1.Init.DataSize = SPI_DATASIZE_8BIT;
	hspi1.Init.CLKPolarity = SPI_POLARITY_HIGH;
	hspi1.Init.CLKPhase = SPI_PHASE_2EDGE;
	hspi1.Init.NSS = SPI_NSS_SOFT;
	hspi1.Init.BaudRatePrescaler = SPI_BAUDRATEPRESCALER_2;
	hspi1.Init.FirstBit = SPI_FIRSTBIT_MSB;
	hspi1.Init.TIMode = SPI_TIMODE_DISABLE;
	hspi1.Init.CRCCalculation = SPI_CRCCALCULATION_DISABLE;
	hspi1.Init.CRCPolynomial = 10;

	HAL_SPI_Init(&hspi1);

	__HAL_SPI_ENABLE(&hspi1);
}

