#include "unity.h"
#include "SensorManager.h"

void setUp(void)
{
}

void tearDown(void)
{
}

void test_isSensorInit(void)
{
    uint8_t id;
    char name[50];
    interface_t interface;
    sensor_t* sensor;

    SensorInit(sensor, name, interface,id);
}

void test_ReturnStatus(void)
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

void test_uninitializedArguments(void)
{
    uint8_t id;
    char name[50];
    interface_t interface;
    sensor_t* sensor;
    SensorInit(sensor, name, interface, id);

    TEST_ASSERT_EQUAL(0,strcmp(sensor->name,"NULL"));
    TEST_ASSERT_EQUAL((uint8_t)NA,sensor->interface);
    TEST_ASSERT_EQUAL(0,sensor->id);
}