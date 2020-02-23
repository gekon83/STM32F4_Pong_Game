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
#include "pong.h"

// ===================================== private variables

SPI_HandleTypeDef hspi1;
TIM_HandleTypeDef htim10;

char strX[10];
char strY[10];

struct BallItem ball;
struct FrameItem frame;

// ===================================== private functions

// ===================================== initialization functions (declarations)
void MX_GPIO_Init(void);
void MX_SPI1_Init(void);
void SystemClock_Config(void);
void MX_TIM10_Init(void);

void HAL_TIM_PeriodElapsedCallback(TIM_HandleTypeDef * htim);

// ===================================== main
int main(void)
{
	HAL_Init();

	SystemClock_Config();

	// initialization
	MX_GPIO_Init();
	MX_SPI1_Init();

	// Pong setup
	setupFrameItem(&frame, 0, 95, 0, 63);
	setupBallItem(&ball, 35, 20, 3, 2, 10);

	// OLED setup
	ssd1331_init();
	ssd1331_clear_screen(BLACK);
	//ssd1331_draw_rect(0,0,95,63,GREEN);

	MX_TIM10_Init();
	HAL_NVIC_EnableIRQ(TIM1_UP_TIM10_IRQn);

	while(1) {}
}

// ===================================== initialization functions (definitions)
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

	if (HAL_SPI_Init(&hspi1) != HAL_OK)
	{
		Error_Handler();
	}

	__HAL_SPI_ENABLE(&hspi1);
}

void SystemClock_Config(void)
{
	RCC_OscInitTypeDef rccOsc;
	RCC_ClkInitTypeDef rccClk;

	// Configure the main internal regulator output voltage
	__HAL_RCC_PWR_CLK_ENABLE();
	__HAL_PWR_VOLTAGESCALING_CONFIG(PWR_REGULATOR_VOLTAGE_SCALE1);

	// Initializes the CPU, AHB and APB busses clocks
	rccOsc.OscillatorType = RCC_OSCILLATORTYPE_HSI;
	rccOsc.HSIState = RCC_HSI_ON;
	rccOsc.HSICalibrationValue = RCC_HSICALIBRATION_DEFAULT;
	rccOsc.PLL.PLLState = RCC_PLL_ON;
	rccOsc.PLL.PLLSource = RCC_PLLSOURCE_HSI;
	rccOsc.PLL.PLLM = 8;
	rccOsc.PLL.PLLN = 100;
	rccOsc.PLL.PLLP = RCC_PLLP_DIV2;
	rccOsc.PLL.PLLQ = 4;

	if (HAL_RCC_OscConfig(&rccOsc) != HAL_OK)
	{
		Error_Handler();
	}

	// Initializes the CPU, AHB and APB busses clocks
	rccClk.ClockType = RCC_CLOCKTYPE_HCLK|RCC_CLOCKTYPE_SYSCLK
							  |RCC_CLOCKTYPE_PCLK1|RCC_CLOCKTYPE_PCLK2;
	rccClk.SYSCLKSource = RCC_SYSCLKSOURCE_PLLCLK;
	rccClk.AHBCLKDivider = RCC_SYSCLK_DIV1;
	rccClk.APB1CLKDivider = RCC_HCLK_DIV2;
	rccClk.APB2CLKDivider = RCC_HCLK_DIV1;

	if (HAL_RCC_ClockConfig(&rccClk, FLASH_LATENCY_3) != HAL_OK)
	{
		Error_Handler();
	}
}

void MX_TIM10_Init(void)
{
	__HAL_RCC_TIM10_CLK_ENABLE();

	htim10.Instance = TIM10;
	htim10.Init.Prescaler = 10000 - 1;
	htim10.Init.CounterMode = TIM_COUNTERMODE_UP;
	htim10.Init.Period = 500 - 1;
	htim10.Init.ClockDivision = TIM_CLOCKDIVISION_DIV1;
	//htim10.Init.AutoReloadPreload = TIM_AUTORELOAD_PRELOAD_DISABLE;
	if (HAL_TIM_Base_Init(&htim10) != HAL_OK)
	{
		Error_Handler();
	}

    /* TIM10 interrupt Init */
    HAL_NVIC_SetPriority(TIM1_UP_TIM10_IRQn, 0, 0);
    HAL_NVIC_EnableIRQ(TIM1_UP_TIM10_IRQn);

	HAL_TIM_Base_Start_IT(&htim10);
}

void HAL_TIM_PeriodElapsedCallback(TIM_HandleTypeDef * htim)
{
	static uint8_t counter = 0;
	counter++;

    if(htim->Instance == TIM10)
    {
    	/* changing timer10 settings (test)
    	if (counter >= 10) {
    		counter = 0;
    		htim10.Init.Period = htim10.Init.Period < 299 ? 299 : 199;
    		HAL_TIM_Base_Init(&htim10);
    	}
    	*/

    	HAL_GPIO_TogglePin(LED_Blue_GPIO_Port, LED_Blue_Pin);

		// clear OLED
		ssd1331_display_string(20, 10, (const uint8_t *) strX, FONT_1608, BLACK);
		ssd1331_display_string(20, 30, (const uint8_t *) strY, FONT_1608, BLACK);

		ssd1331_draw_circle(ball.x, ball.y, ball.radius, BLACK);
		ssd1331_draw_rect(0,0,95,63,GREEN);

		checkCollisions(&ball, &frame);

		ball.x += ball.vx; //96
		ball.y += ball.vy; //62

		sprintf(strX, "x:%d", ball.x);
		sprintf(strY, "y:%d", ball.y);

		ssd1331_display_string(20, 10, (const uint8_t *) strX, FONT_1608, RED);
		ssd1331_display_string(20, 30, (const uint8_t *) strY, FONT_1608, GREEN);

		ssd1331_draw_circle(ball.x, ball.y, ball.radius, YELLOW);

    }
}

void Error_Handler(void)
{
	HAL_GPIO_WritePin(LED_Red_GPIO_Port, LED_Red_Pin, SET);
}
