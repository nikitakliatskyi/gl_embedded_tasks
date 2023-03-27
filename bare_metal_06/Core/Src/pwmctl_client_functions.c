/*
 * pwmctl_client_functions.c
 *
 *  Created on: Mar 26, 2023
 *      Author: Nikita Kliatskyi
 */

#include "pwmctl_client_functions.h"
#include <math.h>

#define OSC_CLOCK_FREQ 25e+6f

static PWMCTL_STATUS _leds_status = DISABLED;
static uint16_t _pwm_frequency = 200;
static uint8_t _duty_cycle = 0;
static PWMCTL_STATUS _sleep_status = DISABLED;

static uint8_t Round_Unsigned(float val)
{
	return (uint8_t)((val >= 0 ? val : -val) + .5f);
}

HAL_StatusTypeDef PWMCTL_CLIENT_Set_All_Leds_Status(PWMCTL_STATUS status)
{
	HAL_StatusTypeDef result;

	result = PWMCTL_Set(status == ENABLED ? PWMCTL_REG_ALL_LED_ON_H : PWMCTL_REG_ALL_LED_OFF_H, PWMCTL_FLAG_LED_FULL_ON);
	if(result != HAL_OK)
	{
		return result;
	}

	result = PWMCTL_Set(status == ENABLED ? PWMCTL_REG_ALL_LED_OFF_H : PWMCTL_REG_ALL_LED_ON_H, 0x00);
	if(result == HAL_OK)
	{
		_leds_status = status;
	}
	return result;
}

HAL_StatusTypeDef PWMCTL_CLIENT_Set_Duty_Cycle(uint8_t duty_cycle_percentage)
{
	HAL_StatusTypeDef result;
	uint16_t duty_cycle_value;

	if(duty_cycle_percentage > 100)
	{
		duty_cycle_percentage = 100;
	}

	duty_cycle_value = 4095 * (uint16_t)duty_cycle_percentage / 100;

	result = PWMCTL_Set(PWMCTL_REG_ALL_LED_ON_H, 0x00);
	if(result != HAL_OK)
	{
		return result;
	}

	result = PWMCTL_Set(PWMCTL_REG_ALL_LED_ON_L, 0x00);
	if(result != HAL_OK)
	{
		return result;
	}

	result = PWMCTL_Set(PWMCTL_REG_ALL_LED_OFF_H, duty_cycle_value >> 8);
	if(result != HAL_OK)
	{
		return result;
	}

	result = PWMCTL_Set(PWMCTL_REG_ALL_LED_OFF_L, duty_cycle_value & 0x00FF);

	if(result == HAL_OK)
	{
		_duty_cycle = duty_cycle_percentage;
	}

	return result;
}

HAL_StatusTypeDef PWMCTL_CLIENT_Set_Frequency(uint16_t update_rate)
{
	HAL_StatusTypeDef result;
	uint8_t prescale_value;

	if(update_rate < 24)
	{
		prescale_value = 0xFF;
	}
	else if(update_rate > 1526)
	{
		prescale_value = 0x03;
	}
	else
	{
		prescale_value = Round_Unsigned(OSC_CLOCK_FREQ / (4096 * update_rate)) - 1;
	}

	PWMCTL_STATUS current_sleep_status = _sleep_status;
	result = PWMCTL_CLIENT_Set_Sleep_Mode_Status(ENABLED);

	if(result != HAL_OK)
	{
		return result;
	}
	result = PWMCTL_Set(PWMCTL_REG_PRE_SCALE, prescale_value);

	if(result == HAL_OK)
	{
		_pwm_frequency = update_rate;
	}

	PWMCTL_CLIENT_Set_Sleep_Mode_Status(current_sleep_status);

	return result;
}

HAL_StatusTypeDef PWMCTL_CLIENT_Set_Sleep_Mode_Status(PWMCTL_STATUS status)
{
	HAL_StatusTypeDef result;

	result = PWMCTL_Set(PWMCTL_REG_MODE1, status == ENABLED ? PWMCTL_FLAG_MODE1_SLEEP : PWMCTL_FLAG_MODE1_DEFAULT&~PWMCTL_FLAG_MODE1_SLEEP);
	if(result == HAL_OK)
	{
		_sleep_status = status;
		_leds_status = DISABLED;
		_duty_cycle = 0;
	}
	return result;
}

void PWMCTL_CLIENT_Get_Data(PWMCTL_STATUS *leds_status, uint16_t *pwm_frequency, uint8_t *duty_cycle, PWMCTL_STATUS *sleep_status)
{
	*leds_status = _leds_status;
	*pwm_frequency = _pwm_frequency;
	*duty_cycle = _duty_cycle;
	*sleep_status = _sleep_status;
}
