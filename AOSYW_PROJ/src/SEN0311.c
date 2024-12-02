#include "SEN0311.h"
#define HEADER_BYTE 0
#define HBYTE 1
#define LBYTE 2
#define SUM_BYTE 3

float SEN0311getFloatValue(sensor_t* sensor)
{
    printf("\nI am SEN0311");
    return 1.0;
}

status_t processInput(const uint8_t* buff, const uint8_t len, float* out)
{
    status_t status=OK;
    uint16_t temp;
    if(buff== NULL) status = ERROR;
    if(len != 4) status = ERROR;
    if(buff[SUM_BYTE] != ((buff[HEADER_BYTE]+buff[HBYTE]+buff[LBYTE]) & 0xFF)) status=ERROR;

    printf("\nSum expected %x \t Calculated %x",buff[SUM_BYTE], ((buff[HEADER_BYTE]+buff[HBYTE]+buff[LBYTE]) & 0xFF));
    if(OK==status)
    {   
        temp=(buff[HBYTE]*256+buff[LBYTE]);
        *out=(float)temp;
    }
    else 
    {
        *out = 0.0;
    }
    return status;
}