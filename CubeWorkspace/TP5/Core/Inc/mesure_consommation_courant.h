/*
 * mesure_consommation_courant.h
 *
 *  Created on: Jun 19, 2024
 *      Author: antotauv
 */

#ifndef INC_MESURE_CONSOMMATION_COURANT_H_
#define INC_MESURE_CONSOMMATION_COURANT_H_

extern TIM_HandleTypeDef htim4;
extern ADC_HandleTypeDef hadc1;
void setup();
void loop();

#endif /* INC_MESURE_CONSOMMATION_COURANT_H_ */
