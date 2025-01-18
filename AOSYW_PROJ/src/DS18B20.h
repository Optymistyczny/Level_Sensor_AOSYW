#ifndef DS18B20_H
#define DS18B20_H

#include "SensorManagerData.h"// for status_t

//Function signature must correspond to the interface to properly assign ptr
status_t DS18B20_getTemp_Celcious(const sensor_t* const sensor, float* val);
status_t DS18B20_getTemp_Fahrenheit(const sensor_t* const sensor, float* val);
status_t DS18B20_getName(const sensor_t* const sensor, char* buffer, const uint8_t len);
#endif
