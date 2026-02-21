/*
 * utils.h
 *
 *  Created on: Apr 26, 2024
 *      Author: antotauv
 */

#ifndef INC_TP1_H_
#define INC_TP1_H_

#include <stm32l4xx_hal.h>

extern UART_HandleTypeDef huart1;

int fillBuffer(char*);

int isGPGGA(char*);
int extractChecksum(char*);
int calculateChecksum(char*);
int checkFrame(char*);

int find_coma(char*, int, int);
float getLatitude(char*);

void setup();
void loop();

#define BUFFER_SIZE 128
#endif /* INC_TP1_H_ */
