/*
 * callbacks.c
 *
 *  Created on: Mar 17, 2023
 *      Author: Nikita Kliatskyi
 */

#include "main.h"
#include "app_data.h"
#include "callbacks.h"

extern UART_HandleTypeDef huart3;
extern uint8_t receivedChar;

void HAL_GPIO_EXTI_Callback(uint16_t GPIO_Pin)
{
	for(int i = 0; i < LEDS_AMOUNT; i++)
	{
		if(GPIO_Pin == ledsControls[i]->ToggleButtonPin) {
			ToggleLed(ledsControls[i]->Led);
		}
		SendLedInfo(*(ledsControls[i]->Led), &huart3);
	}
}

void HAL_ADC_ConvCpltCallback(ADC_HandleTypeDef* hadc)
{
	SendTemperature(GetTemperature(adcValue), &huart3);
}

void HAL_UART_RxCpltCallback(UART_HandleTypeDef *huart)
{
	for(int i = 0; i < LEDS_AMOUNT; i++)
	{
		if(receivedChar == ledsControls[i]->ToggleChar) {
			ToggleLed(ledsControls[i]->Led);
		}
		SendLedInfo(*(ledsControls[i]->Led), &huart3);
	}
}
