/*
 * app_data.h
 *
 *  Created on: Mar 14, 2023
 *      Author: Nikita Kliatskyi
 */

#ifndef INC_APP_DATA_H_
#define INC_APP_DATA_H_

#define LEDS_AMOUNT 4
#define VREF 3.3f
#define VT0 2.73f
#define VC .05f


#define ADC_VALUES_AMOUNT 1

typedef struct {
	uint16_t Pin;
	volatile GPIO_PinState State;
	char* Color;
} LedInfo;

typedef struct {
	LedInfo* Led;
	uint16_t ToggleButtonPin;
	uint8_t ToggleChar;
} LedControlInfo;

extern LedInfo greenLed;
extern LedInfo orangeLed;
extern LedInfo redLed;
extern LedInfo blueLed;

extern LedControlInfo greenLedControl;
extern LedControlInfo orangeLedControl;
extern LedControlInfo redLedControl;
extern LedControlInfo blueLedControl;

extern LedControlInfo* ledsControls[];

extern volatile uint32_t adcValue;

void InitApp(ADC_HandleTypeDef* hadc, uint32_t* pData, uint32_t Length);

void ToggleLed(LedInfo* led);

void SendLedInfo(LedInfo led, UART_HandleTypeDef *huart);

float GetTemperature(uint32_t adcValue);

void SendTemperature(float temp, UART_HandleTypeDef *huart);

#endif /* INC_APP_DATA_H_ */
