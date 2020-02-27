/*
 * frame.h
 *
 *  Created on: 27 lut 2020
 *      Author: grzko
 */

#ifndef FRAME_H_
#define FRAME_H_

#include "stdint.h"

typedef struct {
	uint8_t minX;
	uint8_t maxX;
	uint8_t minY;
	uint8_t maxY;
} Frame;

/************************************************************** constructor */
void Frame_ctor(Frame *me, uint8_t minX, uint8_t maxX, uint8_t minY, uint8_t maxY);

/****************************************************************** getters */
int8_t Frame_getMinX(Frame * const me);
int8_t Frame_getMaxX(Frame * const me);
int8_t Frame_getMinY(Frame * const me);
int8_t Frame_getMaxY(Frame * const me);

#endif /* FRAME_H_ */
