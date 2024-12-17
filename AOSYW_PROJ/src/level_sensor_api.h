#ifndef LEVEL_SENSOR_API_H
#define LEVEL_SENSOR_API_H


typedef enum {distance, temperature, measurement_type_num} measurement_type_t;

typedef struct
{
	measurement_type_t type;
	void* value;
}Queue_element_t;


void StartTaskSensorRunTask(void *argument);
 
#endif