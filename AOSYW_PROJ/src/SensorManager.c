#include "SensorManager.h"

#define MAX_SENSORS 10

status_t SensorInit(sensor_t* sensor, char* name, uint8_t name_len, interface_t interface, uint8_t id)
{
    uint8_t MAX = 50;
    if(sensor == NULL) return ERROR;

    if(name == NULL) return ERROR;

    if( name_len >= MAX) return ERROR;

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
    return OK;
}


float GetValue(sensorManager_t* manager,uint8_t sensor_id)
{
    // for(uint8_t i=0;i<manager->sensor_arr_size;i++)
    // {
    //     if(manager->sensor_arr[i]->id==id)
    //     {
    //         return manager->sensor_arr[i]->itf->getValue(&sensor_arr[i]);
    //     }
    // }
    return 1.0;
}