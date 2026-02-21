/*
 * fill.h
 *
 *  Created on: Sep 28, 2025
 *      Author: FG
 */

#ifndef INC_FILL_H_
#define INC_FILL_H_

#define ARRAY_SIZE 10

void setup();
void loop();
void fillArray(int*, int);
void displayArray(int*, int);
int getMeanValue(int*, int);
void caracArray(int[ARRAY_SIZE], int*, int*, float*);
void dispCaracArray(int, int, float);

#endif /* INC_FILL_H_ */
