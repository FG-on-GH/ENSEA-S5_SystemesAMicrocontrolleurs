/*
 * fill.c
 *
 *  Created on: Sep 28, 2025
 *      Author: FG
 */

#include <stm32l4xx_hal.h>
#include <stdio.h>
#include "fill.h"

void fillArray(int* array, int size){
	for(int i=0; i<size; i++){
		printf("%d presses left\r\n", size-i);
		while(HAL_GPIO_ReadPin(GPIOC, GPIO_PIN_13)!=GPIO_PIN_RESET){
		}
		int start_time = HAL_GetTick();
		while(HAL_GPIO_ReadPin(GPIOC, GPIO_PIN_13)==GPIO_PIN_RESET){
		}
		array[i]=HAL_GetTick()-start_time;
	}
	printf("All done\r\n");
}

void displayArray(int* array, int size){
	int i;
	printf("tab = { %d ", array[0]);
	for (i = 1; i < size; i++){
		printf(", %d ", array[i]);
	}
	printf("}\r\n");
}

int getMeanValue(int* array, int size){
	int sum=0;
	for(int i=0; i<size; i++){
		sum+=array[i];
	}
	return sum/size;
}

void setup(void){
	setvbuf(stdin, NULL, _IONBF, 0);
	// Ce setup est indispensable pour scanf.
}

void loop(){
	printf("- - - - - Init - - - - -\r\n");
	int nb_press=0;
	printf("Enter desired number of press : \r\n");
	scanf("%d", &nb_press);
	int press_tab[nb_press];
	printf("- - - - - Filling - - - - -\r\n");
	fillArray(press_tab, nb_press);
	printf("- - - - - Results - - - - -\r\n");
	displayArray(press_tab, nb_press);
	printf("Mean = %d\r\n", getMeanValue(press_tab, nb_press));
}
