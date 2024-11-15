#ifndef SENSORMANAGER_H
#define SENSORMANAGER_H

#include <assert.h>
#include <stdint.h>
#include <string.h>

enum interface {ADC,UART,I2C};
typedef enum interface interface_t;

struct sensor 
{
    char name[50];
    interface_t interface;
    uint8_t id;
};
typedef struct sensor sensor_t;

enum status {OK, FAIL, ERROR};
typedef enum status status_t;

status_t SensorInit(sensor_t* sensor, char* name,interface_t interface, uint8_t id);

#endif // SENSORMANAGER_H
