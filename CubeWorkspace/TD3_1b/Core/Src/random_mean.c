/*
 * random_mean.c
 *
 *  Created on: Sep 28, 2025
 *      Author: FG
 */


#include "random_mean.h"
#include <stm32l4xx_hal.h>
#include <stdio.h>
#include <stdlib.h>

void displayArray(int* array, int size){
	int i;
	printf("tab = { %d ", array[0]);
	for (i = 1; i < size; i++){
		printf(", %d ", array[i]);
	}
	printf("}\r\n");
}

void caracArray(int array[ARRAY_SIZE], int* pmin, int* pmax, float* pmoy){
	*pmin = array[0];
	for(int i=1; i<ARRAY_SIZE; i++){
		if(array[i]<*pmin){
			*pmin=array[i];
		}
	}
	*pmax = array[0];
	for(int i=0; i<ARRAY_SIZE; i++){
		if(array[i]>*pmax){
			*pmax=array[i];
		}
	}
	int sum = array[0];
	for(int i=0; i<ARRAY_SIZE; i++){
		sum+=array[i];
	}
	*pmoy = (float)sum/ARRAY_SIZE;
}

void dispCaracArray(int mini, int maxi, float moy){
	printf("min = %d , max = %d , moy = %.2f\r\n", mini, maxi, moy);
}

void interresting_function(){
	int random_tab[ARRAY_SIZE];
	for(int i=0; i<ARRAY_SIZE; i++){
		random_tab[i]=rand();
	}
	displayArray(random_tab, ARRAY_SIZE);
	int min;
	int max;
	float moy;
	caracArray(random_tab, &min, &max, &moy);
	dispCaracArray(min, max, moy);
}

void setup(){
	printf("Press blue button to start\r\n");
	while(HAL_GPIO_ReadPin(GPIOC, GPIO_PIN_13)!=GPIO_PIN_RESET){
	}
	while(HAL_GPIO_ReadPin(GPIOC, GPIO_PIN_13)==GPIO_PIN_RESET){
	}
	srand(HAL_GetTick());
	interresting_function();
}

void loop(){
	printf("Press again\r\n");
	while(HAL_GPIO_ReadPin(GPIOC, GPIO_PIN_13)!=GPIO_PIN_RESET){
	}
	while(HAL_GPIO_ReadPin(GPIOC, GPIO_PIN_13)==GPIO_PIN_RESET){
	}
	interresting_function();
}
