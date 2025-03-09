
/*
 * joystick.c
 *
 *  Created on: Mar 3, 2025
 *      Author: hsu38
 */

#include "joystick_task.h"
#include "adc.h"
#include "ssd1306.h"
#include "ssd1306_fonts.h"
#include <stdio.h> // for snprintf
#include "display.h"

static uint16_t raw_adc[2] = {0, 0};

void joystick_task_init(void)
{

    HAL_ADC_Start_DMA(&hadc1, (uint32_t*)raw_adc, 2);
}



void joystick_task_execute(void)
{
    char x_val[30];
    char y_val[30];
	HAL_ADC_Start_DMA(&hadc1, (uint32_t*)raw_adc, 2);
	void ssd1306_UpdateScreen(void);

	snprintf(x_val, sizeof(x_val), "%u", raw_adc[0]);
	snprintf(y_val, sizeof(y_val), "%u", raw_adc[1]);

	ssd1306_SetCursor(0, 10);
	ssd1306_WriteString(x_val, Font_7x10, White);
	ssd1306_SetCursor(0, 20);
	ssd1306_WriteString(y_val, Font_7x10, White);

}

//uses hal lib to interupt when joystick movement detected
void HAL_ADC_ConvCpltCallback(ADC_HandleTypeDef *hadc)
{
    char x_val[30];
    char y_val[30];

    // Convert ADC values to strings
    snprintf(x_val, sizeof(x_val), "%u", raw_adc[0]);
    snprintf(y_val, sizeof(y_val), "%u", raw_adc[1]);
    ssd1306_WriteString("Hello group", Font_7x10, White);
    // move courser down and print x and y vals
    ssd1306_SetCursor(0, 10);
    ssd1306_WriteString(x_val, Font_7x10, White);
    ssd1306_SetCursor(0, 20);
    ssd1306_WriteString(y_val, Font_7x10, White);

}

