#ifndef SEN0311_H
#define SEN0311_H

#include "SensorManagerData.h" //for status_t

//Function signature must correspond to the interface to properly assign ptr
status_t SEN0311_getDistance_mm(const sensor_t* const sensor,float*);
status_t SEN0311_getDistance_m(const sensor_t* const sensor,float*);
status_t SEN0311_getName(const sensor_t* const sensor, char*, const uint8_t);

#endif