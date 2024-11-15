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
    uint8_t id=1;
    char name[]="Water level sensor";
    interface_t interface=ADC;
    sensor_t sensor;
    status_t status=SensorInit(&sensor, name, interface,id);
    TEST_ASSERT_EQUAL(OK,status);
}

void test_ReturnStatusWhenGoodArguments(void)
{
    uint8_t id=1;
    char name[50];
    interface_t interface=ADC;
    sensor_t sensor;

    status_t status;
    status=SensorInit(&sensor, name, interface,id);
    TEST_ASSERT_EQUAL(OK, status);
}

void test_nullSensor(void)
{
    uint8_t id=1;
    char name[50];
    interface_t interface=ADC;
    status_t status=SensorInit(NULL, name, interface, id);
    TEST_ASSERT_EQUAL(ERROR,status);
}

void test_nullName(void)
{
    uint8_t id=1;
    interface_t interface=ADC;
    sensor_t sensor;
    status_t status=SensorInit(&sensor, NULL, interface, id);
    TEST_ASSERT_EQUAL(ERROR,status);
}

/**
 * W tym momencie zacząłem się zastanawiać, czy nie lepiej użyć zmiennych globalnych, bo cały czas inicjalizuję te same dane.
 */

void test_BadInterface(void)
{
    uint8_t id=1;
    char name[50];
    sensor_t sensor;

    status_t status=SensorInit(&sensor, name, 100, id);
    TEST_ASSERT_EQUAL(ERROR,status);

    sensor_t sensor1;
    status=SensorInit(&sensor1, name, ADC, id);
    TEST_ASSERT_EQUAL(OK,status);
    
    sensor_t sensor2;
    status=SensorInit(&sensor2, name, UART, id);
    TEST_ASSERT_EQUAL(OK,status);

    sensor_t sensor3;
    status=SensorInit(&sensor3, name, I2C, id);
    TEST_ASSERT_EQUAL(OK,status);

    sensor_t sensor4;
    status=SensorInit(&sensor4, name, -1, id);
    TEST_ASSERT_EQUAL(ERROR,status);
}

void test_ID_only_positive(void)
{
    char name[50];
    sensor_t sensor;
    interface_t interface=ADC;
    status_t status=SensorInit(&sensor, name, interface, 0);
    TEST_ASSERT_EQUAL(ERROR,status);
}

void test_proper_sensor_initialization(void)
{
    uint8_t id=1;
    char name[]="Water level sensor";
    interface_t interface=ADC;
    sensor_t sensor;
    status_t status=SensorInit(&sensor,name, interface, id);
    TEST_ASSERT_EQUAL(OK,status);
    TEST_ASSERT_EQUAL(ADC,sensor.interface);
    TEST_ASSERT_EQUAL(0,strncmp(sensor.name,name,sizeof(name)/sizeof(char)));
    TEST_ASSERT_EQUAL(1,sensor.id);
}

void test_multiple_initialization(void)
{
    uint8_t id=1;
    char name[]="Water level sensor";
    interface_t interface=ADC;
    sensor_t sensor;
    status_t status=SensorInit(&sensor,name, interface, id);
    TEST_ASSERT_EQUAL(OK,status);
    
    status=SensorInit(&sensor,name, interface, id);
    TEST_ASSERT_EQUAL(ERROR,status);
}

void test_multiple_various_initialization(void)
{
    uint8_t id1=1;
    char name1[]="Water level sensor";
    interface_t interface1=ADC;
    sensor_t Level_sensor;
    status_t status1=SensorInit(&Level_sensor,name1, interface1, id1);
    TEST_ASSERT_EQUAL(OK,status1);

    
    uint8_t id2=2;
    char name2[]="Temperature sensor";
    interface_t interface2=UART;
    sensor_t Temp_sensor;
    status_t status2=SensorInit(&Temp_sensor,name2, interface2, id2);
    TEST_ASSERT_EQUAL(OK,status2);

    
    uint8_t id3=3;
    char name3[]="Moisture level sensor";
    interface_t interface3=I2C;
    sensor_t Moist_sensor;
    status_t status3=SensorInit(&Moist_sensor,name3, interface3, id3);
    TEST_ASSERT_EQUAL(OK,status3);
}
void test_too_long_name_initialization(void)
{
    uint8_t id1=1;
    char name1[]="Water level sensorrrrrrrrrrrrrrrrrrrrrrrrrrrrrrrrrrrrrrrrrrrrrrrrrrrrrrrrrrrrrrr";
    interface_t interface1=ADC;
    sensor_t Level_sensor;
    status_t status1=SensorInit(&Level_sensor,name1, interface1, id1);
    TEST_ASSERT_EQUAL(ERROR,status1);
}