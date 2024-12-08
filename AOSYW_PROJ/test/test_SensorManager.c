#include "unity.h"
#include "SensorManager.h"
#include "SEN0311.h"
#include "DS18B20.h"

void setUp(void)
{
}

void tearDown(void)
{
}


void test_initialize()
{
    TEST_ASSERT_EQUAL(OKK, initialize());
}