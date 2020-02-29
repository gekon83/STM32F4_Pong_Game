/*
 * pad.h
 *
 *  Created on: 27 lut 2020
 *      Author: grzko
 */

#ifndef PAD_H_
#define PAD_H_

#include "stdint.h"

typedef struct {
	int8_t x;
	int8_t length;
} Pad;

/************************************************************** constructor */
void Pad_ctor(Pad *me, int8_t x, uint8_t length);

/***************************************************************** movement */
void Pad_move(Pad *me, uint8_t dx);

/****************************************************************** getters */
int8_t Pad_getMin(Pad * const me);
int8_t Pad_getMax(Pad * const me);

#endif /* PAD_H_ */
