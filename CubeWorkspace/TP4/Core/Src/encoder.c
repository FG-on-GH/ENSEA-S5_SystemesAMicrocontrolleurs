/*
 * encoder.c
 *
 *  Created on: Nov 10, 2025
 *      Author: FG
 */


#include "encoder.h"
#include "stepperMotor.h"

static ENCODER encoder;

void encoder_init(TIM_HandleTypeDef * htim_param, int32_t min, int32_t max){
	  encoder.htim = htim_param;
	  encoder.min_value = min;
	  encoder.max_value = max;
	  HAL_TIM_Encoder_Start(encoder.htim, TIM_CHANNEL_ALL);
	  encoder.htim->Instance->CNT=0;
}

int32_t encoder_read(){
	if ((int32_t)encoder.htim->Instance->CNT > SATURE_MAX){
		encoder.htim->Instance->CNT=SATURE_MAX;
	}
	else if ((int32_t)encoder.htim->Instance->CNT < SATURE_MIN){
		encoder.htim->Instance->CNT=SATURE_MIN;
	}
	return (int32_t)(encoder.htim->Instance->CNT);
}



#include "ssd1315.h"
#include "fonts.h"
#include "tim.h"

void setup(){
	encoder_init(&htim2, SATURE_MAX, SATURE_MIN);
	ssd1315_Init();
	ssd1315_Clear(SSD1315_COLOR_BLACK);
	ssd1315_Refresh();

	init_stepper(
			&htim3,
			TIM_CHANNEL_1,
			GPIOA,
			GPIO_PIN_7,
			GPIOA,
			GPIO_PIN_11,
	        GPIOB,
			GPIO_PIN_12,
	        GPIOA,
			GPIO_PIN_12);
	launch_stepper(0);
}


#include <stdio.h>
#include <inttypes.h>

void loop(){
	static int32_t last = 0;
	int32_t pos = encoder_read();
	if (pos != last){
		char buffer1[30]={0};
		snprintf(buffer1, 30, "Speed level = %" PRId32 " ", pos);
		ssd1315_Draw_String(0, 0, buffer1, &Font_7x10);
		char buffer2[30]={0};
		snprintf(buffer2, 30, "%f tr/min", get_rpm());
		ssd1315_Draw_String(0, 15, buffer2, &Font_7x10);
		ssd1315_Refresh();
		last = pos;
	}
	launch_stepper(pos);
}





