#ifndef SENSORMANAGER_H
#define SENSORMANAGER_H

#include <assert.h>
#include <stdint.h>
#include <string.h>
#include <stdio.h>

#define MAX_NAME_LEN 50
#define SENSORS 3

typedef enum status status_t;
typedef enum sensor_type sensor_type_t;
enum status { OKK, ERR };
enum sensor_type { SEN0311 = 0, DS18B20, SENSORS_COUNT };

status_t sensorInit(char name[], sensor_type_t sensor_type, uint8_t id);
status_t sensorGetSensorType(uint8_t id, sensor_type_t* sensor_type);
status_t sensorGetName(uint8_t id, char* buff);
float getFloatValue(uint8_t id);

#endif // SENSORMANAGER_H
