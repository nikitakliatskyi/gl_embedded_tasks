/*
 * app_data.h
 *
 *  Created on: Mar 5, 2023
 *      Author: Nikita Kliatskyi
 */

#include "main.h"

#ifndef INC_APP_DATA_H_
#define INC_APP_DATA_H_

#define MAX_EMERGENCIES_AMNT 3

#define STANDART_LED_DURATION 100
#define URGENT_LED_DURATION 800

#define HIGH_VOLTAGE_ADC 3000
#define LOW_EX_TEMP_ADC 1700
#define HIGH_IN_TEMP_ADC 1100

typedef struct {
	volatile uint32_t VoltageIsHigh : 1;
	volatile uint32_t InTempIsHigh : 1;
	volatile uint32_t ExTempIsHigh : 1;
} Emergencies;

extern volatile Emergencies emergencies;
extern const uint32_t red_led_freq_states[MAX_EMERGENCIES_AMNT];
extern volatile uint32_t adc_values[MAX_EMERGENCIES_AMNT];
extern const int adc_values_amount;
extern volatile uint32_t current_emergencies_amnt;

void UpdateEmergencies(const uint32_t* adc_values, Emergencies* emergencies, uint32_t* amnt);

#endif /* INC_APP_DATA_H_ */
