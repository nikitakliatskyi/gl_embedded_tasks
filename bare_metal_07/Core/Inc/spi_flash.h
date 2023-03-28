/*
 * spi_flash.h
 *
 *  Created on: Mar 28, 2023
 *      Author: Nikita Kliatskyi
 */

#include "main.h"

#ifndef INC_SPI_FLASH_H_
#define INC_SPI_FLASH_H_

void Read_Capsule(char output[][100]);
void Erase_Capsule();
void Write_Capsule(const char *text);

#endif /* INC_SPI_FLASH_H_ */
