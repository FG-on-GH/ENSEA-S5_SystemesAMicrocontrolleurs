/*
 * insert_sort.c
 *
 *  Created on: Sep 28, 2025
 *      Author: FG
 */

#include "insert_sort.h"
#include <stm32l4xx_hal.h>
#include <stdio.h>
#include <stdlib.h>

void displayArray(int8_t* array, int size){
	int i;
	printf("tab = { %d ", array[0]);
	for (i = 1; i < size; i++){
		printf(", %d ", array[i]);
	}
	printf("}\r\n");
}

int getMinPosition(int8_t* array, int* toBeIgnored, int size){
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

void sortArray(int8_t* toSort, int8_t* sorted, int size){
	int sortedPosition[ARRAY_SIZE]={0};
	for(int i=0; i<size; i++){
		int pos_min=getMinPosition(toSort, sortedPosition, size);
		sortedPosition[pos_min]=1;
		sorted[i]=toSort[pos_min];
	}
}

void tri_à_bulles(int8_t* t, int size){
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

void tri_insertion(int8_t* t){
	for(int i=0; i<ARRAY_SIZE; i++){
		int x = t[i];
		int j=i;
		while(j>0 && t[j-1]>x){
			t[j]=t[j-1];
			j--;
		}
		t[j]=x;
	}
}

void interresting_function(){
	printf("- - - - - Random Tab - - - - -\r\n");
	int8_t random_tab_for_insert[ARRAY_SIZE];
	int8_t random_tab_for_bubble[ARRAY_SIZE];
	int8_t random_tab_for_naive[ARRAY_SIZE];
	for(int i=0; i<ARRAY_SIZE; i++){
		random_tab_for_insert[i]=(int8_t)rand();
		random_tab_for_bubble[i]=random_tab_for_insert[i];
		random_tab_for_naive[i]=random_tab_for_insert[i];
	}
	//displayArray(random_tab_for_insert, ARRAY_SIZE);

	printf("- - - - - Insert Sort - - - - -\r\n");
	long start=HAL_GetTick();
	tri_insertion(random_tab_for_insert);
	long stop=HAL_GetTick();
	//displayArray(random_tab_for_insert, ARRAY_SIZE);
	printf("Solved in %ld milliseconds\n\r", stop-start);

	printf("- - - - - Bubble Sort - - - - -\r\n");
	start=HAL_GetTick();
	tri_à_bulles(random_tab_for_bubble, ARRAY_SIZE);
	stop=HAL_GetTick();
	//displayArray(random_tab_for_bubble, ARRAY_SIZE);
	printf("Solved in %ld milliseconds\n\r", stop-start);

	printf("- - - - - Naive Sort - - - - -\r\n");
	int8_t naive_sorted[ARRAY_SIZE];
	start=HAL_GetTick();
	sortArray(random_tab_for_naive, naive_sorted, ARRAY_SIZE);
	stop=HAL_GetTick();
	//displayArray(naive_sorted, ARRAY_SIZE);
	printf("Solved in %ld milliseconds\n\r", stop-start);
	printf("\r\n");
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
