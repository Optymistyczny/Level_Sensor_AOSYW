#include "SensorManager.h"

status_t SensorInit(sensor_t* sensor, char* name,interface_t interface, uint8_t id)
{
    uint8_t MAX = 50;
    if(sensor == NULL) return ERROR;

    if(name == NULL) return ERROR;
    if(sizeof(name)/sizeof(char)>=MAX) return ERROR;

    if(interface>(uint8_t)INTERFACES_COUNT || interface < 0) return ERROR;

    if(id<=0)return ERROR;

    if(sensor->isInitializated!=Initialized)
    {
        strncpy(sensor->name,name, sizeof(sensor->name)/sizeof(char)-1);
        sensor->name[sizeof(sensor->name)/sizeof(char)-1]='\0';
        sensor->id=id;
        sensor->interface=interface;

        sensor->isInitializated=Initialized;
        return OK;
    }
    return ERROR;
}