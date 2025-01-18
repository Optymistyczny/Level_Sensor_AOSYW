#ifndef LEVEL_SENSOR_OS_H_
#define LEVEL_SENSOR_OS_H_

#include "cmsis_os.h"

typedef enum {distance_mm, distance_m, temperatureC, temperatureF, measurement_type_num} measurement_type_t;

typedef struct
{
	measurement_type_t type;
	const uint32_t id; 			//between 0 - 31
	void* value;
}measure_element_t;

osStatus_t init();
osStatus_t measure(const measure_element_t*);
osStatus_t waitForMeasurement(const measure_element_t*, const uint32_t timeout);

void SensorProcess(void);

#endif /* LEVEL_SENSOR_OS_H_ */
