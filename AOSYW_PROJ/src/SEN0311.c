#include "SEN0311.h"
#include "stm32l0xx_hal.h"
#include "main.h"
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
    if(ERR == SEN0311_UART_Receive(buff, EXPECTED_LEN)) return -1.0;
    if(ERR == processInput(buff, EXPECTED_LEN, &out)) return -1.0;
    return out;
}

static uint8_t calculateChecksum(const uint8_t* buff) {
    return (buff[HEADER_BYTE] + buff[HBYTE] + buff[LBYTE]) & 0xFF;
}

status_t processInput(const uint8_t* buff, const uint8_t len, float* out)
{
    status_t status=OKK;
    uint16_t temp, sum;
    if (buff == NULL || out == NULL || len != EXPECTED_LEN) return ERR;

    sum=calculateChecksum(buff); 

    if(buff[SUM_BYTE] != sum) status=ERR;

    // printf("\nSum expected %x \t Calculated %x",buff[SUM_BYTE], ((buff[HEADER_BYTE]+buff[HBYTE]+buff[LBYTE]) & 0xFF));
    if(OKK==status)
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
	extern UART_HandleTypeDef huart1;
	extern void Error_Handler();
	uint16_t tmp=0;
	uint8_t received=0;
	if(NULL==buff)
		return ERR;

	while(received==0) //dodać timeout
	{
		HAL_UARTEx_ReceiveToIdle(&huart1, buff, 4, &tmp, HAL_MAX_DELAY);
		if(tmp==EXPECTED_LEN)
		{
			HAL_GPIO_TogglePin(LD2_GPIO_Port, LD2_Pin);
			received=1;
		}
	}
	return OKK;
}
