#include "SensorManager.h"



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

sensor_t sensor_arr [SENSORS]={0};


status_t SensorInit(char name[], interface_t interface, uint8_t id)
{
    status_t status=OK;
    //Assertions
    if(strlen(name)==0 || strlen(name)>=MAX_NAME_LEN) 
    {
        // printf("\nName length err. Len = %d", strlen(name));
        status=ERROR;
    }
    if(interface>=(uint8_t)INTERFACES_COUNT || interface < 0)
    {
        // printf("\nInterface error. Interface %d", interface);
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
        sensor_arr[id].interface=interface;
        switch (interface)
        {
            case ADC:
                bind_adc_itf(id);
                break;
            case UART:
                bind_uart_itf(id);
                /* code */
                break;
            case I2C:
                bind_i2c_itf(id);
                /* code */
                break;
            
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
        buff[strlen(sensor_arr[id].name)] = '\0'; // Bezpieczne zakończenie stringa
        status = OK;
    }
    return status;
}

status_t sensorGetInterface(uint8_t id, interface_t* interface)
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
        *interface = sensor_arr[id].interface;
    }
    return status;
}

float GetFloatValue(uint8_t id)
{
    return sensor_arr[id].itf.getFloatValue(&sensor_arr[id]);
}   

static void bind_adc_itf(uint8_t id)
{
    sensor_arr[id].itf=get_adc_itf();
}


static void bind_uart_itf(uint8_t id)
{
    sensor_arr[id].itf=get_uart_itf();
}


static void bind_i2c_itf(uint8_t id)
{
    sensor_arr[id].itf=get_i2c_itf();
}