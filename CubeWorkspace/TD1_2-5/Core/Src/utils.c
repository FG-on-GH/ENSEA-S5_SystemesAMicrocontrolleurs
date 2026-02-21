/*
 * utils.c
 *
 *  Created on: Sep 27, 2025
 *      Author: FG
 */


#include <stm32l4xx_hal.h>
#include "utils.h"
#include <stdio.h>

#define GPIO_PORT_LED GPIOA
#define GPIO_PIN_LED GPIO_PIN_5

void setup(){
	// Insert the setup code here, it will run once.
	int annee = 2028;
	float note = 20.8;
	printf("ENSEA promotion %d, ", annee);
	printf("votre note %f\r\n", note);
}

int nb_flash_led = 0;

void loop(){
	// This code will run indefinitely.
	HAL_GPIO_WritePin(GPIO_PORT_LED, GPIO_PIN_LED, GPIO_PIN_RESET);
	HAL_Delay(250);
	HAL_GPIO_WritePin(GPIO_PORT_LED, GPIO_PIN_LED, GPIO_PIN_SET);
	HAL_Delay(250);
	nb_flash_led++;
	printf("%d flash\r\n", nb_flash_led);
}
