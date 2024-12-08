#include "SEN0311.h"
#include <stddef.h>


 #include "stm32l0xx_hal.h"
 #include "main.h"

#define HEADER_BYTE 0
#define HBYTE 1
#define LBYTE 2
#define SUM_BYTE 3
#define EXPECTED_LEN 4

static status_t processInput(const uint8_t*,const uint8_t, float*);
static status_t SEN0311_UART_Receive(uint8_t*,const uint8_t);
float SEN0311getFloatValue(void);

//Interface functions
status_t SEN0311_getDistance_mm(const sensor_t* const sensor, float* val)
{
    if(NULL == sensor || NULL == val) return ERR;
    *val = SEN0311getFloatValue();
    if(-1 == *val) return ERR;
    else return OKK;

}
status_t SEN0311_getDistance_m(const sensor_t* const sensor,float* val)
{
    if(NULL == sensor || NULL == val) return ERR;
    *val = SEN0311getFloatValue();
    *val = *val /1000.0;
    if(-1 == *val) return ERR;
    else return OKK;
}
status_t SEN0311_getName(const sensor_t* const sensor, char* buffer, const uint8_t len)
{
    if(NULL == sensor || NULL == buffer) return ERR;
    return OKK;
}

float SEN0311getFloatValue(void)
{
    uint8_t buff [EXPECTED_LEN]={0};
    float out = 0.0;
    if(ERR == SEN0311_UART_Receive(buff, EXPECTED_LEN)) return -1.0;
    if(ERR == processInput(buff, EXPECTED_LEN, &out)) return -1.0;
    return out;
}

static uint8_t calculateChecksum(const uint8_t* buff) {
    return (buff[HEADER_BYTE] + buff[HBYTE] + buff[LBYTE]) & 0xFF;
}

static status_t processInput(const uint8_t* buff, const uint8_t len, float* out)
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

static status_t SEN0311_UART_Receive(uint8_t* buff,const uint8_t len)
{
	extern UART_HandleTypeDef huart1;
	uint16_t tmp=0;
	uint8_t received=0;
	if(NULL==buff)
		return ERR;

	 while(received==0) //dodać timeout
	 {
		 CLEAR_BIT((&huart1)->Instance->CR1 , 1<<2);//Reception cancelled
		 if((&huart1)->Instance->ISR & 1<<5) //RXNE
		 {
			 (&huart1)->Instance->RQR = (&huart1)->Instance->RQR | (1<<3);
		 }
		 if((&huart1)->Instance->ISR & 1<<3) //ORE
		 {
			 (&huart1)->Instance->ICR = (&huart1)->Instance->ICR | (1<<3);
		 }

		SET_BIT((&huart1)->Instance->CR1 , 1<<2);//Start reception}
		HAL_UARTEx_ReceiveToIdle(&huart1, buff, 4, &tmp, HAL_MAX_DELAY);
		CLEAR_BIT((&huart1)->Instance->CR1 , 1<<2);//Reception cancelled
		received = 1;
	 }
	 return OKK;
}
