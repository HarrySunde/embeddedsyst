/*
 * app.c
 *
 *  Created on: Feb 24, 2025
 *      Author: hsu38
 */
#include <stdio.h>
#include "gpio.h"
#include "buttons.h"
#include "adc.h"
#include "joystick_task.h"
#include "button_task.h"
#include "blinky.h"
#include "display.h"
#include "ssd1306.h"
#include "ssd1306_fonts.h"
#include "i2c.h"

#define TICK_FREQUENCY_HZ 1000
#define HZ_TO_TICKS(FREQUENCY_HZ) (TICK_FREQUENCY_HZ/FREQUENCY_HZ)

#define TASK_BUTTON_FREQUENCY_HZ 200
#define TASK_DISPLAY_FREQUENCY_HZ 4
#define TASK_LED_FREQUENCY_HZ 2
#define TASK_JOYSTICK_FREQUENCY_HZ 200

#define TASK_BUTTON_PERIOD_TICKS (TICK_FREQUENCY_HZ/TASK_BUTTON_FREQUENCY_HZ)
#define TASK_DISPLAY_PERIOD_TICKS (TICK_FREQUENCY_HZ/TASK_DISPLAY_FREQUENCY_HZ)
#define TASK_LED_PERIOD_TICKS (TICK_FREQUENCY_HZ/TASK_LED_FREQUENCY_HZ)
#define TASK_JOYSTICK_PERIOD_TICKS (TICK_FREQUENCY_HZ/TASK_JOYSTICK_FREQUENCY_HZ)


static uint32_t taskButtonNextRun = 0;
static uint32_t taskDisplayNextRun = 0;
static uint32_t taskLEDNextRun = 0;
static uint32_t taskJoystickNextRun = 0;

//getstoring static joystick values here
//static uint16_t raw_adc[2];



//this works and prints out x-y coodinates for joystick, commented out for modularization testing (see joystick_task)
/*
void HAL_ADC_ConvCpltCallback(ADC_HandleTypeDef *hadc)
{
    char x_val[30];
    char y_val[30];

    snprintf(x_val, sizeof(x_val), "%u", raw_adc[0]);
    snprintf(y_val, sizeof(y_val), "%u", raw_adc[1]);
    //need to move cursor down for each line set cursor
    ssd1306_SetCursor(0, 10);
    ssd1306_WriteString(x_val, Font_7x10, White);

    ssd1306_SetCursor(0, 20);
    ssd1306_WriteString(y_val, Font_7x10, White);

}
*/



void app_main()
{
	buttons_init();

	//INIT ssd1306
	ssd1306_Init();
	//we might consider intitiallising x and y variables for cursor so we can iterate rather than hardcode
	ssd1306_SetCursor(0, 0);
	//ssd1306_WriteString("Hello World", Font_7x10, White);
	//comented out HAL_ADC call for testing of joystick task
	//HAL_ADC_Start_DMA(&hadc1, (uint32_t*)raw_adc, 2);
	joystick_task_init();

	taskButtonNextRun = HAL_GetTick() + TASK_BUTTON_PERIOD_TICKS;
	taskDisplayNextRun = HAL_GetTick() + TASK_DISPLAY_PERIOD_TICKS;
	taskLEDNextRun = HAL_GetTick() + TASK_LED_PERIOD_TICKS;
	taskJoystickNextRun = HAL_GetTick() + TASK_JOYSTICK_PERIOD_TICKS;


	while(1){
		uint32_t ticks = HAL_GetTick();

		//HAL_ADC_Start_DMA(&hadc1, (uint32_t*)raw_adc, 2);

		if(ticks > taskButtonNextRun)
		{
			button_task_execute();
			taskButtonNextRun += TASK_BUTTON_PERIOD_TICKS;

		}

		if(ticks > taskDisplayNextRun)
		{
			display_task_execute();
			taskDisplayNextRun += TASK_DISPLAY_PERIOD_TICKS;
		}


		if(ticks > taskJoystickNextRun)
		{
			joystick_task_execute();
			taskJoystickNextRun += TASK_JOYSTICK_PERIOD_TICKS;
		}

		if (ticks > taskLEDNextRun)
		{
			blinky_task_execute();
			taskLEDNextRun += TASK_LED_PERIOD_TICKS;
		}
	}
}

