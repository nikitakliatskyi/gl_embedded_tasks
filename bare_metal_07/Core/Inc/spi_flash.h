/*
 * spi_flash.h
 *
 *  Created on: Mar 28, 2023
 *      Author: Nikita Kliatskyi
 */

#include "main.h"

#ifndef INC_SPI_FLASH_H_
#define INC_SPI_FLASH_H_

#define SECTORS_AMOUNT 20
#define SECTOR_SIZE 4096
#define SYMS_PER_SECTOR 100

void Read_Sector(char output[SYMS_PER_SECTOR], uint32_t adr);
void Write_Sector(const char *text, uint32_t adr);
void Erase_Memory(void);

#endif /* INC_SPI_FLASH_H_ */
