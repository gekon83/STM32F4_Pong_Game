/*
 * pong.c
 *
 *  Created on: 23 lut 2020
 *      Author: grzko
 */

#include "pong.h"


/***************************************************** objects interactions */
void checkCollisions(Ball *ball, Frame *frame) {

	if (Ball_getMinX(ball) <= Frame_getMinX(frame)) {

		Ball_bounceRight(ball);

	} else if (Ball_getMaxX(ball) >= Frame_getMaxX(frame)) {

		Ball_bounceLeft(ball);

	}

	if (Ball_getMinY(ball) <= Frame_getMinY(frame)) {

		Ball_bounceUp(ball);

	} else if (Ball_getMaxY(ball) >= Frame_getMaxY(frame)) {

		Ball_bounceDown(ball);

	}
}
