#include "SensorManager.h"

#define MAX_SENSORS 10
#define MAX_NAME_LEN 50
#define SENSORS 3

typedef struct sensor sensor_t;
typedef struct sensor_itf sensor_itf_t;



struct sensor_itf {
    float (*getFloatValue)(sensor_t* this);
};

struct sensor {
    sensor_itf_t itf;
    char name[MAX_NAME_LEN + 1];
    interface_t interface;
    uint8_t id;
};
//Aplikacja nie może znać szczegółów implementacji sensorów, więc nie może alokować im  pamięci -> albo alokuje dynamicznie sensor_t*, albo pamięć jest alokowana gdzieś indziej.

sensor_t sensor_arr [SENSORS];

status_t SensorInit(char name[], interface_t interface, uint8_t id)
{
    if(strlen(name)==0 || strlen(name)>=MAX_NAME_LEN) return ERROR;
    if(interface>(uint8_t)INTERFACES_COUNT || interface < 0) return ERROR;
    if(id < 1 || id > MAX_SENSORS) return ERROR;

    id-=1;
    strncpy(sensor_arr[id].name, name, strlen(name));
    sensor_arr[id].name[strlen(name)]='\0';
    sensor_arr[id].interface=interface;
    return OK;
}

float GetFloatValue(uint8_t id)
{
    return sensor_arr[id].itf.getFloatValue(&sensor_arr[id]);
}