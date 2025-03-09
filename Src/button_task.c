/*
 * button_task.c
 *
 *  Created on: Mar 3, 2025
 *      Author: hsu38
 */

#include "rgb.h"
#include "buttons.h"

void button_task_execute() {
	buttons_update();

	rgb_colour_all_on();

	if (buttons_checkButton(RIGHT)== !NO_CHANGE){
		rgb_led_toggle(RGB_RIGHT);
	}
	if (buttons_checkButton(LEFT)== !NO_CHANGE){
		rgb_led_toggle(RGB_LEFT);
	}
	if (buttons_checkButton(DOWN)== !NO_CHANGE){
		rgb_led_toggle(RGB_DOWN);
	}
	if (buttons_checkButton(UP)== !NO_CHANGE){
		rgb_led_toggle(RGB_UP);
	}
}
