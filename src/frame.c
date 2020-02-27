/*
 * frame.c
 *
 *  Created on: 27 lut 2020
 *      Author: grzko
 */

#include "frame.h"

/************************************************************** constructor */
void Frame_ctor(Frame *me, uint8_t minX, uint8_t maxX, uint8_t minY, uint8_t maxY) {
	me->minX = minX;
	me->maxX = maxX;
	me->minY = minY;
	me->maxY = maxY;
}

/****************************************************************** getters */
int8_t Frame_getMinX(Frame * const me)	{	return me->minX;	}
int8_t Frame_getMaxX(Frame * const me)	{	return me->maxX;	}
int8_t Frame_getMinY(Frame * const me)	{	return me->minY;	}
int8_t Frame_getMaxY(Frame * const me)	{	return me->maxY;	}
