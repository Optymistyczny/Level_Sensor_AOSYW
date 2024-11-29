#include "SensorManager.h"

#define MAX_SENSORS 10
#define MAX_NAME_LEN 50

enum interface { ADC = 0, UART, I2C, INTERFACES_COUNT };
enum status { OK, ERROR };

struct sensor_itf {
    float (*getFloatValue)(sensor_t* this);
};

struct sensor {
    sensor_itf_t itf;
    char name[MAX_NAME_LEN + 1];
    interface_t interface;
    uint8_t id;
};

status_t SensorInit(sensor_t* sensor, char* name, uint8_t name_len, interface_t interface, uint8_t id)
{
    if(sensor == NULL) return ERROR;

    if(name == NULL) return ERROR;

    if(name_len >= MAX_NAME_LEN) return ERROR;

    if(interface>(uint8_t)INTERFACES_COUNT || interface < 0) return ERROR;

    if(id<=0)return ERROR;

    strncpy(sensor->name,name, name_len);
    sensor->name[sizeof(sensor->name)/sizeof(char)-1]='\0';
    sensor->id=id;
    sensor->interface=interface;
    return OK;
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
                return manager->sensor_arr[i]->itf.getFloatValue((manager->sensor_arr[i]));
            }
        }
        else return -1.0f;
    }
}