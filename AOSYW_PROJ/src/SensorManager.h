#ifndef SENSORMANAGER_H
#define SENSORMANAGER_H

#include <assert.h>
#include <stdint.h>
#include <string.h>
#include <stdio.h>

// Forward declarations
typedef struct sensor sensor_t;
typedef struct sensor_itf sensor_itf_t;
typedef enum interface interface_t;
typedef enum status status_t;

struct sensorManager 
{
    sensor_t** sensor_arr;
    uint8_t sensor_arr_size;
};
typedef struct sensorManager sensorManager_t;

status_t SensorManagerInit(sensorManager_t* manager, sensor_t** sensor_array, uint8_t size);
float GetFloatValue(sensorManager_t* manager, uint8_t sensor_id);

#endif // SENSORMANAGER_H
