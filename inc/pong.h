/*
 * pong.h
 *
 *  Created on: 23 lut 2020
 *      Author: grzko
 */

#ifndef PONG_H_
#define PONG_H_


#include "stdint.h"

struct BallItem {
	uint8_t x;
	uint8_t y;
	uint8_t vx;
	uint8_t vy;
	uint8_t radius;
};

struct FrameItem {
	uint8_t minX;
	uint8_t maxX;
	uint8_t minY;
	uint8_t maxY;
};

void setupFrameItem(struct FrameItem *item, int minX, int maxX, int minY, int maxY);
void setupBallItem(struct BallItem *item, int x, int y, int vx, int vy, int radius);

void checkCollisions(struct BallItem *ballItem, struct FrameItem *frameItem);


#endif /* PONG_H_ */
