/*
 * task.c
 *
 *  Created on: Nov 4, 2025
 *      Author: FG
 */


#include "task.h"


static int globalDelayInMs=200;

typedef struct motif_type{
	int size;
	int * motif;
	char * name;
}MOTIF_TYPE;

int upDownMotif[]={0,128,192,224,240,248,252,254,255,254,252,248,240,224,192,128};
int chenillardUpMotif[]={1,2,4,8,16,32,64,128};
int chenillardDownMotif[]={128,64,32,16,8,4,2,1};

const MOTIF_TYPE upDown={16,upDownMotif,"Up Down"};
const MOTIF_TYPE chenillardUp={8,chenillardUpMotif,"K 2000"};
const MOTIF_TYPE chenillardDown={8,chenillardDownMotif,"K -2000"};

const MOTIF_TYPE* tableau_motif[3]={&upDown, &chenillardUp, &chenillardDown};

static int index_tableau_motif=0;



#include "led.h"

void taskLED(){
	int numero_motif=(HAL_GetTick()/globalDelayInMs)%(tableau_motif[index_tableau_motif]->size);
	LED_Set_Value_With_Int(tableau_motif[index_tableau_motif]->motif[numero_motif]);
	LED_Update();
}



#include "button.h"
#define NB_TOTAL_MOTIF 3

int needDisplayRefresh=0;
#define REFRESH_MOTIF 1
#define REFRESH_SPEED 2

void taskButton(){
	BUTTON_Update();
	if(BUTTON_Get_Pressed(CENTER)==1){
		index_tableau_motif++;
		index_tableau_motif%=NB_TOTAL_MOTIF;
		needDisplayRefresh=REFRESH_MOTIF;
	}
	if(BUTTON_Get_Pressed(DOWN)==1){
		globalDelayInMs+=10;
		needDisplayRefresh=REFRESH_SPEED;
	}
	if(BUTTON_Get_Pressed(UP)==1 && globalDelayInMs>10){
		globalDelayInMs-=10;
		needDisplayRefresh=REFRESH_SPEED;
	}
}


#include "ssd1315.h"
#include "fonts.h"
#include <stdio.h>

void screen_setup(){

	ssd1315_Init();
	ssd1315_Clear(SSD1315_COLOR_BLACK);

	ssd1315_Draw_String(0, 0, "Welcome ENSEA", &Font_7x10);

	char speed_buffer[16]={0};
	snprintf(speed_buffer, 16, "SPEED= %d", globalDelayInMs);
	ssd1315_Draw_String(0, 10, speed_buffer, &Font_7x10);

	char motif_buffer[16]={0};
	snprintf(motif_buffer, 16, "%s", tableau_motif[index_tableau_motif]->name);
	ssd1315_Draw_String(0, 20, motif_buffer, &Font_7x10);

	ssd1315_Refresh();
}

void taskScreen(){
	if(needDisplayRefresh==REFRESH_SPEED){
		printf("start %lu\r\n",HAL_GetTick());
		char speed_buffer[16]={0};
		snprintf(speed_buffer, 16, "SPEED= %d", globalDelayInMs);
		ssd1315_Draw_String(0, 10, speed_buffer, &Font_7x10);
		ssd1315_Refresh();
		printf("end %lu\r\n", HAL_GetTick());
	}
	if(needDisplayRefresh==REFRESH_MOTIF){
		printf("start %lu\r\n",HAL_GetTick());
		char motif_buffer[16]={0};
		snprintf(motif_buffer, 16, "%s", tableau_motif[index_tableau_motif]->name);
		ssd1315_Draw_String(0, 20, motif_buffer, &Font_7x10);
		ssd1315_Refresh();
		printf("end %lu\r\n", HAL_GetTick());
	}
	needDisplayRefresh=0;
}
