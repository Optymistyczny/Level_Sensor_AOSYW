#include "unity.h"
#include "SEN0311.h"
void setUp(void)
{
}

void tearDown(void)
{
}

void test_issensorInit(void)
{
    sensor_t sensor;
    SEN0311getFloatValue(&sensor);
}
void test_processingInput(void)
{
    uint8_t buff [4] = {0xFF, 0x07, 0xA1, 0xA7};
    float out = 0.0;
    status_t status = processInput(buff, 4, &out);
    TEST_ASSERT_EQUAL(OK,status);
    TEST_ASSERT_EQUAL_FLOAT(1953,out);

    uint8_t buff1 [4] = {0xFF,0x00,	0x00, 0xFF};
    out = 0.0;
    status = processInput(buff1, 4, &out);
    TEST_ASSERT_EQUAL(OK,status);
    TEST_ASSERT_EQUAL_FLOAT(0,out);
    
    uint8_t buff2 [4] = {0xFF,0xFF,0xFF,0xFD};
    out = 0.0;
    status = processInput(buff2, 4, &out);
    TEST_ASSERT_EQUAL(OK,status);
    TEST_ASSERT_EQUAL_FLOAT(65535,out);

    uint8_t buff3 [4] = {0xFF,0x80,	0x00, 0x7F};
    out = 0.0;
    status = processInput(buff3, 4, &out);
    TEST_ASSERT_EQUAL(OK,status);
    TEST_ASSERT_EQUAL_FLOAT(32768,out);

    uint8_t buff4 [4] = {0xFF,0x00, 0x01,0x00};
    out = 0.0;
    status = processInput(buff4, 4, &out);
    TEST_ASSERT_EQUAL(OK,status);
    TEST_ASSERT_EQUAL_FLOAT(1,out);

    uint8_t buff5 [4] = {0xFF,0x01,0xFF,0xFF};
    out = 0.0;
    status = processInput(buff5, 4, &out);
    TEST_ASSERT_EQUAL(OK,status);
    TEST_ASSERT_EQUAL_FLOAT(511,out);
}