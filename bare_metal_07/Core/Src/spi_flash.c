/*
 * spi_flash.c
 *
 *  Created on: Mar 28, 2023
 *      Author: Nikita Kliatskyi
 */

#include "spi_flash.h"
#include "main.h"
#include <stdarg.h>
#include <stdio.h>
#include <string.h>

extern SPI_HandleTypeDef hspi1;

static void Set_Instruction(uint8_t *tx_buf, int params_amount, ...)
{
	va_list params;
	va_start(params, params_amount);
	for(int i = 0; i < params_amount; i++)
	{
		tx_buf[i] = va_arg(params, int);
	}
	va_end(params);
}

static void Execute_Instruction(uint8_t *tx_buf, uint8_t *rx_buf, uint16_t size)
{
	HAL_GPIO_WritePin(GPIOD, GPIO_PIN_7, GPIO_PIN_RESET);
	HAL_SPI_TransmitReceive(&hspi1, tx_buf, rx_buf, size, 100);
	HAL_GPIO_WritePin(GPIOD, GPIO_PIN_7, GPIO_PIN_SET);
	HAL_Delay(1000);
}

void Read_Capsule(char output[][100])
{
	uint8_t tx_buf[100] = { 0 };
	uint8_t rx_buf[100] = { 0 };
	for(int i = 0; i < 20; i++)
	{
		uint32_t page_adr = (uint32_t)i * 4096;
		Set_Instruction(tx_buf, 4, 0x03, (uint8_t)(page_adr >> 16), (uint8_t)(page_adr >> 8), (uint8_t)page_adr);
		Execute_Instruction(tx_buf, rx_buf, 100);

		for(int j = 0; j < 100 && rx_buf[j - 1] != '\n'; j++)
		{
			output[i][j] = rx_buf[j];
		}
	}
}

void Write_Capsule(const char *text)
{
  uint32_t address = 0x000000;
  uint16_t text_len = strlen(text);
  uint8_t tx_buf[4] = { 0 };
  HAL_GPIO_WritePin(GPIOD, GPIO_PIN_7, GPIO_PIN_RESET);
  for (uint16_t i = 0; i < text_len; i++) {
	Set_Instruction(tx_buf, 4, 0x02, (uint8_t)(address >> 16), (uint8_t)(address >> 8), (uint8_t)(address));
    HAL_SPI_Transmit(&hspi1, tx_buf, sizeof(tx_buf), 1000);
    HAL_SPI_Transmit(&hspi1, (uint8_t*)&text[i], sizeof(char), 1000);
    address++;
    if (text[i] == '\n') {
      while (address % 4096 != 0) {
        HAL_SPI_Transmit(&hspi1, (uint8_t*)" ", sizeof(char), 1000);
        address++;
      }
    }
  }
  HAL_GPIO_WritePin(GPIOD, GPIO_PIN_7, GPIO_PIN_SET);
}

void Erase_Capsule()
{
  uint8_t tx_buf[4] = { 0 };
  HAL_GPIO_WritePin(GPIOD, GPIO_PIN_7, GPIO_PIN_RESET);
  for (uint32_t i = 0; i < 0x20000; i += 0x1000)
  {
	  Set_Instruction(tx_buf, 4, 0x20, (uint8_t)((i >> 16) & 0xFF), (uint8_t)((i >> 8) & 0xFF), (uint8_t)(i & 0xFF));
	  HAL_SPI_Transmit(&hspi1, tx_buf, 4, 1000);
	  while ((HAL_SPI_Transmit(&hspi1, (uint8_t*)"\xFF\xFF\xFF\xFF", 4, HAL_MAX_DELAY) == HAL_BUSY));
  }
  HAL_GPIO_WritePin(GPIOD, GPIO_PIN_7, GPIO_PIN_SET);
}
