#ifndef SENSORMANAGERDATA_H
#define SENSORMANAGERDATA_H

#include "SensorManager.h"

typedef struct sensor sensor_t;
typedef struct sensor_itf sensor_itf_t;

struct sensor_itf {
    float (*getFloatValue)(sensor_t* sensor);
};

struct sensor {
    sensor_itf_t itf;
    char name[MAX_NAME_LEN + 1];
    sensor_type_t sensor_type;
    uint8_t id;
};


#endif