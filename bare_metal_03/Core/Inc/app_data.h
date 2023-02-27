/*
 * app_data.c
 *
 *  Created on: Feb 27, 2023
 *      Author: Nikita Kliatskyi
 */

#include "main.h"

#ifndef INC_APP_DATA_H_
#define INC_APP_DATA_H_

typedef struct {
	uint32_t Prescaler;
	uint32_t MaxPrescaler;
	unsigned int Channel;
	uint32_t DutyCycle;
	uint32_t MaxDutyCycle;
	uint8_t NeedsUpdate;
} AppData;

extern AppData appData;

void InitAppData(uint32_t prescaler, unsigned int channel, uint32_t duty_cycle);

#endif /* INC_APP_DATA_H_ */
