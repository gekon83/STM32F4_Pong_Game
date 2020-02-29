/**
  ******************************************************************************
  * @file    main.c
  * @author  Ac6
  * @version V1.0
  * @date    01-December-2013
  * @brief   Default main function.
  ******************************************************************************
	 * to do list:
	 * 		xxx implement bluetooth communications
	 * 		xxx implement pad control
	 * 		xxx use polimorphism for all drawn shapes (virtual draw and erase function)
  ******************************************************************************
*/

#include "stm32f4xx.h"
#include "main.h"
#include "pong.h"

#define ADC_RESOLUTION 4095
//#define LOWER_TRESH (25*ADC_RESOLUTION)/100
//#define UPPER_TRESH (75*ADC_RESOLUTION)/100

// ===================================== private variables

SPI_HandleTypeDef hspi1;
ADC_HandleTypeDef hadc1;
DMA_HandleTypeDef hdma_adc1;
TIM_HandleTypeDef htim10;

uint16_t joystick[2];

// ===================================== private functions

// ===================================== initialization functions (declarations)
static void MX_GPIO_Init(void);
static void MX_SPI1_Init(void);
static void MX_DMA_Init(void);
static void MX_ADC1_Init(void);
void SystemClock_Config(void);
static void MX_TIM10_Init(void);


// ===================================== interrupts
void HAL_TIM_PeriodElapsedCallback(TIM_HandleTypeDef * htim);
void HAL_GPIO_EXTI_Callback(uint16_t GPIO_Pin);

// ===================================== main
int main(void)
{
	HAL_Init();

	SystemClock_Config();

	// initialization
	MX_GPIO_Init();
	MX_SPI1_Init();

	MX_DMA_Init();
	MX_ADC1_Init();
	HAL_ADC_Start_DMA(&hadc1, (uint32_t*) joystick, 2);

	/* init screen */
	//ssd1331_init();
	//ssd1331_clear_screen(BLACK);
	//__SSD1331_RES_SET();  //RES set
	HAL_GPIO_WritePin(RES_GPIO_Port, RES_Pin, GPIO_PIN_SET);
	//__SSD1331_CS_SET();
	HAL_GPIO_WritePin(CS_GPIO_Port, CS_Pin, GPIO_PIN_SET);

	Pong_initScreen();
	Pong_initObjects();

	MX_TIM10_Init();
	HAL_NVIC_EnableIRQ(TIM1_UP_TIM10_IRQn);

	while(1) {}
}

// ===================================== initialization functions (definitions)
static void MX_GPIO_Init(void)
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





    /*Configure GPIO pin : Button_Blue_Pin */
    gpio.Pin = Button_Blue_Pin;
    gpio.Mode = GPIO_MODE_IT_RISING;
    gpio.Pull = GPIO_NOPULL;
    HAL_GPIO_Init(Button_Blue_GPIO_Port, &gpio);

    /*Configure GPIO pin : Button_Joystick_Pin */
    gpio.Pin = Button_Joystick_Pin;
    gpio.Mode = GPIO_MODE_IT_RISING;
    gpio.Pull = GPIO_PULLUP;
    HAL_GPIO_Init(Button_Joystick_GPIO_Port, &gpio);

    /* EXTI interrupt init*/
    HAL_NVIC_SetPriority(EXTI0_IRQn, 0, 0);
    HAL_NVIC_EnableIRQ(EXTI0_IRQn);

    HAL_NVIC_SetPriority(EXTI3_IRQn, 0, 0);
    HAL_NVIC_EnableIRQ(EXTI3_IRQn);
}

static void MX_SPI1_Init(void)
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

static void MX_DMA_Init(void)
{
	// DMA controller clock enable
	__HAL_RCC_DMA2_CLK_ENABLE();

	// DMA interrupt init
	// DMA2_Stream0_IRQn interrupt configuration
	HAL_NVIC_SetPriority(DMA2_Stream0_IRQn, 0, 0);
	HAL_NVIC_EnableIRQ(DMA2_Stream0_IRQn);
}

