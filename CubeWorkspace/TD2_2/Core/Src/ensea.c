/*
 * ensea.c
 *
 *  Created on: Sep 28, 2025
 *      Author: FG
 */

#include <stdio.h>
#include <stm32l4xx_hal.h>
#include "ensea.h"

void setup(void){
	int ceci_est_une_variable = 100;
	printf("Variable selon différents formats : %d, %x, %c \r\n",
			ceci_est_une_variable,
			ceci_est_une_variable,
			ceci_est_une_variable);

	ceci_est_une_variable++;
	printf("Après modification : %d, %x, %c \r\n",
			ceci_est_une_variable,
			ceci_est_une_variable,
			ceci_est_une_variable);
}

void loop(void){
	// This code will run infinitely.
}
