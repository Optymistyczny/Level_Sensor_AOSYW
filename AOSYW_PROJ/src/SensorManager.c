#include "SensorManager.h"

status_t SensorInit(sensor_t* sensor, char* name,interface_t interface, uint8_t id)
{
    if(sensor == NULL) return ERROR;
    if(name == NULL) return ERROR;

    //dodajemy obsługę interfejsu spoza zakresu
    if(interface>(uint8_t)INTERFACES_COUNT | interface < 0) return ERROR;
    return OK;
}