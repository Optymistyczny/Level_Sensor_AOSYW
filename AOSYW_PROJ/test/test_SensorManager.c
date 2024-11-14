#include "unity.h"
#include "SensorManager.h"

void setUp(void)
{
}

void tearDown(void)
{
}

void test_SensorManager_NeedToImplement(void)
{
    TEST_IGNORE_MESSAGE("Need to Implement SensorManager");
}

void test_isSensorInit(void)
{
    uint8_t id;
    char name[50];
    interface_t interface;
    sensor_t* sensor;

    SensorInit(sensor, name, interface,id);
}

void test_SensorInitReturnValue(void)
{
    uint8_t id;
    char name[50];
    interface_t interface;
    sensor_t* sensor;

    status_t status = OK;
    status_t status2 = OK;
    status2=SensorInit(sensor, name, interface,id);
    TEST_ASSERT_EQUAL_UINT8((uint8_t)status,(uint8_t)status2);
}

