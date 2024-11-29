#ifndef SENSORMANAGER_H
#define SENSORMANAGER_H

#include <assert.h>
#include <stdint.h>
#include <string.h>
#include <stdio.h>

typedef enum status status_t;
typedef enum interface interface_t;
enum status { OK, ERROR };
enum interface { ADC = 0, UART, I2C, INTERFACES_COUNT };

//zamiast przekazywać dwa parametry jak char* i długość to daję samą tablicę
status_t SensorInit(char name[], interface_t interface, uint8_t id);
float GetFloatValue(uint8_t id);

#endif // SENSORMANAGER_H
