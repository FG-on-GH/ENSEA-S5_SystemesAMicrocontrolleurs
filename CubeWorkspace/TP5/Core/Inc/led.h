/*
 * led.h
 *
 *  Created on: Apr 15, 2024
 *      Author: antotauv
 */

#ifndef LED_LED_H_
#define LED_LED_H_
#include "main.h"

typedef struct led {
	int isOn;
	GPIO_TypeDef* port;
	uint16_t pinNumber;
}LED;

void LED_Set_Value_With_Int(int value);
void LED_Set_Value_With_Array(int value[8]);
int LED_Get_Value();
void LED_Update();
void LED_Test_All();

#endif /* LED_LED_H_ */
