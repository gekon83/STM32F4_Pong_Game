/*
 * pong.c
 *
 *  Created on: 23 lut 2020
 *      Author: grzko
 */

#include "pong.h"

static Ball ball;
static Frame frame;

static char strX[10];
static char strY[10];

/*************************************************************** game setup */
void Pong_initScreen()
{
	ssd1331_init();
	ssd1331_clear_screen(BLACK);
}

void Pong_initObjects()
{
	Ball_ctor(&ball, 35, 20, -3, 2, 10);
	Frame_ctor(&frame, 0, 95, 0, 63);
}

/******************************************************* ticker loop action */
void Pong_timerTick()
{
	ssd1331_display_string(20, 10, (const uint8_t *) strX, FONT_1608, BLACK);
	ssd1331_display_string(20, 30, (const uint8_t *) strY, FONT_1608, BLACK);

	ssd1331_draw_circle(Ball_getX(&ball), Ball_getY(&ball), Ball_getRadius(&ball), BLACK);

	ssd1331_draw_rect(Frame_getMinX(&frame),
					  Frame_getMinY(&frame),
					  Frame_getMaxX(&frame),
					  Frame_getMaxY(&frame),GREEN);

	Pong_collisions(&ball, &frame);

	Ball_move(&ball);

	sprintf(strX, "vx:%d", Ball_getVx(&ball));
	sprintf(strY, "vy:%d", Ball_getVy(&ball));

	ssd1331_display_string(20, 10, (const uint8_t *) strX, FONT_1608, RED);
	ssd1331_display_string(20, 30, (const uint8_t *) strY, FONT_1608, GREEN);

	ssd1331_draw_circle(Ball_getX(&ball), Ball_getY(&ball), Ball_getRadius(&ball), YELLOW);
}

/***************************************************** objects interactions */
void Pong_collisions(Ball *ball, Frame *frame)
{

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
