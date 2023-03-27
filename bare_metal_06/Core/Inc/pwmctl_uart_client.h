/*
 * pwmctl_uart_client.h
 *
 *  Created on: Mar 26, 2023
 *      Author: Nikita Kliatskyi
 */

#ifndef INC_PWMCTL_UART_CLIENT_H_
#define INC_PWMCTL_UART_CLIENT_H_

#include "pwmctl_client_functions.h"

void PWMCTL_UART_Client_Init(UART_HandleTypeDef *huart);
HAL_StatusTypeDef PWMCTL_UART_Start_Session(void);

#endif /* INC_PWMCTL_UART_CLIENT_H_ */
