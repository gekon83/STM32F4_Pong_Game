/*
 * ball.c
 *
 *  Created on: 27 lut 2020
 *      Author: grzko
 */

#include "ball.h"

/************************************************************** constructor */
void Ball_ctor(Ball *me, int8_t x, int8_t y, int8_t vx, int8_t vy, uint8_t radius) {
	me->x = x;
	me->y = y;
	me->vx = vx;
	me->vy = vy;
	me->radius = radius;
}

/***************************************************************** movement */
void Ball_move(Ball *me) {
	me->x += me->vx;
	me->y += me->vy;
}

void Ball_bounceLeft(Ball *me) 	{	me->vx = (me->vx > 0 ? -me->vx : me->vx);	}
void Ball_bounceRight(Ball *me) {	me->vx = (me->vx < 0 ? -me->vx : me->vx);	}
void Ball_bounceDown(Ball *me) 	{	me->vy = (me->vy > 0 ? -me->vy : me->vy);	}
void Ball_bounceUp(Ball *me) 	{	me->vy = (me->vy < 0 ? -me->vy : me->vy);	}

/****************************************************************** getters */
int8_t Ball_getX(Ball * const me)		{	return me->x;	}
int8_t Ball_getY(Ball * const me)		{	return me->y;	}
int8_t Ball_getVx(Ball * const me)		{	return me->vx;	}
int8_t Ball_getVy(Ball * const me)		{	return me->vy;	}
int8_t Ball_getRadius(Ball * const me)	{	return me->radius;	}

int8_t Ball_getMinX(Ball * const me)	{	return (me->x - me->radius);	}
int8_t Ball_getMaxX(Ball * const me)	{	return (me->x + me->radius);	}
int8_t Ball_getMinY(Ball * const me)	{	return (me->y - me->radius);	}
int8_t Ball_getMaxY(Ball * const me)	{	return (me->y + me->radius);	}



