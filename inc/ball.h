/*
 * ball.h
 *
 *  Created on: 27 lut 2020
 *      Author: grzko
 */

#ifndef BALL_H_
#define BALL_H_

#include "stdint.h"

typedef struct {
	int8_t x;			/* x-coordinate of ball */
	int8_t y;			/* y-coordinate of ball */
	int8_t vx;			/* vx-speed of ball */
	int8_t vy;			/* vy-speed of ball */
	uint8_t radius;		/* radius of ball */
} Ball;

/************************************************************** constructor */
void Ball_ctor(Ball *me, int8_t x, int8_t y, int8_t vx, int8_t vy, uint8_t radius);

/***************************************************************** movement */
//void Ball_move(Ball *me, int8_t dx, int8_t dy);
void Ball_move(Ball *me);
void Ball_bounceLeft(Ball *me);
void Ball_bounceRight(Ball *me);
void Ball_bounceDown(Ball *me);
void Ball_bounceUp(Ball *me);

/****************************************************************** getters */
int8_t Ball_getX(Ball * const me);
int8_t Ball_getY(Ball * const me);
int8_t Ball_getVx(Ball * const me);
int8_t Ball_getVy(Ball * const me);
int8_t Ball_getRadius(Ball * const me);

int8_t Ball_getMinX(Ball * const me);
int8_t Ball_getMaxX(Ball * const me);
int8_t Ball_getMinY(Ball * const me);
int8_t Ball_getMaxY(Ball * const me);

#endif /* BALL_H_ */
