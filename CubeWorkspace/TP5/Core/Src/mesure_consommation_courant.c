/*
 * mesure_consommation_courant.c
 *
 *  Created on: Jun 19, 2024
 *      Author: antotauv
 */
#include "main.h"
#include "mesure_consommation_courant.h"
#include "led.h"
#include <stdio.h>
#include "bmm150.h"

extern SPI_HandleTypeDef hspi2;

void setup(){
	printf("**** TP5 : liaisons et bus, consommation electrique**** \r\n");
	HAL_TIM_Base_Start(&htim4);
	HAL_ADC_Start_IT(&hadc1);
	initDriverBMM150(&hspi2);
}

void loop(){
	//HAL_PWR_EnterSLEEPMode(0,PWR_SLEEPENTRY_WFI);

	//Lecture de l'angle (fonction bloquante car elle attend le bit DRDY)
	float angle_rad = readAngle();

	//Conversion Radians -> Degrés (180 / PI = 57.296)
    float angle_deg = angle_rad * 57.296f;

    //Affichage
    printf("Cap : %.2f degres\r\n", angle_deg);
}

void HAL_GPIO_EXTI_Callback(uint16_t GPIO_Pin){
	static int isOn=0;
	if(GPIO_Pin==ENC_BTN_Pin){
		printf("BTN pressed \r\n");
		LED_Set_Value_With_Int((isOn==0)?0:255);
		isOn=1-isOn;
		LED_Update();
	}
}

void HAL_ADC_ConvCpltCallback(ADC_HandleTypeDef *hadc){
	/*
	if(hadc->Instance == ADC1){
		uint16_t adc_read=HAL_ADC_GetValue(&hadc1);
		float voltage = (adc_read*3.3)/4095;
		float intensity = (voltage*1000)/(0.4*200);
		printf("Mesure courant : %d \t %f \t %f\r\n",(int) adc_read, voltage, intensity);
	}
	*/
}
