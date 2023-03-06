/*
 * app_data.c
 *
 *  Created on: Mar 5, 2023
 *      Author: Nikita Kliatskyi
 */

#include "app_data.h"
#include "main.h"

volatile Emergencies emergencies = { 0, 0, 0 };
const uint32_t red_led_freq_states[MAX_EMERGENCIES_AMNT] = { 1, 2.5, 5 };
volatile uint32_t adc_values[MAX_EMERGENCIES_AMNT];
const int adc_values_amount = sizeof(adc_values) / sizeof(adc_values[0]);
volatile uint32_t current_emergencies_amnt = 0;

void UpdateEmergencies(const uint32_t* adc_values, Emergencies* emergencies, uint32_t* amnt)
{
	emergencies->VoltageIsHigh = (adc_values[0] >= HIGH_VOLTAGE_ADC);
	emergencies->ExTempIsHigh = (adc_values[1] <= LOW_EX_TEMP_ADC);
	emergencies->InTempIsHigh = (adc_values[2] >= HIGH_IN_TEMP_ADC);
	*amnt = emergencies->VoltageIsHigh + emergencies->InTempIsHigh + emergencies->ExTempIsHigh;
}
