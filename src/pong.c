/*
 * pong.c
 *
 *  Created on: 23 lut 2020
 *      Author: grzko
 */

#include "pong.h"

void setupFrameItem(struct FrameItem *item, int minX, int maxX, int minY, int maxY) {
	item->minX = minX;
	item->maxX = maxX;
	item->minY = minY;
	item->maxY = maxY;
}

void setupBallItem(struct BallItem *item, int x, int y, int vx, int vy, int radius) {
	item->x = x;
	item->y = y;
	item->vx = vx;
	item->vy = vy;
	item->radius = radius;
}

void checkCollisions(struct BallItem *ballItem, struct FrameItem *frameItem) {

	if (ballItem->x - ballItem->radius <= frameItem->minX) {

	    //dx = ballItem->x - ballItem->radius - frameItem->minX;
		ballItem->vx = (ballItem->vx < 0 ? ballItem->vx : -ballItem->vx);
	    //vx *= factor;

	} else if (ballItem->x + ballItem->radius >= frameItem->maxX) {

		//dx = ballItem->x + ballItem->radius - frameItem->maxX;
		ballItem->vx = (ballItem->vx > 0 ? -ballItem->vx : ballItem->vx);
		//vx *= factor;

	}

	if (ballItem->y - ballItem->radius <= frameItem->minY) {

		//dy = ballItem->y - ballItem->radius - frameItem->minY;
		ballItem->vy = (ballItem->vy < 0 ? ballItem->vy : -ballItem->vy);
	    //vx *= factor;

	} else if (ballItem->y + ballItem->radius >= frameItem->maxY) {

		//dy = ballItem->y + ballItem->radius - frameItem->maxY;
		ballItem->vy = (ballItem->vy > 0 ? -ballItem->vy : ballItem->vy);
		//vx *= factor;

	}
}
