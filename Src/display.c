/*
 * display.c
 *
 *  Created on: Mar 7, 2025
 *      Author: kad112
 */



#include "ssd1306.h"
#include "ssd1306_fonts.h"
#include "joystick_task.h"
#include <stdio.h>

void display_task_execute(void) {

    // Update the display with the new content
    ssd1306_UpdateScreen();
}
