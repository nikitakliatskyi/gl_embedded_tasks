/*
 * input_handler.c
 *
 *  Created on: Feb 27, 2023
 *      Author: Nikita Kliatskyi
 */

#include "input_handler.h"
#include "app_data.h"
#include "main.h"

#define DUTY_CYCLE_STEP .05f

static uint32_t prescaler_modifier = 2;

static float duty_cycle_modifier = .5f;

static unsigned int channels[] = { TIM_CHANNEL_1, TIM_CHANNEL_2, TIM_CHANNEL_3, TIM_CHANNEL_4 };
static uint32_t led_index = 0;

void HAL_GPIO_EXTI_Callback(uint16_t GPIO_Pin) {
	switch(GPIO_Pin)
	{
		case GPIO_PIN_9:	// frequency up
			if(prescaler_modifier < 4) {
				appData.Prescaler = appData.MaxPrescaler / (++prescaler_modifier);
			}
		break;

		case GPIO_PIN_11:	// frequency down
			if(prescaler_modifier > 1) {
				appData.Prescaler = appData.MaxPrescaler / (--prescaler_modifier);
			}
		break;

		case GPIO_PIN_6:	// duty_cycle up
			duty_cycle_modifier += DUTY_CYCLE_STEP;
			appData.DutyCycle = appData.MaxDutyCycle * duty_cycle_modifier;
		break;

		case GPIO_PIN_8:	// duty_cycle down
			duty_cycle_modifier -= DUTY_CYCLE_STEP;
			appData.DutyCycle = appData.MaxDutyCycle * duty_cycle_modifier;
		break;

		case GPIO_PIN_15:	// change led
			led_index = (led_index + 1) % 4;
			appData.Channel = channels[led_index];
		break;

		default:
			return;
			__NOP();
		break;
	}
	appData.NeedsUpdate = 1;
}
