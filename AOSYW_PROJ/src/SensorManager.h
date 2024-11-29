#ifndef SENSORMANAGER_H
#define SENSORMANAGER_H

#include <assert.h>
#include <stdint.h>
#include <string.h>
#include <stdio.h>

#define MAX_NAME_LEN 50
#define SENSORS 3

typedef enum status status_t;
typedef enum interface interface_t;
enum status { OK, ERROR };
enum interface { ADC = 0, UART, I2C, INTERFACES_COUNT };

//zamiast przekazywać dwa parametry jak char* i długość to daję samą tablicę
status_t SensorInit(char name[], interface_t interface, uint8_t id);

status_t sensorGetInterface(uint8_t id, interface_t* interface);
status_t sensorGetName(uint8_t id, char* buff);
float GetFloatValue(uint8_t id);

#endif // SENSORMANAGER_H
