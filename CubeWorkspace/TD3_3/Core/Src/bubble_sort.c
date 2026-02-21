/*
 * bubble_sort.c
 *
 *  Created on: Sep 28, 2025
 *      Author: FG
 */


#include "bubble_sort.h"
#include <stdio.h>
#include <stm32l4xx_hal.h>

#define ARRAY_SIZE 15

void tri_à_bulles(int* t, int size){
	for(int i=0; i<size; i++){
		for(int j=0; j<size; j++){
			if(t[j+1]<t[j]){
				int tmp=t[j];
				t[j]=t[j+1];
				t[j+1]=tmp;
			}
		}
	}
}

void displayArray(int* array, int size){
	int i;
	printf("tab = { %d ", array[0]);
	for (i = 1; i < size; i++){
		printf(", %d ", array[i]);
	}
	printf("}\r\n");
}


void setup(){

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
	long start=HAL_GetTick();
	tri_à_bulles(arrayTest, ARRAY_SIZE);
	long stop=HAL_GetTick();
	displayArray(arrayTest, ARRAY_SIZE);
	printf("Solved in %ld milliseconds\n\r", stop-start);
}
