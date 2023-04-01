/*
 * pwmctl_api.h
 *
 *  Created on: Mar 25, 2023
 *      Author: Nikita Kliatskyi
 */

#include "main.h"

#ifndef INC_PWMCTL_API_H_
#define INC_PWMCTL_API_H_

#define PWMCTL_REG_MODE1 0x00

#define PWMCTL_FLAG_MODE1_DEFAULT 0x11
#define PWMCTL_FLAG_MODE1_RESTART 0x80
#define PWMCTL_FLAG_MODE1_EXTCLK 0x40
#define PWMCTL_FLAG_MODE1_AI 0x20
#define PWMCTL_FLAG_MODE1_SLEEP 0x10
#define PWMCTL_FLAG_MODE1_SUB1 0x08
#define PWMCTL_FLAG_MODE1_SUB2 0x04
#define PWMCTL_FLAG_MODE1_SUB3 0x02
#define PWMCTL_FLAG_MODE1_ALLCALL 0x01

#define PWMCTL_REG_MODE2 0x01

#define PWMCTL_FLAG_MODE2_INVRT 0x10
#define PWMCTL_FLAG_MODE2_OCH 0x08
#define PWMCTL_FLAG_MODE2_OUTDRV 0x04
#define PWMCTL_FLAG_MODE2_OUTNE 0x03

#define PWMCTL_REG_SUBADR1 0x02
#define PWMCTL_REG_SUBADR2 0x03
#define PWMCTL_REG_SUBADR3 0x04

#define PWMCTL_REG_ALLCALLADR 0x05

#define PWMCTL_LED0_ON_L 0x06
#define PWMCTL_LED0_ON_H 0x07
#define PWMCTL_LED0_OFF_L 0x08
#define PWMCTL_LED0_OFF_H 0x09
#define PWMCTL_LED1_ON_L 0x0A
#define PWMCTL_LED1_ON_H 0x0B
#define PWMCTL_LED1_OFF_L 0x0C
#define PWMCTL_LED1_OFF_H 0x0D
#define PWMCTL_LED2_ON_L 0x0E
#define PWMCTL_LED2_ON_H 0x0F
#define PWMCTL_LED2_OFF_L 0x10
#define PWMCTL_LED2_OFF_H 0x11
#define PWMCTL_LED3_ON_L 0x12
#define PWMCTL_LED3_ON_H 0x13
#define PWMCTL_LED3_OFF_L 0x14
#define PWMCTL_LED3_OFF_H 0x15
#define PWMCTL_LED4_ON_L 0x16
#define PWMCTL_LED4_ON_H 0x17
#define PWMCTL_LED4_OFF_L 0x18
#define PWMCTL_LED4_OFF_H 0x19
#define PWMCTL_LED5_ON_L 0x1A
#define PWMCTL_LED5_ON_H 0x1B
#define PWMCTL_LED5_OFF_L 0x1C
#define PWMCTL_LED5_OFF_H 0x1D
#define PWMCTL_LED6_ON_L 0x1E
#define PWMCTL_LED6_ON_H 0x1F
#define PWMCTL_LED6_OFF_L 0x20
#define PWMCTL_LED6_OFF_H 0x21
#define PWMCTL_LED7_ON_L 0x22
#define PWMCTL_LED7_ON_H 0x23
#define PWMCTL_LED7_OFF_L 0x24
#define PWMCTL_LED7_OFF_H 0x25
#define PWMCTL_LED8_ON_L 0x26
#define PWMCTL_LED8_ON_H 0x27
#define PWMCTL_LED8_OFF_L 0x28
#define PWMCTL_LED8_OFF_H 0x29
#define PWMCTL_LED9_ON_L 0x2A
#define PWMCTL_LED9_ON_H 0x2B
#define PWMCTL_LED9_OFF_L 0x2C
#define PWMCTL_LED9_OFF_H 0x2D
#define PWMCTL_LED10_ON_L 0x2E
#define PWMCTL_LED10_ON_H 0x2F
#define PWMCTL_LED10_OFF_L 0x30
#define PWMCTL_LED10_OFF_H 0x31
#define PWMCTL_LED11_ON_L 0x32
#define PWMCTL_LED11_ON_H 0x33
#define PWMCTL_LED11_OFF_L 0x34
#define PWMCTL_LED11_OFF_H 0x35
#define PWMCTL_LED12_ON_L 0x36
#define PWMCTL_LED12_ON_H 0x37
#define PWMCTL_LED12_OFF_L 0x38
#define PWMCTL_LED12_OFF_H 0x39
#define PWMCTL_LED13_ON_L 0x3A
#define PWMCTL_LED13_ON_H 0x3B
#define PWMCTL_LED13_OFF_L 0x3C
#define PWMCTL_LED13_OFF_H 0x3D
#define PWMCTL_LED14_ON_L 0x3E
#define PWMCTL_LED14_ON_H 0x3F
#define PWMCTL_LED14_OFF_L 0x40
#define PWMCTL_LED14_OFF_H 0x41
#define PWMCTL_LED15_ON_L 0x42
#define PWMCTL_LED15_ON_H 0x43
#define PWMCTL_LED15_OFF_L 0x44
#define PWMCTL_LED15_OFF_H 0x45
#define PWMCTL_REG_ALL_LED_ON_L 0xFA
#define PWMCTL_REG_ALL_LED_ON_H 0xFB
#define PWMCTL_REG_ALL_LED_OFF_L 0xFC
#define PWMCTL_REG_ALL_LED_OFF_H 0xFD

#define PWMCTL_FLAG_LED_FULL_ON 0x10

#define PWMCTL_REG_PRE_SCALE 0xFE
#define PWMCTL_REG_TEST_MODE 0xFF

HAL_StatusTypeDef PWMCTL_Init(I2C_HandleTypeDef *init_hi2c);
HAL_StatusTypeDef PWMCTL_Set(uint8_t reg, uint8_t value);

#endif /* INC_PWMCTL_API_H_ */
