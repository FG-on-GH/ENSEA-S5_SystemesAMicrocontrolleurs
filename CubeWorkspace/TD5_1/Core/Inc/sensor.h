/*
 * sensor.h
 *
 *  Created on: Oct 22, 2025
 *      Author: FG
 */

#ifndef INC_SENSOR_H_
#define INC_SENSOR_H_



typedef enum {
	ACTIVE,
	INACTIVE
} SENSOR_STATE;

#define SENSOR_NUMBER 5

typedef struct{
	int id;
	float threshold;
	float value;
	SENSOR_STATE state;
} SENSOR;

typedef struct{
	SENSOR sensors[SENSOR_NUMBER];
} SENSOR_ARRAY;



void init_system(SENSOR_ARRAY * system);
void display_system(SENSOR_ARRAY * system);
void read_sensors(SENSOR_ARRAY * system);
void check_threshold(SENSOR * sensor);



void setup();
void loop();



#endif /* INC_SENSOR_H_ */
