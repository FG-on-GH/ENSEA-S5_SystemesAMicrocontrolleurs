/*
 * utils.c
 *
 *  Created on: Sep 28, 2025
 *      Author: FG
 */


#include "utils.h"
#include <stm32l4xx_hal.h>
#include <stdio.h>

void setup(){

}

void loop(){
	while(HAL_GPIO_ReadPin(GPIOC, GPIO_PIN_13)!=0){
	}
	HAL_GPIO_WritePin(GPIOA, GPIO_PIN_5, GPIO_PIN_SET);
	printf("Light ON\r\n");
	HAL_Delay(1500);
	HAL_GPIO_WritePin(GPIOA, GPIO_PIN_5, GPIO_PIN_RESET);
	printf("Light OFF\r\n");
}
