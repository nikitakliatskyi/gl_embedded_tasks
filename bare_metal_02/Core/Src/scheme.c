/*
 * scheme.c
 *
 *  Created on: Feb 19, 2023
 *      Author: Nikita Kliatskyi
 */

#include "scheme.h"
#include "stdlib.h"
#include "string.h"

SchemeData schemeData;

void InitSchemeData(void) {
	schemeData.SchemesAmount = 3;
	schemeData.Schemes = (Scheme*)calloc(schemeData.SchemesAmount, sizeof(Scheme));
	schemeData.Delay = 500;
	schemeData.IsTurnedOn = 1;
	schemeData.SchemeIndex = 2;
	schemeData.LedIndex = 0;

	schemeData.Schemes[0].Size = 4;
	schemeData.Schemes[1].Size = 4;
	schemeData.Schemes[2].Size = 2;

	for(int i = 0; i < schemeData.SchemesAmount; i++)
	{
		schemeData.Schemes[i].Order = (uint16_t*)calloc(schemeData.Schemes[i].Size, sizeof(uint16_t));
	}

	memcpy(schemeData.Schemes[0].Order, (uint16_t []){ GPIO_PIN_12, GPIO_PIN_13, GPIO_PIN_14, GPIO_PIN_15 }, 4 * sizeof(uint16_t));
	memcpy(schemeData.Schemes[1].Order, (uint16_t []){ GPIO_PIN_15, GPIO_PIN_14, GPIO_PIN_13, GPIO_PIN_12 }, 4 * sizeof(uint16_t));
	memcpy(schemeData.Schemes[2].Order, (uint16_t []){ GPIO_PIN_12|GPIO_PIN_14, GPIO_PIN_13|GPIO_PIN_15 }, 2 * sizeof(uint16_t));
}

void DestroySchemeData(void) {
	while(schemeData.SchemesAmount) {
		free(schemeData.Schemes[schemeData.SchemesAmount-1].Order);
		schemeData.SchemesAmount--;
	}
	free(schemeData.Schemes);
}
