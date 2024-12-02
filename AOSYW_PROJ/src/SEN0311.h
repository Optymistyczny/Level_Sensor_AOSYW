#ifndef SEN0311_H
#define SEN0311_H

#include "SensorManagerData.h"

float SEN0311getFloatValue(sensor_t* sensor);
status_t processInput(const uint8_t* buff,const uint8_t len, float* out);

#endif