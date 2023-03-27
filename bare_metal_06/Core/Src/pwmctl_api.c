/*
 * pwmctl_api.c
 *
 *  Created on: Mar 25, 2023
 *      Author: Nikita Kliatskyi
 */

#include "pwmctl_api.h"
#include "main.h"

#define PWMCTL_DEVICE_ID (0x40<<1)

static uint8_t tx_buff[2];
static I2C_HandleTypeDef *hi2c;

HAL_StatusTypeDef PWMCTL_Init(I2C_HandleTypeDef *init_hi2c)
{
	HAL_Delay(10);
	hi2c = init_hi2c;
	HAL_GPIO_WritePin(GPIOB, GPIO_PIN_7, GPIO_PIN_RESET);
	return PWMCTL_Set(PWMCTL_REG_MODE1, PWMCTL_FLAG_MODE1_DEFAULT &~ PWMCTL_FLAG_MODE1_SLEEP);
}

HAL_StatusTypeDef PWMCTL_Set(uint8_t reg, uint8_t value)
{
	tx_buff[0] = reg;
	tx_buff[1] = value;
	return HAL_I2C_Master_Transmit(hi2c, PWMCTL_DEVICE_ID, tx_buff, 2, 10000);
}
