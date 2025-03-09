/*
 * blinky.c
 *
 *  Created on: Mar 3, 2025
 *      Author: hsu38
 */

#include "gpio.h"

void blinky_task_execute() {
	HAL_GPIO_TogglePin(GPIOA, GPIO_PIN_5);
}
