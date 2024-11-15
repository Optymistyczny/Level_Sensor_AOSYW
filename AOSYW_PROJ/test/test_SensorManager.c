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

void test_ReturnStatusWhenGoodArguments(void)
{
    uint8_t id;
    char name[50];
    interface_t interface;
    sensor_t* sensor;

    status_t status;
    status=SensorInit(sensor, name, interface,id);
    TEST_ASSERT_EQUAL_UINT8(OK, status);
}

void test_nullSensor(void)
{
    uint8_t id;
    char name[50];
    interface_t interface;
    status_t status=SensorInit(NULL, name, interface, id);
    TEST_ASSERT_EQUAL(ERROR,status);
}

void test_nullName(void)
{
    uint8_t id;
    interface_t interface;
    sensor_t* sensor;
    status_t status=SensorInit(sensor, NULL, interface, id);
    TEST_ASSERT_EQUAL(ERROR,status);
}

/**
 * W tym momencie zacząłem się zastanawiać, czy nie lepiej użyć zmiennych globalnych, bo cały czas inicjalizuję te same dane.
 */

void test_BadInterface(void)
{
    uint8_t id;
    char name[50];
    sensor_t* sensor;

    status_t status=SensorInit(sensor, name, 100, id);
    TEST_ASSERT_EQUAL(ERROR,status);

    status=SensorInit(sensor, name, ADC, id);
    TEST_ASSERT_EQUAL(OK,status);
    
    status=SensorInit(sensor, name, UART, id);
    TEST_ASSERT_EQUAL(OK,status);

    status=SensorInit(sensor, name, I2C, id);
    TEST_ASSERT_EQUAL(OK,status);

    status=SensorInit(sensor, name, -1, id);
    TEST_ASSERT_EQUAL(ERROR,status);
}