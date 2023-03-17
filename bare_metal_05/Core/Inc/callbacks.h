/*
 * callbacks.h
 *
 *  Created on: Mar 17, 2023
 *      Author: Nikita Kliatskyi
 */

#ifndef INC_CALLBACKS_H_
#define INC_CALLBACKS_H_

void HAL_GPIO_EXTI_Callback(uint16_t GPIO_Pin);

void HAL_ADC_ConvCpltCallback(ADC_HandleTypeDef* hadc);

void HAL_UART_RxCpltCallback(UART_HandleTypeDef *huart);

#endif /* INC_CALLBACKS_H_ */
