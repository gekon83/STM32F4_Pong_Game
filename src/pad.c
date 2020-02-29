/*
 * pad.c
 *
 *  Created on: 27 lut 2020
 *      Author: grzko
 */

#include "pad.h"

/************************************************************** constructor */
void Pad_ctor(Pad *me, int8_t x, uint8_t length) {
	me->x = x;
	me->length = length;
}

/***************************************************************** movement */
void Pad_move(Pad *me, uint8_t dx) {
	me->x += dx;
}

/****************************************************************** getters */
int8_t Pad_getMin(Pad * const me)	{	return me->x;	}
int8_t Pad_getMax(Pad * const me)	{	return (me->x + me->length);	}

