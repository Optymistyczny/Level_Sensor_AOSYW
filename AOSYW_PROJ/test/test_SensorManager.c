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


void test_issensorInit(void)
{
    uint8_t id=1;
    char name[]="Water level sensor";
    sensor_type_t sensor_type=SEN0311;
    status_t status=sensorInit(name,sensor_type,id);
    TEST_ASSERT_EQUAL(OK,status);
}

void test_Empty_or_Bad_Name(void)
{
    //ASCII covers range from 0 to 127
    status_t status;

    char name [127][2];
    for (uint8_t i = 1; i <= 127; i++) {
        name[i - 1][0] = (char)i;  // Wstaw znak ASCII
        name[i - 1][1] = '\0';     // Dodaj terminator '\0', aby był to prawidłowy string
    }
    
    for(uint8_t i=1; i<=127; i++)
    {
        status=sensorInit(name[i-1],SEN0311,1); 
        TEST_ASSERT_EQUAL(OK,status);
    }

    char name1 []={(char)-1};
    status=sensorInit(name1,SEN0311,1); // Out of range
    TEST_ASSERT_EQUAL(ERR,status);

    char name2 []={(char)0};
    status=sensorInit(name2,SEN0311,1); // ASCII '\0'
    TEST_ASSERT_EQUAL(ERR,status);

    char name3 []={(char)128};
    status=sensorInit(name3,SEN0311,1); // Out of range
    TEST_ASSERT_EQUAL(ERR,status);
}

void test_BadSensorType(void)
{
    status_t status=sensorInit("Level Sensor", -1, 1);
    TEST_ASSERT_EQUAL(ERR,status);

    status=sensorInit("Level Sensor", SEN0311, 1);
    TEST_ASSERT_EQUAL(OK,status);
    
    status=sensorInit("Level Sensor", DS18B20, 1);
    TEST_ASSERT_EQUAL(OK,status);

    status=sensorInit("Level Sensor", SENSORS_COUNT, 1);
    TEST_ASSERT_EQUAL(ERR,status);
}

void test_IDs_and_Number_of_sensors(void)
{
    status_t status;
 
    for(uint8_t i=SENSORS;i>=1;i--)
    {
        status=sensorInit("Level Sensor", SEN0311, i);
        TEST_ASSERT_EQUAL(OK,status);
    }    
    status=sensorInit("Level Sensor", SEN0311, SENSORS+1);
    TEST_ASSERT_EQUAL(ERR,status);
    status=sensorInit("Level Sensor", SEN0311, 0);
    TEST_ASSERT_EQUAL(ERR,status);
}

void test_proper_sensor_initialization(void)
{
    uint8_t id=1;
    char name[]="Water level sensor";
    char name_buff[MAX_NAME_LEN];
    sensor_type_t sensor_type = SEN0311;
    sensor_type_t sensor_type2;
    status_t status=sensorInit(name, sensor_type, id);
    TEST_ASSERT_EQUAL(OK,status);
    status=sensorGetSensorType(id, &sensor_type2);
    TEST_ASSERT_EQUAL(OK,status);
    TEST_ASSERT_EQUAL(SEN0311,sensor_type2);

    status=sensorGetName(id, name_buff);
    TEST_ASSERT_EQUAL(OK,status);
    TEST_ASSERT_EQUAL(0,strcmp(name_buff,name));
}

void test_getReadingsFromSensor(void)
{
    status_t status = sensorInit("Water Level Sensor",SEN0311,1);
    TEST_ASSERT_EQUAL(OK,status);
    float reading = getFloatValue(1);
    TEST_ASSERT_EQUAL_FLOAT(1.0,reading);

    status = sensorInit("Water Level Sensor",DS18B20,2);
    TEST_ASSERT_EQUAL(OK,status);
    reading = getFloatValue(1);
    TEST_ASSERT_EQUAL_FLOAT(1.0,reading);
}