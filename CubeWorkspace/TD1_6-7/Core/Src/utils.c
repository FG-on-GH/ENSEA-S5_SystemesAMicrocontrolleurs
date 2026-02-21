/*
 * utils.c
 *
 *  Created on: Sep 27, 2025
 *      Author: FG
 */


#include "utils.h"
#include <stm32l4xx_hal.h>
#include <stdbool.h>
#include <stdio.h>

void setup(){

}

int etat_led = GPIO_PIN_RESET;
int nb_flash = 0;

void loop(){
	while(HAL_GPIO_ReadPin(GPIOC, GPIO_PIN_13)!=GPIO_PIN_RESET){
	}
	while(HAL_GPIO_ReadPin(GPIOC, GPIO_PIN_13)==GPIO_PIN_RESET){
	}
	etat_led = 1 - etat_led;
	nb_flash++;
	HAL_GPIO_WritePin(GPIOA, GPIO_PIN_5, etat_led);
	printf("Switch pressed %d times, LED state : %d/1\r\n", nb_flash, etat_led);
	/* Version 1.6.2
	if(etat_led==GPIO_PIN_SET){
		printf("Switch pressed %d times, LED state : %d/1\r\n", nb_flash, etat);
	}
	else{
		printf("Switch pressed, LED OFF\r\n");
	}
	*/
}
