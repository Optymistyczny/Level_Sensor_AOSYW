#include "SEN0311.h"
#define HEADER_BYTE 0
#define HBYTE 1
#define LBYTE 2
#define SUM_BYTE 3
#define EXPECTED_LEN 4

float SEN0311getFloatValue(sensor_t* sensor)
{
    uint8_t buff [EXPECTED_LEN]={0};
    float out = 0.0;

    if(NULL==sensor) return -1.0;
    if(ERROR == SEN0311_UART_Receive(buff, EXPECTED_LEN)) return -1.0;
    if(ERROR == processInput(buff, EXPECTED_LEN, &out)) return -1.0;
    return out;
}

static uint8_t calculateChecksum(const uint8_t* buff) {
    return (buff[HEADER_BYTE] + buff[HBYTE] + buff[LBYTE]) & 0xFF;
}

status_t processInput(const uint8_t* buff, const uint8_t len, float* out)
{
    status_t status=OK;
    uint16_t temp, sum;
    if (buff == NULL || out == NULL || len != EXPECTED_LEN) return ERROR;

    sum=calculateChecksum(buff); 

    if(buff[SUM_BYTE] != sum) status=ERROR;

    // printf("\nSum expected %x \t Calculated %x",buff[SUM_BYTE], ((buff[HEADER_BYTE]+buff[HBYTE]+buff[LBYTE]) & 0xFF));
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

status_t SEN0311_UART_Receive(uint8_t* buff,const uint8_t len)
{
    return OK;
}
