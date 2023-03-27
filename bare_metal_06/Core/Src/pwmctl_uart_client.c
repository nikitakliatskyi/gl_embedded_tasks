/*
 * pwmctl_uart_client.c
 *
 *  Created on: Mar 26, 2023
 *      Author: Nikita Kliatskyi
 */

#include "pwmctl_uart_client.h"
#include "main.h"
#include <string.h>
#include <stdio.h>
#include <stdlib.h>

#define UART_TIMEOUT 1000

#define INPUT_BUF_LEN 10
#define OUTPUT_BUF_LEN 100

static const char *_status_string[] = { "DISABLED", "ENABLED" };

static const char *_menu_msg =
		"[1] - Enable all outputs\n\r"
		"[2] - Disable all outputs\n\r"
		"[3] - Set duty cycle\n\r"
		"[4] - Set PWM frequency\n\r"
		"[5] - Enable sleep mode\n\r"
		"[6] - Disable sleep mode\n\r";

static const char *_status_msg_template =
		"Outputs: %s\n\r"
		"Duty Cycle: %u\n\r"
		"PWM Frequency: %u\n\r"
		"Sleep Mode: %s\n\r";

static UART_HandleTypeDef *_huart;

static char _input_buf[INPUT_BUF_LEN];
static char _output_buf[OUTPUT_BUF_LEN];

static uint8_t _input_is_received = 0;

void PWMCTL_UART_Client_Init(UART_HandleTypeDef *huart)
{
	_huart = huart;
}

void Set_Output(const char* output)
{
	strcpy(_output_buf, output);
}

void Generate_Status_Message()
{
	char status_msg[OUTPUT_BUF_LEN];
	PWMCTL_STATUS leds_status, sleep_status;
	uint16_t pwm_frequency;
	uint8_t duty_cycle;

	PWMCTL_CLIENT_Get_Data(&leds_status, &pwm_frequency, &duty_cycle, &sleep_status);
	sprintf(status_msg, _status_msg_template, _status_string[leds_status], duty_cycle, pwm_frequency, _status_string[sleep_status]);
	Set_Output(status_msg);
}

HAL_StatusTypeDef Print_Output()
{
	return HAL_UART_Transmit(_huart, (uint8_t*)_output_buf, strlen(_output_buf), UART_TIMEOUT);
}

HAL_StatusTypeDef Read_Input(uint16_t input_len)
{
	HAL_StatusTypeDef result;
	_input_is_received = 0;

	result = HAL_UART_Receive_DMA(_huart, (uint8_t*)_input_buf, input_len);
	if(result == HAL_OK && INPUT_BUF_LEN >= input_len)
	{
		_input_buf[input_len] = '\0';
	}

	while(!_input_is_received);

	return result;
}

HAL_StatusTypeDef PWMCTL_UART_Start_Session(void)
{
	HAL_StatusTypeDef result;
	Set_Output(_menu_msg);
	result = Print_Output();
	if(result != HAL_OK)
	{
		return result;
	}

	result = Read_Input(1);
	if(result == HAL_OK) {
	switch(_input_buf[0]) {
		case '1':
			PWMCTL_CLIENT_Set_All_Leds_Status(ENABLED);
			break;
		case '2':
			PWMCTL_CLIENT_Set_All_Leds_Status(DISABLED);
			break;
		case '3':
			Set_Output("Enter new duty cycle: ");
			Print_Output();
			Read_Input(3);
			PWMCTL_CLIENT_Set_Duty_Cycle(atoi(_input_buf));
			break;
		case '4':
			Set_Output("Enter new frequency: ");
			Print_Output();
			Read_Input(4);
			PWMCTL_CLIENT_Set_Frequency(atoi(_input_buf));
			break;
		case '5':
			PWMCTL_CLIENT_Set_Sleep_Mode_Status(ENABLED);
			break;
		case '6':
			PWMCTL_CLIENT_Set_Sleep_Mode_Status(DISABLED);
			break;
		default:
			Set_Output("Incorrect user input\n\r");
			Print_Output();
			return HAL_ERROR;
			break;
	} }

	Generate_Status_Message();
	result = Print_Output();

	return result;
}

void HAL_UART_RxCpltCallback(UART_HandleTypeDef *huart)
{
	_input_is_received = 1;
}
