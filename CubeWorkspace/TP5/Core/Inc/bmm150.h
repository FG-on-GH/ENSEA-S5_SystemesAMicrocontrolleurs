/*
 * bmm150.h
 *
 *  Created on: Jun 17, 2024
 *      Author: antotauv
 */

#ifndef INC_BMM150_H_
#define INC_BMM150_H_

uint8_t initDriverBMM150(SPI_HandleTypeDef * param);
uint8_t checkForBMM150Connection();
void writeOneRegister(uint8_t adress, uint8_t value);
uint8_t readOneRegister(uint8_t adress);
uint16_t readXValue();
uint16_t readXValue();
float readAngle();

#endif /* INC_BMM150_H_ */
