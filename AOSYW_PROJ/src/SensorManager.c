#include "SensorManager.h"

#define MAX_SENSORS 10

enum interface {ADC=0,UART,I2C, INTERFACES_COUNT};
enum initStatus {Initialized=111,Uninitialized=112};
enum status {OK, ERROR};
struct sensor 
{
    sensor_itf_t itf;
    char name[50];
    interface_t interface;
    uint8_t id;
    initStatus_t isInitializated;
};
struct sensorManager 
{
    sensor_t** sensor_arr;
    uint8_t sensor_arr_size;
    initStatus_t isInitializated;
};

status_t SensorCreate(sensor_t* sensor)
{
    if(sensor==NULL)
    {
        return ERROR;
    } 
    else
    { 
        sensor->isInitializated=Initialized;
        return OK;
    }
}

status_t SensorInit(sensor_t* sensor, char* name, uint8_t name_len, interface_t interface, uint8_t id)
{
    uint8_t MAX = 50;
    if(sensor == NULL) return ERROR;

    if(name == NULL) return ERROR;

    if(name_len >= MAX) return ERROR;

    if(interface>(uint8_t)INTERFACES_COUNT || interface < 0) return ERROR;

    if(id<=0)return ERROR;

    if(sensor->isInitializated!=Initialized)
    {
        strncpy(sensor->name,name, name_len);
        sensor->name[sizeof(sensor->name)/sizeof(char)-1]='\0';
        sensor->id=id;
        sensor->interface=interface;
        sensor->isInitializated=Initialized;
        return OK;
    }
    return ERROR;
}

status_t SensorManagerInit(sensorManager_t* manager, sensor_t** sensor_array, uint8_t size)
{
    if(manager == NULL) return ERROR;
    if(sensor_array == NULL) return ERROR;
    
    for(uint8_t i=0;i<size;i++)
    {
        if(sensor_array[i]==NULL) return ERROR;
    }
    if(size <= 0 || size > MAX_SENSORS) return ERROR;

    manager->sensor_arr = sensor_array;
    manager->sensor_arr_size = size;

    return OK;
}


float GetFloatValue(sensorManager_t* manager,uint8_t sensor_id)
{
    for(uint8_t i=0;i<manager->sensor_arr_size;i++)
    {
        if(manager->sensor_arr[i]->id==sensor_id)
        {
            if (manager->sensor_arr[i]->itf.getFloatValue != NULL)
            {
                return manager->sensor_arr[i]->itf.getFloatValue((sensor_itf_t*)(manager->sensor_arr[i]));
            }
        }
        else return -1.0f;
    }
}