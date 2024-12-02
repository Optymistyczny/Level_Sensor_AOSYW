#include "SensorManager.h"
#include "SensorManagerData.h"

//Sensors
#include "SEN0311.h"
#include "DS18B20.h"

static void bind_SEN0311_itf(sensor_t*);
static void bind_DS18B20_itf(sensor_t*);

sensor_t sensor_arr [SENSORS]={0};

status_t sensorInit(char name[], sensor_type_t sensor_type, uint8_t id)
{
    status_t status=OK;
    //Assertions
    if(strlen(name)==0 || strlen(name)>=MAX_NAME_LEN) 
    {

        // printf("\nName length err. Len = %d", strlen(name));
        status=ERROR;
    }
    if(sensor_type>=(uint8_t)SENSORS_COUNT || sensor_type < 0)
    {
        // printf("\nSensor type error. Sensor type:  %00d", sensor_type);
        status=ERROR;
    }        
    if(id < 1 || id > SENSORS)
    {
        // printf("\nID error. ID = %d",id);
        status=ERROR;
    } 
    for(uint8_t i=0;i<strlen(name);i++)
    {
        if(name[i]<1 || name[i]>127) 
        {
            status=ERROR;
            break;
        }
    }
    if(status!=ERROR)
    {
        id-=1;
        strncpy(sensor_arr[id].name, name, strlen(name));
        sensor_arr[id].name[strlen(name)]='\0';
        sensor_arr[id].sensor_type=sensor_type;

        
        //Rozbudowa o dodatkowe sensory poprzez zaimplementowanie interfejsu w pliku <nazwa_sensora>.c +.h i dodanie funkcji przypisującej interfejs do case'a.
        //Należy pamiętać o inkluzji plików nagłówkowych do SensorManager.h oraz dodaniu prototypu funkcji bindującej na górze pliku.
        switch (sensor_type)
        {
            case SEN0311:
                bind_SEN0311_itf(&sensor_arr[id]);
                break;
            case DS18B20:
                bind_DS18B20_itf(&sensor_arr[id]);
                break;         
            // case some_other_sensor:
            //     bind_some_other_sensor_itf(id);
            //     break;               
            default:
                status = ERROR;
                break;
            }
    }
    return status;
}

status_t sensorGetName(uint8_t id, char* buff)
{
    status_t status=OK;
    if(id < 1 || id > SENSORS)
    {
        // printf("\nID error. ID = %d",id);
        status=ERROR;
    } 
    else
    {
        id-=1;
        strcpy(buff, sensor_arr[id].name); //kopiowanie do '\0'
        buff[strlen(sensor_arr[id].name)] = '\0';
        status = OK;
    }
    return status;
}

status_t sensorGetSensorType(uint8_t id, sensor_type_t* sensor_type)
{
    status_t status=OK;
    if(id < 1 || id > SENSORS)
    {
        // printf("\nID error. ID = %d",id);
        status=ERROR;
    } 
    else
    {
        id-=1;
        *sensor_type = sensor_arr[id].sensor_type;
    }
    return status;
}

float getFloatValue(uint8_t id)
{
    return sensor_arr[id].itf.getFloatValue(&sensor_arr[id]);
}   

static void bind_SEN0311_itf(sensor_t* sensor)
{
    sensor->itf.getFloatValue=SEN0311getFloatValue;
}

static void bind_DS18B20_itf(sensor_t* sensor)
{
    sensor->itf.getFloatValue=DS18B20getFloatValue;
}