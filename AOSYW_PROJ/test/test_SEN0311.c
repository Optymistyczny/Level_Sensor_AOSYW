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
    TEST_IGNORE();
    sensor_t sensor;
    SEN0311getFloatValue(&sensor);
}
void test_processingInput(void)
{
    uint8_t buff [4] = {0xFF, 0x07, 0xA1, 0xA7};
    float out = 0.0;
    status_t status = processInput(buff, out);
    TEST_ASSERT_EQUAL(OK,status);
    TEST_ASSERT_EQUAL((uint32_t)1953,out);
}