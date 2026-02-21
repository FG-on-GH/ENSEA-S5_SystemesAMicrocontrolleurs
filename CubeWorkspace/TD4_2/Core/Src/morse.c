/*
 * morse.c
 *
 *  Created on: Sep 28, 2025
 *      Author: FG
 */

#include "morse.h"
#include <stdio.h>
#include <string.h>

const MORSE_LETTER alphabet[ALPHABET_SIZE] =
	{	{'A',".-"},{'B',"-..."},{'C',"-.-."},
		{'D',"-.."},{'E',"."},{'F',"..-."},
		{'G',"--."},{'H',"...."},{'I',".."},
		{'J',".---"},{'K',"-.-"},{'L',".-.."},
		{'M',"--"},{'N',"-."},{'O',"---"},
		{'P',".--."},{'Q',"--.-"},{'R',".-."},
		{'S',"..."},{'T',"-"},{'U',"..-"},
		{'V',"...-"},{'W',".--"},{'X',"-..-"},
		{'Y',"-.--"},{'Z',"--.."},
		{'1',".----"},{'2',"..---"},{'3',"...--"},
		{'4',"....-"},{'5',"....."},{'6',"-...."},
		{'7',"--..."},{'8',"---.."},{'9',"----."},
		{'0',"-----"}
};


char lookupInBaseFromCode(char* code){
	for(int i=0; i<ALPHABET_SIZE-1; i++){
		if(strcmp(alphabet[i].code, code)==0){
			return alphabet[i].letter;
		}
	}
	return '0';
}

char* lookupInBaseFromLetter(char letter){
	for(int i=0; i<ALPHABET_SIZE-1; i++){
		if(alphabet[i].letter == letter){
			return alphabet[i].code;
		}
	}
	return "-----";
}

void setup(void){
}

void loop(){
}

