#ifndef SENSORMANAGER_H
#define SENSORMANAGER_H

#include <assert.h>
#include <stdint.h>
#include <string.h>
#include <stdio.h>

enum interface {ADC=0,UART,I2C, INTERFACES_COUNT};
typedef enum interface interface_t;

enum initStatus {Initialized=111,Uninitialized=112};
typedef enum initStatus initStatus_t;

struct sensor 
{
    char name[50];
    interface_t interface;
    uint8_t id;
    initStatus_t isInitializated;
};
typedef struct sensor sensor_t;

enum status {OK, ERROR};
typedef enum status status_t;

struct sensorManager 
{
    sensor_t* sensor_arr;
    initStatus_t isInitializated;
};
typedef struct sensorManager sensorManager_t;

status_t SensorInit(sensor_t* sensor, char* name,uint8_t name_len, interface_t interface, uint8_t id);
status_t SensorManagerInit(sensor_t* sensor_arr);

#endif // SENSORMANAGER_H
