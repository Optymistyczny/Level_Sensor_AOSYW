#include "DS18B20.h"
#include <stddef.h>

static float convertCtoF(float* val);

status_t DS18B20_getTemp_Celcious(const sensor_t* const sensor, float* val)
{
    if(NULL == sensor || NULL == val) return ERR;
    *val=24.0;
    return OKK;
}
status_t DS18B20_getTemp_Fahrenheit(const sensor_t* const sensor, float* val)
{
    if(NULL == sensor || NULL == val) return ERR;
    if(ERR == DS18B20_getTemp_Celcious(sensor, val)) return ERR;
    *val = convertCtoF(val);
    return OKK;
}
status_t DS18B20_getName(const sensor_t* const sensor, char* buffer, const uint8_t len)
{
    if(NULL == sensor || NULL == buffer) return ERR;
    return OKK;
}
static float convertCtoF(float* val)
{
    if(NULL == val) return -1.0;
    return *val = (*val)*(9.0/5.0) + 32.0;
}
