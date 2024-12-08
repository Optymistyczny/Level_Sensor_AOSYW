#ifndef SENSORMANAGERDATA_H
#define SENSORMANAGERDATA_H

#include "SensorManager.h" //for status_t

#define MAX_NAME_LEN 50
#define SENSORS 2
#define DISTANCE_SENSOR_ID 0
#define TEMPERATURE_SENSOR_ID 1

typedef enum {temperature_sensor, distance_sensor} sensor_type_t;

//Klasa "bazowa", która jest przekazywana do funkcji jako argument

typedef struct sensor sensor_t;
typedef struct base_itf base_itf_t;
typedef struct temp_itf temp_itf_t;
typedef struct dist_itf dist_itf_t;

struct base_itf
{
    status_t (*getName)(const sensor_t* const sensor, char* buffer, const uint8_t len);
};

struct temp_itf
{
    status_t (*getTemp_Celcious)(const sensor_t* const sensor, float* val);
    status_t (*getTemp_Fahrenheit)(const sensor_t* const sensor, float* val);
};

struct dist_itf
{
    status_t (*getDistance_mm)(const sensor_t* const sensor, float* val);
    status_t (*getDistance_m)(const sensor_t* const sensor, float* val);
};

typedef struct sensor{
    base_itf_t base_itf;
    sensor_type_t sensor_type;
    char name[MAX_NAME_LEN + 1];
}sensor_t;

typedef struct
{
    sensor_t base;
    dist_itf_t dist_itf;
}dist_sensor_t;

typedef struct
{
    sensor_t base;
    temp_itf_t temp_itf;
}temp_sensor_t;








#endif