/*
 * app_data.c
 *
 *  Created on: Feb 27, 2023
 *      Author: Nikita Kliatskyi
 */

#include "main.h"
#include "app_data.h"

AppData appData;

void InitAppData(uint32_t prescaler, unsigned int channel, uint32_t duty_cycle)
{
	appData.Prescaler = prescaler / 2;
	appData.MaxPrescaler = prescaler;
	appData.Channel = channel;
	appData.DutyCycle = duty_cycle / 2;
	appData.MaxDutyCycle = duty_cycle;
	appData.NeedsUpdate = 1;
}
