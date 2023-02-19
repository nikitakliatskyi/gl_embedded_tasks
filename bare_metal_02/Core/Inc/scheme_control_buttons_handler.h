/*
 * scheme_control_buttons_handler.h
 *
 *  Created on: Feb 19, 2023
 *      Author: Nikita Kliatskyi
 */

#ifndef INC_SCHEME_CONTROL_BUTTONS_HANDLER_H_
#define INC_SCHEME_CONTROL_BUTTONS_HANDLER_H_

#define SCHEME_STEP 50
#define DELAY_STEP 50
#define DELAY_MAX 1000
#define DELAY_MIN 0

void HAL_GPIO_EXTI_Callback(uint16_t GPIO_Pin);

#endif /* INC_SCHEME_CONTROL_BUTTONS_HANDLER_H_ */
