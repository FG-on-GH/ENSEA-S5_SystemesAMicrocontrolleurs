/*
 * min_sort.c
 *
 *  Created on: Sep 28, 2025
 *      Author: FG
 */

#include <stm32l4xx_hal.h>
#include <stdio.h>
#include "min_sort.h"

#define ARRAY_SIZE 15

int getMinPosition(int* array, int* toBeIgnored, int size){
	int pos_min=0;
	while(toBeIgnored[pos_min]==1){
		pos_min++;
	}
	for(int i=0; i<size; i++){
		if(toBeIgnored[i]!=1){
			if(array[i]<array[pos_min]){
				pos_min=i;
			}
		}
	}
	return pos_min;
}

void displayArray(int* array, int size){
	int i;
	printf("tab = { %d ", array[0]);
	for (i = 1; i < size; i++){
		printf(", %d ", array[i]);
	}
	printf("}\r\n");
}

void sortArray(int* toSort, int* sorted, int size){
	int sortedPosition[ARRAY_SIZE]={0};
	for(int i=0; i<size; i++){
		int pos_min=getMinPosition(toSort, sortedPosition, size);
		sortedPosition[pos_min]=1;
		sorted[i]=toSort[pos_min];
	}
}

int arrayTest[ARRAY_SIZE]={0, 1, -3, 10, -1, 0, 0, 0, 0, 12, 1024, 10, 45, 6, 4};

void loop(void){

	printf("Waiting\r\n");
	while(HAL_GPIO_ReadPin(GPIOC, GPIO_PIN_13)!=GPIO_PIN_RESET){
	}
	while(HAL_GPIO_ReadPin(GPIOC, GPIO_PIN_13)==GPIO_PIN_RESET){
	}
	displayArray(arrayTest, ARRAY_SIZE);
	/*
	int ignored[ARRAY_SIZE]={0};
	int index;
	index=getMinPosition(arrayTest, ignored, ARRAY_SIZE);
	printf("First min at : %d \n\r",index);
	ignored[index]=1;
	index=getMinPosition(arrayTest, ignored, ARRAY_SIZE);
	printf("Second min at : %d \n\r",index);
	*/
	int sorted[ARRAY_SIZE]={0};
	long start=HAL_GetTick();
	sortArray(arrayTest, sorted, ARRAY_SIZE);
	long stop=HAL_GetTick();
	displayArray(sorted, ARRAY_SIZE);
	printf("Solved in %ld milliseconds\n\r", stop-start);
}
