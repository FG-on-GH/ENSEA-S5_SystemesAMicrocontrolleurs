/*
 * sensor.c
 *
 *  Created on: Oct 22, 2025
 *      Author: FG
 */

#include "sensor.h"
#include <stdlib.h>
#include <stdio.h>
#include <stm32l4xx_hal.h>


void init_system(SENSOR_ARRAY* system){
	for(int i=0; i<SENSOR_NUMBER; i++){
		(system->sensors[i]).id = i;
		(system->sensors[i]).threshold = ((float)(rand() % 100)) / 10.0;
		(system->sensors[i]).value = 0;
		(system->sensors[i]).state = INACTIVE;
	}
}

void display_system(SENSOR_ARRAY* system){
	printf("\r\n");
	printf("- - - Détail des capteurs - - -\r\n");
	printf("\r\n");
	for(int i=0; i<SENSOR_NUMBER; i++){
		printf("- Capteur numéro %d\r\n", (system->sensors[i]).id);
		printf( ((system->sensors[i]).state == ACTIVE) ? "Actif\r\n" : "Inactif\r\n");
		printf("valeur : %.1f, seuil : %.1f\r\n",(system->sensors[i]).value, (system->sensors[i]).threshold);
		printf("\r\n");
	}
}

void read_sensors(SENSOR_ARRAY * system){
	for(int i=0; i<SENSOR_NUMBER; i++){
		(system->sensors[i]).value = ((float)(rand() % 100)) / 10.0;
	}
}

void check_threshold(SENSOR* sensor){
	for(int i=0; i<SENSOR_NUMBER; i++){
		if(sensor[i].value>=sensor[i].threshold){
			sensor[i].state=ACTIVE;
		}
		else{
			sensor[i].state=INACTIVE;
		}
	}
}



SENSOR_ARRAY systest;

void setup(){
	printf("Press blue button to init\r\n");
	while(HAL_GPIO_ReadPin(GPIOC, GPIO_PIN_13)!=GPIO_PIN_RESET){
	}
	while(HAL_GPIO_ReadPin(GPIOC, GPIO_PIN_13)==GPIO_PIN_RESET){
	}
	srand(HAL_GetTick());
	init_system(&systest);
	display_system(&systest);
}

void loop(){
	printf("Press blue button to read values\r\n");
	while(HAL_GPIO_ReadPin(GPIOC, GPIO_PIN_13)!=GPIO_PIN_RESET){
	}
	while(HAL_GPIO_ReadPin(GPIOC, GPIO_PIN_13)==GPIO_PIN_RESET){
	}
	read_sensors(&systest);
	check_threshold(systest.sensors);
	display_system(&systest);
}
