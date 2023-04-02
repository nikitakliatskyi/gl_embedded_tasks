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

#define READ_INSTR 0x03
#define CHIP_ERASE_INSTR 0x60
#define WREN_INSTR 0x06
#define WRDI_INSTR 0x04
#define EWSR_INSTR 0x50
#define WRSR_INSTR 0x01
#define RDSR_INSTR 0x05
#define AAI_WORD_PROGRAM_INSTR 0xAD

#define LSBYTE(num, offset) ((uint8_t)((num) >> ((offset) * (8))))

typedef enum {
	DISABLED = 0,
	ENABLED = !DISABLED
} STATUS;

extern SPI_HandleTypeDef hspi1;

static void Set_SPI_Status(STATUS status)
{
	HAL_GPIO_WritePin(GPIOD, GPIO_PIN_7, status ? GPIO_PIN_RESET : GPIO_PIN_SET);
	HAL_Delay(100);
}

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

static void Transmit(uint8_t *tx_buf, uint16_t size)
{
	HAL_SPI_Transmit(&hspi1, tx_buf, size, 100);
}

static void Receive(uint8_t *rx_buf, uint16_t size)
{
	HAL_SPI_Receive(&hspi1, rx_buf, size, 100);
}

static void Transmit_Receive(uint8_t *tx_buf, uint8_t *rx_buf, uint16_t size)
{
	HAL_SPI_TransmitReceive(&hspi1, tx_buf, rx_buf, size, 100);
}

static void Set_Write_Register(STATUS status)
{
	uint8_t tx_buf[2] = { 0 };
	Set_Instruction(tx_buf, 1, EWSR_INSTR);
	Set_SPI_Status(ENABLED);
	Transmit(tx_buf, 1);
	Set_SPI_Status(DISABLED);

	Set_Instruction(tx_buf, 2, WRSR_INSTR, status ? 0x00 : 0x1C);
	Set_SPI_Status(ENABLED);
	Transmit(tx_buf, 2);
	Set_SPI_Status(DISABLED);
}

static void Set_Write_Status(STATUS status)
{
	uint8_t tx_buf = 0;

	Set_Instruction(&tx_buf, 1, status ? WREN_INSTR : WRDI_INSTR);
	Set_SPI_Status(ENABLED);
	Transmit(&tx_buf, 1);
	Set_SPI_Status(DISABLED);
}

void Read_Sector(char output[SYMS_PER_SECTOR], uint32_t adr)
{
	uint8_t tx_buf[SYMS_PER_SECTOR] = { 0 };
	uint8_t rx_buf[SYMS_PER_SECTOR] = { 0 };

	Set_Instruction(tx_buf, 4, READ_INSTR, LSBYTE(adr, 2), LSBYTE(adr, 1), LSBYTE(adr, 0));
	Set_SPI_Status(ENABLED);
	Transmit_Receive(tx_buf, rx_buf, SYMS_PER_SECTOR);
	Set_SPI_Status(DISABLED);

	for(int j = 0; j < SYMS_PER_SECTOR && rx_buf[j + 4 - 1] != '\n'; j++)
	{
		output[j] = rx_buf[j + 4];
	}
}

void Write_Sector(const char *text, uint32_t adr)
{
  uint16_t text_len = strlen(text);
  uint8_t tx_buf[6] = { 0 };
  uint8_t rx_buf = 0;

  Set_Write_Register(ENABLED);
  Set_Write_Status(ENABLED);

  Set_Instruction(tx_buf, 6, AAI_WORD_PROGRAM_INSTR, LSBYTE(adr, 2), LSBYTE(adr, 1), LSBYTE(adr, 0), text[0], text[1]);
  Set_SPI_Status(ENABLED);
  Transmit(tx_buf, 6);
  Set_SPI_Status(DISABLED);

  for(int i = 2; i < text_len; i++)
  {
	  if(text[i] != '\n')
	  {
		  Set_Instruction(tx_buf, 3, AAI_WORD_PROGRAM_INSTR, text[i], text[i + 1]);
		  i++;
	  }
	  else
	  {
		  Set_Instruction(tx_buf, 3, AAI_WORD_PROGRAM_INSTR, text[i], '\0');
	  }

	  Set_SPI_Status(ENABLED);
	  Transmit(tx_buf, 3);
	  Set_SPI_Status(DISABLED);
  }

  Set_Write_Status(DISABLED);
  Set_Write_Register(DISABLED);

  Set_Instruction(tx_buf, 1, RDSR_INSTR);
  Set_SPI_Status(ENABLED);
  Transmit(tx_buf, 1);
  do
  {
	  Receive(&rx_buf, 1);
  }
  while (rx_buf & 0x01);
  Set_SPI_Status(DISABLED);
}

void Erase_Memory(void)
{
  uint8_t tx_buf = { 0 };

  Set_Instruction(&tx_buf, 1, CHIP_ERASE_INSTR);

  Set_Write_Register(ENABLED);
  Set_Write_Status(ENABLED);
  Set_SPI_Status(ENABLED);

  Transmit(&tx_buf, 1);

  Set_SPI_Status(DISABLED);
  Set_Write_Status(DISABLED);
  Set_Write_Register(DISABLED);
}
