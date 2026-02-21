/*
 * stupid.c
 *
 *  Created on: Sep 28, 2025
 *      Author: FG
 */


#include <stm32l4xx_hal.h>
#include<stdio.h>
#include "stupid.h"

void stupid_function(int stupid_variable){
	stupid_variable++;
}

void not_so_stupid_function(int* stupid_pointer){
	(*stupid_pointer)++;
}

void another_function(void){
	int x = 0;
	stupid_function(x);
	printf("Valeur de x par SF : %d\r\n", x);
	not_so_stupid_function(&x);
	printf("Valeur de x par NSSF : %d\r\n", x);
}
