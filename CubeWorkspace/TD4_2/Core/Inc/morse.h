/*
 * morse.h
 *
 *  Created on: Sep 28, 2025
 *      Author: FG
 */

#ifndef INC_MORSE_H_
#define INC_MORSE_H_

typedef struct morse_lettre {
	char letter;
	char * code;
} MORSE_LETTER;

#define ALPHABET_SIZE 36

void setup();
void loop();

#endif /* INC_MORSE_H_ */
