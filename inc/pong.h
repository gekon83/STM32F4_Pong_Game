/*
 * pong.h
 *
 *  Created on: 23 lut 2020
 *      Author: grzko
 */

#ifndef PONG_H_
#define PONG_H_

/*  OLED library  */
#include "SSD1331.h"

#include "ball.h"
#include "frame.h"
#include "pad.h"


/*************************************************************** game setup */
void Pong_initScreen(void);
void Pong_initObjects(void);

/******************************************************* ticker loop action */
void Pong_timerTick(void);

/***************************************************** objects interactions */
void Pong_collisions(Ball *ball, Frame *frame);

/********************************************************** joystick output */
void Pong_joystick(void);

#endif /* PONG_H_ */
