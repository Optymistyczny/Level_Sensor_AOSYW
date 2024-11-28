#ifndef SENSORMANAGER_H
#define SENSORMANAGER_H

#include <assert.h>
#include <stdint.h>
#include <string.h>
#include <stdio.h>

typedef enum interface interface_t;
typedef enum initStatus initStatus_t;
typedef enum status status_t;

typedef struct sensor_itf sensor_itf_t;
typedef struct sensorManager sensorManager_t;
typedef struct sensor sensor_t;

struct sensor_itf
{
    float (*getFloatValue)(sensor_itf_t *this);
};

status_t SensorInit(sensor_t* sensor, char* name,uint8_t name_len, interface_t interface, uint8_t id);
status_t SensorManagerInit(sensorManager_t* manager, sensor_t** sensor_array, uint8_t size);
float GetFloatValue(sensorManager_t* manager,uint8_t sensor_id);

#endif // SENSORMANAGER_H
