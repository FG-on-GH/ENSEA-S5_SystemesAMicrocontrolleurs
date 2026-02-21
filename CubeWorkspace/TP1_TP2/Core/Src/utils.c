/*
 * utils.c
 *
 *  Created on: Sep 25, 2023
 *      Author: antotauv
 */



#include "utils.h"
#include "main.h"
#include "utils.h"
#include "ssd1315.h"
#include "fonts.h"
#include <stdio.h>





// - - - - - - Récupération des trames NMEA sur la liaison USART1 - - - - - - //

// 3. Fonction fillBuffer

int fillBuffer(char* buffer){

    char received_char='\0';
    int total=0;

    for(int index=0; index<BUFFER_SIZE; index++){
        buffer[index]=0;
    }

    HAL_UART_Abort(&huart1);

    while(received_char!='$'){
        HAL_UART_Receive(&huart1, (uint8_t*)&received_char, 1, HAL_MAX_DELAY);
    }

    while(received_char!='\n' && total<BUFFER_SIZE-1){
        *buffer=received_char;
        HAL_UART_Receive(&huart1, (uint8_t*)&received_char, 1, HAL_MAX_DELAY);
        total++;
        buffer++;
    }
    *buffer=received_char;

    return total;
}






// - - - - - - Vérification de l’intégrité des trames - - - - - - //

int isGPGGA(char* frame){
    char gpgga[6]="$GPGGA";
    for(int i=0; i<6; i++){
        if(frame[i]!=gpgga[i]){
            return -1;
        }
    }
    //plutôt que de taper à la main une boucle for,
    //on pourrait utiliser la fonction strncomp du module string.h
    return 1;
}

int extractChecksum(char* buffer){
while(*buffer!='*'){
        buffer++;
    }
    return (buffer[1]&0x0f)*16 + (buffer[2]&0x0f);
}

int calculateChecksum(char* buffer){
    int checksum=0;
    buffer++;
    while(*buffer!='*'){
        checksum=checksum^(*buffer);
        buffer++;
    }
    return checksum;
}

int checkFrame(char* buffer){
	if(isGPGGA(buffer)==1 && calculateChecksum(buffer)==extractChecksum(buffer)){
		return 1;
	}
	else{
		return 0;
	}
}





// - - - - - - Récupération de l’information au format flottant - - - - - - //

int find_coma(char* frame, int size, int num){
	int i=0;
	while(i<size && num>0){
		i++;
		if(frame[i]==','){
			num--;
		}
	}
	return i;
}

float getLatitude(char* frame){

	int second_coma = find_coma(frame, BUFFER_SIZE, 2);

	char* latitude = frame + second_coma+1;
	float calcul_latitude = 0;

	calcul_latitude += 10*(latitude[0]&0xf);
	calcul_latitude += latitude[1]&0xf;
	float tmp=0;
	tmp+=10*(latitude[2]&0xf);
	tmp+=latitude[3]&0xf;
	tmp+=0.1*(latitude[5]&0xf);
	tmp+=0.01*(latitude[6]&0xf);
	tmp+=0.001*(latitude[7]&0xf);
	tmp/=60;
	calcul_latitude += tmp;

	calcul_latitude = (latitude[9]=='S') ? calcul_latitude*(-1) : calcul_latitude;

	return calcul_latitude;
}

float getLongitude(char* frame){

	int fourth_coma = find_coma(frame, BUFFER_SIZE, 4);

	char* longitude = frame + fourth_coma+1;
	float calcul_longitude = 0;

	calcul_longitude +=	100*(longitude[0]&0xf) + 10*(longitude[1]&0xf) + (longitude[2]&0xf);
	float tmp=0;
	tmp+=10*(longitude[3]&0xf);
	tmp+=longitude[4]&0xf;
	tmp+=0.1*(longitude[6]&0xf);
	tmp+=0.01*(longitude[7]&0xf);
	tmp+=0.001*(longitude[8]&0xf);
	tmp/=60;
	calcul_longitude += tmp;

	calcul_longitude = (longitude[10]=='W') ? calcul_longitude*(-1) : calcul_longitude;

	return calcul_longitude;
}





// - - - - - - Recherche de la ville la plus proche - - - - - - //

// 1. Création de la base de donnée

#include "cityDataBase.h"

#define TAILLE_BdD 4

const VILLE kiev = {50.4501,30.5234,"Kiev"};
const VILLE cergy = {49.033,2.066,"Cergy"};
const VILLE chicago = {41.88,-87.623,"Chicago"};
const VILLE barcelone = {41.385,2.173,"Barcelone"};

VILLE base_de_donnée[TAILLE_BdD]={kiev, cergy, chicago, barcelone};

// 2. Calcul de distance

#include <math.h>

float norme(VILLE* v, float latitude, float longitude){
	int norme = latitude - v->latitude;
	norme*=norme;
	float tmp = longitude - v->longitude;
	tmp*= cos((latitude - v->latitude) / 2);
	tmp*=tmp;
	norme+=tmp;
	return norme;
}

// 3. Recherche du minimum

int getMinIndex(float* array, int size){
	int index_min=0;
	for(int i=0; i<size; i++){
		if(array[i]<array[index_min]){
			index_min=i;
		}
	}
	return index_min;
}

VILLE* findNearest(VILLE tableau[], int size, float latitude, float longitude){
	float distance[size];
	for(int i=0; i<size; i++){
		distance[i] = norme(tableau+i, latitude, longitude);
	}
	return tableau+getMinIndex(distance, size);
}





// - - - - - - setup/loop - - - - - - //

void setup(){
	printf ("TP1 ENSEA by A.T. \r\n");
	ssd1315_Init();
	ssd1315_Clear(SSD1315_COLOR_BLACK);
	ssd1315_Draw_String(0,0,"GPS Lab",&Font_16x26);
	ssd1315_Refresh();
	HAL_GPIO_WritePin(GPS_ENN_GPIO_Port,GPS_ENN_Pin,1);
}

char buffer[BUFFER_SIZE];

void loop(){

	int size = fillBuffer(buffer);
	printf("Just received %d bytes : %s", size, buffer);

	if(checkFrame(buffer)==1){

		printf("Trame GPGGA\r\n");

		float latitude = getLatitude(buffer);
		float longitude = getLongitude(buffer);
		VILLE* ville_la_plus_proche = findNearest(base_de_donnée, TAILLE_BdD, latitude, longitude);
		float distance = norme(ville_la_plus_proche, latitude, longitude);

		printf("Latitude = %f, Longitude = %f\r\n", latitude, longitude);
		printf("Ville la plus proche : %s\r\n", ville_la_plus_proche->nom);
		printf("Distance : %f\r\n",distance);

		snprintf(buffer,16,"Ville : %s",ville_la_plus_proche->nom);
		ssd1315_Draw_String(0,30,buffer,&Font_7x10);
		ssd1315_Refresh();

	}

	else{
		printf("Trame invalide\r\n");
	}

	printf("\r\n");
}
