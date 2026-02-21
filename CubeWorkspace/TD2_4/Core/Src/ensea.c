/*
 * ensea.c
 *
 *  Created on: Sep 28, 2025
 *      Author: FG
 */

#include <stdio.h>
#include <stm32l4xx_hal.h>
#include "ensea.h"

int globale = 100;

void fonction(int parametre){
	int locale = 5;
	locale++;
	globale++;
	parametre++;
	printf("*** Intérieur de la fonction *** \n\r Valeur de locale : %d"
			"\t de globale : %d \t de parametre : %d\n\r",
			locale, globale, parametre);
}

void setup(void){
	int locale = 10;
	int parametre = 20;
	printf("*** Setup avant appel de fonction ***\n\r"
			"Valeur de locale : %d"
			"\t de globale : %d \t de parametre : %d \n\r",
			locale, globale, parametre);
	fonction(parametre);
	printf("*** Setup après appel de fonction ***\n\r"
			"Valeur de locale : %d"
			"\t de globale : %d \t de parametre : %d \n\r",
			locale, globale, parametre);
}

void loop(void){
	// This code will run indefinitely.
}
