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

void setup(void){
	setvbuf(stdin, NULL, _IONBF, 0);
	// Ce setup est indispensable pour scanf.
}

void loop(){
	int press_tab[ARRAY_SIZE];
	printf("- - - - - Filling - - - - -\r\n");
	fillArray(press_tab, ARRAY_SIZE);
	printf("- - - - - Results - - - - -\r\n");
	int min;
	int max;
	float moy;
	caracArray(press_tab, &min, &max, &moy);
	displayArray(press_tab, ARRAY_SIZE);
	dispCaracArray(min, max, moy);
}
