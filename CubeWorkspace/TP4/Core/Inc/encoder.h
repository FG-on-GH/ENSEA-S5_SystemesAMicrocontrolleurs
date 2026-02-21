/*
 * encoder.h
 *
 *  Created on: Nov 10, 2025
 *      Author: FG
 */

#ifndef INC_ENCODER_H_
#define INC_ENCODER_H_

#include "stm32l4xx_hal.h"

typedef struct encoder{
	TIM_HandleTypeDef * htim;
	int32_t max_value;
	int32_t min_value;
}ENCODER;

void encoder_init(TIM_HandleTypeDef * htim_param, int32_t min, int32_t max);
int32_t encoder_read();


#define SATURE_MAX 8
#define SATURE_MIN -8

void setup();
void loop();

#endif /* INC_ENCODER_H_ */