static void MX_ADC1_Init(void)
{
	ADC_ChannelConfTypeDef sConfig;

	// Configure the global features of the ADC (Clock, Resolution, Data Alignment and number of conversion)
	hadc1.Instance = ADC1;
	hadc1.Init.ClockPrescaler = ADC_CLOCK_SYNC_PCLK_DIV8;
	hadc1.Init.Resolution = ADC_RESOLUTION_12B;
	hadc1.Init.ScanConvMode = ENABLE;
	hadc1.Init.ContinuousConvMode = ENABLE;
	hadc1.Init.DiscontinuousConvMode = DISABLE;
	hadc1.Init.ExternalTrigConvEdge = ADC_EXTERNALTRIGCONVEDGE_NONE;
	hadc1.Init.ExternalTrigConv = ADC_SOFTWARE_START;
	hadc1.Init.DataAlign = ADC_DATAALIGN_RIGHT;
	hadc1.Init.NbrOfConversion = 2;
	hadc1.Init.DMAContinuousRequests = ENABLE;
	hadc1.Init.EOCSelection = ADC_EOC_SINGLE_CONV;

	if (HAL_ADC_Init(&hadc1) != HAL_OK)
	{
		Error_Handler();
	}

	// Configure for the selected ADC regular channel its corresponding rank in the sequencer and its sample time.
	sConfig.Channel = ADC_CHANNEL_1;
	sConfig.Rank = 1;
	sConfig.SamplingTime = ADC_SAMPLETIME_480CYCLES;

	if (HAL_ADC_ConfigChannel(&hadc1, &sConfig) != HAL_OK)
	{
		Error_Handler();
	}

	// Configure for the selected ADC regular channel its corresponding rank in the sequencer and its sample time.
	sConfig.Channel = ADC_CHANNEL_2;
	sConfig.Rank = 2;

	if (HAL_ADC_ConfigChannel(&hadc1, &sConfig) != HAL_OK)
	{
		Error_Handler();
	}
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

static void MX_TIM10_Init(void)
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

void HAL_ADC_MspInit(ADC_HandleTypeDef* hadc)
{
  GPIO_InitTypeDef GPIO_InitStruct = {0};
  if(hadc->Instance==ADC1)
  {
  /* USER CODE BEGIN ADC1_MspInit 0 */

  /* USER CODE END ADC1_MspInit 0 */
    /* Peripheral clock enable */
    __HAL_RCC_ADC1_CLK_ENABLE();

    __HAL_RCC_GPIOA_CLK_ENABLE();
    /**ADC1 GPIO Configuration
    PA1     ------> ADC1_IN1
    PA2     ------> ADC1_IN2
    */
    GPIO_InitStruct.Pin = GPIO_PIN_1|GPIO_PIN_2;
    GPIO_InitStruct.Mode = GPIO_MODE_ANALOG;
    GPIO_InitStruct.Pull = GPIO_NOPULL;
    HAL_GPIO_Init(GPIOA, &GPIO_InitStruct);

    /* ADC1 DMA Init */
    /* ADC1 Init */
    hdma_adc1.Instance = DMA2_Stream0;
    hdma_adc1.Init.Channel = DMA_CHANNEL_0;
    hdma_adc1.Init.Direction = DMA_PERIPH_TO_MEMORY;
    hdma_adc1.Init.PeriphInc = DMA_PINC_DISABLE;
    hdma_adc1.Init.MemInc = DMA_MINC_ENABLE;
    hdma_adc1.Init.PeriphDataAlignment = DMA_PDATAALIGN_HALFWORD;
    hdma_adc1.Init.MemDataAlignment = DMA_MDATAALIGN_HALFWORD;
    hdma_adc1.Init.Mode = DMA_CIRCULAR;
    hdma_adc1.Init.Priority = DMA_PRIORITY_LOW;
    hdma_adc1.Init.FIFOMode = DMA_FIFOMODE_DISABLE;
    if (HAL_DMA_Init(&hdma_adc1) != HAL_OK)
    {
      Error_Handler();
    }

    __HAL_LINKDMA(hadc,DMA_Handle,hdma_adc1);

  /* USER CODE BEGIN ADC1_MspInit 1 */

  /* USER CODE END ADC1_MspInit 1 */
  }

}

/**
* @brief ADC MSP De-Initialization
* This function freeze the hardware resources used in this example
* @param hadc: ADC handle pointer
* @retval None
*/

void HAL_ADC_MspDeInit(ADC_HandleTypeDef* hadc)
{
  if(hadc->Instance==ADC1)
  {
  /* USER CODE BEGIN ADC1_MspDeInit 0 */

  /* USER CODE END ADC1_MspDeInit 0 */
    /* Peripheral clock disable */
    __HAL_RCC_ADC1_CLK_DISABLE();

    /**ADC1 GPIO Configuration
    PA1     ------> ADC1_IN1
    PA2     ------> ADC1_IN2
    */
    HAL_GPIO_DeInit(GPIOA, GPIO_PIN_1|GPIO_PIN_2);

    /* ADC1 DMA DeInit */
    HAL_DMA_DeInit(hadc->DMA_Handle);
  /* USER CODE BEGIN ADC1_MspDeInit 1 */

  /* USER CODE END ADC1_MspDeInit 1 */
  }

}

// ===================================== interrupts
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

    	Pong_timerTick();

    }
}

void HAL_GPIO_EXTI_Callback(uint16_t GPIO_Pin) {

	if (GPIO_Pin == Button_Joystick_Pin) {
		HAL_GPIO_TogglePin(LED_Green_GPIO_Port, LED_Green_Pin);
	} else if (GPIO_Pin == Button_Blue_Pin) {
		HAL_GPIO_TogglePin(LED_Orange_GPIO_Port, LED_Orange_Pin);
	}
}

void Error_Handler(void)
{
	HAL_GPIO_WritePin(LED_Red_GPIO_Port, LED_Red_Pin, SET);
}


