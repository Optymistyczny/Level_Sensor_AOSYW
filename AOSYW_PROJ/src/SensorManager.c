#include "SensorManager.h"
#include "SensorManagerData.h"
#include "stdio.h"
#include <stddef.h>


//Sensor interfaces
#include "SEN0311.h"
#include "DS18B20.h"

sensor_t* sensor_array[SENSORS]={0};
temp_sensor_t temp_sensor;
dist_sensor_t dist_sensor;

static status_t bind_dist_itf(sensor_t* sensor)
{ 
    if(NULL == sensor)
    {
        //printf("\nSensor null...");
        return ERR; 
    } 
    if(distance_sensor != sensor->sensor_type)
    {
        //printf("\nNot dist sensor...");
        return ERR; 
    } 
    dist_sensor_t* this = (dist_sensor_t*)(sensor); 

    this->base.base_itf.getName=SEN0311_getName;
    this->dist_itf.getDistance_m=SEN0311_getDistance_m;
    this->dist_itf.getDistance_mm=SEN0311_getDistance_mm;
    return OKK;
}

static status_t bind_temp_itf(sensor_t* sensor)
{ 
    if(NULL == sensor)
    {
        //printf("\nSensor null...");
        return ERR; 
    } 
    if(temperature_sensor!=sensor->sensor_type)
    {
        //printf("\nNot temp sensor...");
        return ERR; 
    } 
    temp_sensor_t* this = (temp_sensor_t*)(sensor); 

    this->base.base_itf.getName=DS18B20_getName;
    this->temp_itf.getTemp_Celcious=DS18B20_getTemp_Celcious;
    this->temp_itf.getTemp_Fahrenheit=DS18B20_getTemp_Fahrenheit;
    return OKK;
}

static status_t bind_interfaces()
{
    status_t status=OKK;
    //printf("\nBinding temp itf...");
    status = bind_temp_itf((sensor_array[TEMPERATURE_SENSOR_ID]));
    //printf("\nDone. Status %d", status);
    //printf("\nBinding dist itf...");
    status = bind_dist_itf((sensor_array[DISTANCE_SENSOR_ID]));
    //printf("\nDone. Status %d", status);

    //printf("\nDone.");
    return status;
}

status_t initialize()
{
    dist_sensor.base.sensor_type=distance_sensor;
    temp_sensor.base.sensor_type=temperature_sensor;

    sensor_array[TEMPERATURE_SENSOR_ID]=(sensor_t*)&temp_sensor;
    sensor_array[DISTANCE_SENSOR_ID]=(sensor_t*)&dist_sensor;

    if(ERR == bind_interfaces()) return ERR;

    return OKK;
}

status_t getDistance_m(float* distance)
{    
    if(NULL == distance)
    {
        return ERR;
    } 
    if(distance_sensor!=sensor_array[DISTANCE_SENSOR_ID]->sensor_type || NULL == sensor_array[DISTANCE_SENSOR_ID])
    {
        return ERR;
    } 
    dist_sensor_t* this = (dist_sensor_t*)sensor_array[DISTANCE_SENSOR_ID];
    
    if(NULL == this->dist_itf.getDistance_m)
    {
        return ERR;
    }
    this->dist_itf.getDistance_m(sensor_array[DISTANCE_SENSOR_ID],distance);
    return OKK;
}

status_t getDistance_mm(float* distance)
{   
    if(NULL == distance)
    {
        return ERR;
    } 
    if(distance_sensor!=sensor_array[DISTANCE_SENSOR_ID]->sensor_type || NULL == sensor_array[DISTANCE_SENSOR_ID])
    {
        return ERR;
    } 
    dist_sensor_t* this = (dist_sensor_t*)sensor_array[DISTANCE_SENSOR_ID];
    
    if(NULL == this->dist_itf.getDistance_mm)
    {
        return ERR;
    }
    this->dist_itf.getDistance_mm(sensor_array[DISTANCE_SENSOR_ID],distance);
    return OKK;
}

status_t getTemperature_Celcious(float* temperature)
{    
    if(NULL == temperature)
    {
        return ERR;
    } 
    if(temperature_sensor!=sensor_array[TEMPERATURE_SENSOR_ID]->sensor_type || NULL == sensor_array[TEMPERATURE_SENSOR_ID])
    {
        return ERR;
    } 
    temp_sensor_t* this = (temp_sensor_t*)sensor_array[DISTANCE_SENSOR_ID];
    
    if(NULL == this->temp_itf.getTemp_Celcious)
    {
        return ERR;
    }
    this->temp_itf.getTemp_Celcious(sensor_array[DISTANCE_SENSOR_ID],temperature);
    return OKK;
}

status_t getTemperature_Fahrenheit(float* temperature)
{    
    if(NULL == temperature)
    {
        return ERR;
    } 
    if(temperature_sensor!=sensor_array[TEMPERATURE_SENSOR_ID]->sensor_type || NULL == sensor_array[TEMPERATURE_SENSOR_ID])
    {
        return ERR;
    } 
    temp_sensor_t* this = (temp_sensor_t*)sensor_array[DISTANCE_SENSOR_ID];
    
    if(NULL == this->temp_itf.getTemp_Fahrenheit)
    {
        return ERR;
    }
    this->temp_itf.getTemp_Fahrenheit(sensor_array[DISTANCE_SENSOR_ID], temperature);
    return OKK;
}

status_t getDistanceSensorName(char* buffer, const uint8_t len)
{
    if(NULL == buffer || len <=0) 
    {
        return ERR;
    }

    for(uint8_t i=0;i<len;i++)
    {
        buffer[i]='A';
    }
    return OKK;
}

status_t getTempSensorName(char* buffer, const uint8_t len)
{
    if(NULL == buffer || len <=0) 
    {
        return ERR;
    }

    for(uint8_t i=0;i<len;i++)
    {
        buffer[i]='A';
    }
    return OKK;
}
 
