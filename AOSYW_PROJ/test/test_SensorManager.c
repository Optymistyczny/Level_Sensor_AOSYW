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
    status_t status=SensorInit(&sensor, name, strlen(name), interface,id);
    TEST_ASSERT_EQUAL(OK,status);
}

void test_ReturnStatusWhenGoodArguments(void)
{
    uint8_t id=1;
    char name[50];
    interface_t interface=ADC;
    sensor_t sensor;

    status_t status;
    status=SensorInit(&sensor, name, strlen(name), interface,id);
    TEST_ASSERT_EQUAL(OK, status);
}

void test_nullSensor(void)
{
    uint8_t id=1;
    char name[50];
    interface_t interface=ADC;
    status_t status=SensorInit(NULL, name, strlen(name), interface, id);
    TEST_ASSERT_EQUAL(ERROR,status);
}

void test_nullName(void)
{
    uint8_t id=1;
    interface_t interface=ADC;
    sensor_t sensor;
    status_t status=SensorInit(&sensor, NULL, 0 , interface, id);
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

    status_t status=SensorInit(&sensor, name, strlen(name), 100, id);
    TEST_ASSERT_EQUAL(ERROR,status);

    sensor_t sensor1;
    status=SensorInit(&sensor1, name, strlen(name), ADC, id);
    TEST_ASSERT_EQUAL(OK,status);
    
    sensor_t sensor2;
    status=SensorInit(&sensor2, name, strlen(name), UART, id);
    TEST_ASSERT_EQUAL(OK,status);

    sensor_t sensor3;
    status=SensorInit(&sensor3, name, strlen(name), I2C, id);
    TEST_ASSERT_EQUAL(OK,status);

    sensor_t sensor4;
    status=SensorInit(&sensor4, name, strlen(name), -1, id);
    TEST_ASSERT_EQUAL(ERROR,status);
}

void test_ID_only_positive(void)
{
    char name[50];
    sensor_t sensor;
    interface_t interface=ADC;
    status_t status=SensorInit(&sensor, name, strlen(name), interface, 0);
    TEST_ASSERT_EQUAL(ERROR,status);
}

void test_proper_sensor_initialization(void)
{
    uint8_t id=1;
    char name[]="Water level sensor";
    interface_t interface=ADC;
    sensor_t sensor;
    status_t status=SensorInit(&sensor,name, strlen(name), interface, id);
    TEST_ASSERT_EQUAL(OK,status);
    TEST_ASSERT_EQUAL(ADC,sensor.interface);
    TEST_ASSERT_EQUAL(0,strncmp(sensor.name,name,strlen(name)));
    TEST_ASSERT_EQUAL(1,sensor.id);
}

void test_multiple_initialization(void)
{
    uint8_t id=1;
    char name[]="Water level sensor";
    interface_t interface=ADC;
    sensor_t sensor;
    status_t status=SensorInit(&sensor,name, strlen(name), interface, id);
    TEST_ASSERT_EQUAL(OK,status);
    
    status=SensorInit(&sensor,name, strlen(name), interface, id);
    TEST_ASSERT_EQUAL(ERROR,status);
}

void test_multiple_various_initialization(void)
{
    uint8_t id1=1;
    char name1[]="Water level sensor";
    interface_t interface1=ADC;
    sensor_t Level_sensor;
    status_t status1=SensorInit(&Level_sensor,name1, strlen(name1), interface1, id1);
    TEST_ASSERT_EQUAL(OK,status1);
    TEST_ASSERT_EQUAL(0,strncmp(Level_sensor.name,name1,strlen(name1)));
    
    uint8_t id2=2;
    char name2[]="Temperature sensor";
    interface_t interface2=UART;
    sensor_t Temp_sensor;
    status_t status2=SensorInit(&Temp_sensor,name2, strlen(name2), interface2, id2);
    TEST_ASSERT_EQUAL(OK,status2);
    TEST_ASSERT_EQUAL(0,strncmp(Temp_sensor.name,name2,strlen(name2)));

    uint8_t id3=3;
    char name3[]="Moisture level sensor";
    interface_t interface3=I2C;
    sensor_t Moist_sensor;
    status_t status3=SensorInit(&Moist_sensor,name3, strlen(name3), interface3, id3);
    TEST_ASSERT_EQUAL(OK,status3);
    TEST_ASSERT_EQUAL(0,strncmp(Moist_sensor.name,name3,strlen(name3)));
}
void test_too_long_name_initialization(void)
{
    uint8_t id=1;
    char name[]="Water level sensorrrrrrrrrrrrrrrrrrrrrrrrrrrrr48";  
    interface_t interface=ADC;
    sensor_t sensor;
    status_t status=SensorInit(&sensor,name,strlen(name), interface, id);
    TEST_ASSERT_EQUAL(OK,status);
    TEST_ASSERT_EQUAL(0,strncmp(sensor.name,name,strlen(name)));

    char name1[]="Water level sensorrrrrrrrrrrrrrrrrrrrrrrrrrrrrr49";
    sensor_t sensor1;
    status=SensorInit(&sensor1,name1,strlen(name1), interface, id);
    TEST_ASSERT_EQUAL(OK,status);
    TEST_ASSERT_EQUAL(0,strncmp(sensor1.name,name1,strlen(name1)));

    char name2[]="Water level sensorrrrrrrrrrrrrrrrrrrrrrrrrrrrrrr50";
    sensor_t sensor2;
    status=SensorInit(&sensor2,name2,strlen(name2), interface, id);
    TEST_ASSERT_EQUAL(ERROR,status);
}

void test_isManager(void)
{
    sensorManager_t manager;
    sensor_t s1, s2, s3;
    sensor_t* sensor_arr [3]={&s1, &s2, &s3};
    status_t status = SensorManagerInit(&manager, sensor_arr, 3);
    TEST_ASSERT_EQUAL(OK,status);
}


void test_NullProtection(void)
{
    sensorManager_t manager;
    sensor_t s1,s2;
    sensor_t* s3_ptr=NULL;
    sensor_t* sensor_arr [3]={&s1, &s2, s3_ptr};
    status_t status = SensorManagerInit(&manager, sensor_arr, 3);
    TEST_ASSERT_EQUAL(ERROR,status);
}

void test_sizeProtection(void)
{
    sensorManager_t manager;
    sensor_t s1,s2,s3,s4,s5,s6,s7,s8,s9,s10,s11;
    sensor_t* sensor_arr [11]={&s1,&s2,&s3,&s4,&s5,&s6,&s7,&s8,&s9,&s10,&s11};
    status_t status = SensorManagerInit(&manager, sensor_arr, 11);
    TEST_ASSERT_EQUAL(ERROR,status);

    sensorManager_t manager2;
    sensor_t s12,s13,s14;
    sensor_t* sensor_arr2 [3]={&s12,&s13,&s14};
    status = SensorManagerInit(&manager2, sensor_arr2, 0);
    TEST_ASSERT_EQUAL(ERROR,status);
    
    sensorManager_t manager3;
    sensor_t s15,s16,s17;
    sensor_t* sensor_arr3 [3]={&s15,&s16,&s17};
    status = SensorManagerInit(&manager3, sensor_arr3,3);
    TEST_ASSERT_EQUAL(OK,status);
}

void test_getReadingsFromSensor(void)
{
    sensorManager_t manager;
    sensor_t sensor_arr [10]; //zakładam, że już są zainicjalizowane? 
    status_t status = SensorManagerInit(&manager, sensor_arr, 10);
    uint8_t sensor_id = 1;
    float reading = GetValue(&manager,sensor_id);
}
