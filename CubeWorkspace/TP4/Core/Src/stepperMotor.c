/*
 * stepperMotor.c
 *
 *  Created on: Nov 10, 2025
 *      Author: FG
 */

#include "stepperMotor.h"

STEPPERMOTOR steppermotor;

void init_stepper
		(TIM_HandleTypeDef * htim_pwm_p,
		uint32_t pwm_channel_number_p,
		GPIO_TypeDef * gpio_direction_p,
		uint16_t gpio_direction_pin_p,
		GPIO_TypeDef * gpio_ms1_p,
		uint16_t gpio_ms1_pin_p,
		GPIO_TypeDef * gpio_ms2_p,
		uint16_t gpio_ms2_pin_p,
		GPIO_TypeDef * gpio_enable_p,
		uint16_t gpio_enable_pin_p)

{
	steppermotor.htim_pwm         	= htim_pwm_p;
	steppermotor.pwm_channel_number = pwm_channel_number_p;
	steppermotor.gpio_direction   	= gpio_direction_p;
	steppermotor.gpio_direction_pin = gpio_direction_pin_p;
	steppermotor.gpio_ms1         	= gpio_ms1_p;
	steppermotor.gpio_ms1_pin     	= gpio_ms1_pin_p;
	steppermotor.gpio_ms2         	= gpio_ms2_p;
	steppermotor.gpio_ms2_pin     	= gpio_ms2_pin_p;
	steppermotor.gpio_enable      	= gpio_enable_p;
	steppermotor.gpio_enable_pin  	= gpio_enable_pin_p;
	steppermotor.speed            	= 0;
	steppermotor.step_target      	= 0;
	steppermotor.step_actual      	= 0;

	HAL_GPIO_WritePin(steppermotor.gpio_ms1, steppermotor.gpio_ms1_pin, GPIO_PIN_SET);
	HAL_GPIO_WritePin(steppermotor.gpio_ms2, steppermotor.gpio_ms2_pin, GPIO_PIN_RESET);

	HAL_GPIO_WritePin(steppermotor.gpio_direction, steppermotor.gpio_direction_pin, GPIO_PIN_RESET);

	HAL_GPIO_WritePin(steppermotor.gpio_enable,   steppermotor.gpio_enable_pin,   GPIO_PIN_SET);

	HAL_TIM_PWM_Start(steppermotor.htim_pwm, steppermotor.pwm_channel_number);
}


#define SATURE_MAX 8
#define SATURE_MIN -8

int tab_ARR[8] = {14970, 7575, 3012, 1497, 500, 250, 166, 125};

void launch_stepper(int speed){

	if(speed>SATURE_MAX){
		speed=SATURE_MAX;
	}
	else if(speed<SATURE_MIN){
		speed=SATURE_MIN;
	}

	if(speed==0){
		steppermotor.htim_pwm->Instance->CCR1=0;
	}
	else{

		if(speed<0){
			HAL_GPIO_WritePin(
				steppermotor.gpio_direction,
				steppermotor.gpio_direction_pin,
				GPIO_PIN_RESET);
			speed*=(-1);
		}
		else{
			HAL_GPIO_WritePin(
				steppermotor.gpio_direction,
				steppermotor.gpio_direction_pin,
				GPIO_PIN_SET);
		}

		steppermotor.speed=speed;
		steppermotor.htim_pwm->Instance->ARR=tab_ARR[speed-1];
		steppermotor.htim_pwm->Instance->CCR1=tab_ARR[speed-1]/2;
		HAL_GPIO_WritePin(steppermotor.gpio_enable, steppermotor.gpio_enable_pin,0);
	}


}

#define STEPS_PER_REV        400
#define TIM_APB1_TIMER_HZ    80000000

float get_rpm(){
	if(steppermotor.speed==0){
		return 0;
	}
	uint32_t psc = 799;
	uint32_t arr = steppermotor.htim_pwm->Instance->ARR;
	uint32_t f_tick = TIM_APB1_TIMER_HZ / (psc + 1);

	float f_step = (float)f_tick / (float)(arr + 1U);
	float rpm    = (f_step * 60.0) / (float)STEPS_PER_REV;

	GPIO_PinState dir = HAL_GPIO_ReadPin(steppermotor.gpio_direction, steppermotor.gpio_direction_pin);
	if (dir == GPIO_PIN_SET) {
	rpm = -rpm;
	}
	return rpm;
}



