/*
 * scheme_control_buttons_handler.c
 *
 *  Created on: Feb 19, 2023
 *      Author: Nikita Kliatskyi
 */

#include "main.h"
#include "scheme_control_buttons_handler.h"
#include "scheme.h"

void HAL_GPIO_EXTI_Callback(uint16_t GPIO_Pin) {
	switch(GPIO_Pin)
	{
		case GPIO_PIN_9:	// speed up
			if(schemeData.Delay <= 1000 - 50)
			{
				schemeData.Delay += 50;
			}
		break;

		case GPIO_PIN_11:	// speed down
			if(schemeData.Delay >= 0 + 50)
			{
				schemeData.Delay -= 50;
			}
		break;

		case GPIO_PIN_6:	// next scheme
			HAL_GPIO_WritePin(GPIOD, GPIO_PIN_12|GPIO_PIN_13|GPIO_PIN_14|GPIO_PIN_15, GPIO_PIN_RESET);
			if(schemeData.SchemeIndex < schemeData.SchemesAmount - 1)
			{
				schemeData.SchemeIndex++;
			}
		break;

		case GPIO_PIN_8:	// previous scheme
			HAL_GPIO_WritePin(GPIOD, GPIO_PIN_12|GPIO_PIN_13|GPIO_PIN_14|GPIO_PIN_15, GPIO_PIN_RESET);
			if(schemeData.SchemeIndex > 0)
			{
				schemeData.SchemeIndex--;
			}
		break;

		case GPIO_PIN_15:	// toggle blinking
			schemeData.IsTurnedOn = !schemeData.IsTurnedOn;
		break;

		default:
			__NOP();
		break;
	}
}
