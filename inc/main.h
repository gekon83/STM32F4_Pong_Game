/*
 * main.h
 *
 *  Created on: 21 lut 2020
 *      Author: grzko
 */

#ifndef MAIN_H_
#define MAIN_H_

void Error_Handler(void);


#define Button_Blue_Pin GPIO_PIN_0
#define Button_Blue_GPIO_Port GPIOA
#define Button_Blue_EXTI_IRQn EXTI0_IRQn
#define Button_Joystick_Pin GPIO_PIN_3
#define Button_Joystick_GPIO_Port GPIOA
#define Button_Joystick_EXTI_IRQn EXTI3_IRQn

//------------ LED --------------
#define LED_Green_Pin GPIO_PIN_12
#define LED_Green_GPIO_Port GPIOD

#define LED_Orange_Pin GPIO_PIN_13
#define LED_Orange_GPIO_Port GPIOD

#define LED_Red_Pin GPIO_PIN_14
#define LED_Red_GPIO_Port GPIOD

#define LED_Blue_Pin GPIO_PIN_15
#define LED_Blue_GPIO_Port GPIOD

#define LED_GPIO_Port GPIOD
//-------------------------------

// ------------ OLED ------------
#define SCK_Pin GPIO_PIN_5
#define SCK_GPIO_Port GPIOA

#define MOSI_Pin GPIO_PIN_7
#define MOSI_GPIO_Port GPIOA

#define CS_Pin GPIO_PIN_5
#define CS_GPIO_Port GPIOC

#define DC_Pin GPIO_PIN_1
#define DC_GPIO_Port GPIOB

#define RES_Pin GPIO_PIN_7
#define RES_GPIO_Port GPIOE
//-------------------------------

#endif /* MAIN_H_ */
