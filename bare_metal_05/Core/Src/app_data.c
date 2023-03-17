/*
 * app_data.c
 *
 *  Created on: Mar 12, 2023
 *      Author: Nikita Kliatskyi
 */

#include "main.h"
#include "string.h"
#include "stdio.h"
#include "app_data.h"

LedInfo greenLed = {
		.Pin = GPIO_PIN_12,
		.State = GPIO_PIN_RESET,
		.Color = "Green"
};

LedInfo orangeLed = {
		.Pin = GPIO_PIN_13,
		.State = GPIO_PIN_RESET,
		.Color = "Orange"
};

LedInfo redLed = {
		.Pin = GPIO_PIN_14,
		.State = GPIO_PIN_RESET,
		.Color = "Red"
};

LedInfo blueLed = {
		.Pin = GPIO_PIN_15,
		.State = GPIO_PIN_RESET,
		.Color = "Blue"
};

LedControlInfo greenLedControl = {
		.Led = &greenLed,
		.ToggleButtonPin = GPIO_PIN_8,
		.ToggleChar = '1'
};

LedControlInfo orangeLedControl = {
		.Led = &orangeLed,
		.ToggleButtonPin = GPIO_PIN_9,
		.ToggleChar = '2'
};

LedControlInfo redLedControl = {
		.Led = &redLed,
		.ToggleButtonPin = GPIO_PIN_6,
		.ToggleChar = '3'
};

LedControlInfo blueLedControl = {
		.Led = &blueLed,
		.ToggleButtonPin = GPIO_PIN_11,
		.ToggleChar = '4'
};

LedControlInfo* ledsControls[] = { &greenLedControl, &orangeLedControl, &redLedControl, &blueLedControl };

volatile uint32_t adcValue;

void ToggleLed(LedInfo* led) {
	HAL_GPIO_TogglePin(GPIOD, led->Pin);
	led->State = HAL_GPIO_ReadPin(GPIOD, led->Pin);
}

void SendLedInfo(LedInfo led, UART_HandleTypeDef *huart) {
	char message[20];
	sprintf(message, "%s led is %s\r\n", led.Color, (led.State ? "on" : "off"));
	HAL_UART_Transmit(huart, (uint8_t *)message, strlen(message), 10);
}

float GetTemperature(uint32_t adcValue) {
    float vout = VREF * adcValue / 4096.0f;
    float temp = (VT0 - vout) / VC;
    return temp;
}

void SendTemperature(float temp, UART_HandleTypeDef *huart) {
	char message[100];
	sprintf(message, "Current temperature is %+.2f\r\n", temp);
	HAL_UART_Transmit(huart, (uint8_t *)message, strlen(message), 10);
}
