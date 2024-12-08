#ifndef SENSORMANAGER_H
#define SENSORMANAGER_H

#include <stdint.h>

typedef enum { OKK, ERR } status_t;
//Nowe API
status_t initialize();
status_t getDistance_m(float*);
status_t getDistance_mm(float*);
status_t getTemperature_Celcious(float*);
status_t getTemperature_Fahrenheit(float*);
status_t getDistanceSensorName(char*, const uint8_t);
status_t getTempSensorName(char*, const uint8_t);

#endif // SENSORMANAGER_H
