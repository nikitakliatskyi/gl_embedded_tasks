/*
 * pwmctl_client_functions.h
 *
 *  Created on: Mar 26, 2023
 *      Author: Nikita Kliatskyi
 */

#ifndef INC_PWMCTL_CLIENT_FUNCTIONS_H_
#define INC_PWMCTL_CLIENT_FUNCTIONS_H_

#include "pwmctl_api.h"
#include "main.h"

typedef enum {
	DISABLED = 0,
	ENABLED = !DISABLED
} PWMCTL_STATUS;

HAL_StatusTypeDef PWMCTL_CLIENT_Set_All_Leds_Status(PWMCTL_STATUS status);
HAL_StatusTypeDef PWMCTL_CLIENT_Set_Duty_Cycle(uint8_t duty_cycle_percentage);
HAL_StatusTypeDef PWMCTL_CLIENT_Set_Frequency(uint16_t update_rate);
HAL_StatusTypeDef PWMCTL_CLIENT_Set_Sleep_Mode_Status(PWMCTL_STATUS status);

void PWMCTL_CLIENT_Get_Data(PWMCTL_STATUS *leds_status, uint16_t *pwm_frequency, uint8_t *duty_cycle, PWMCTL_STATUS *sleep_status);

#endif /* INC_PWMCTL_CLIENT_FUNCTIONS_H_ */
