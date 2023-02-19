/*
 * scheme.h
 *
 *  Created on: Feb 19, 2023
 *      Author: Nikita Kliatskyi
 */

#ifndef INC_SCHEME_H_
#define INC_SCHEME_H_

#include "main.h"

typedef struct {
	uint16_t Size;
	uint16_t *Order;
} Scheme;

typedef struct {
	uint16_t SchemesAmount;
	Scheme *Schemes;
	uint32_t Delay;
	uint8_t IsTurnedOn;
	uint16_t SchemeIndex;
	uint16_t LedIndex;
} SchemeData;

extern SchemeData schemeData;

void InitSchemeData(void);

void DestroySchemeData(void);

#endif /* INC_SCHEME_H_ */
