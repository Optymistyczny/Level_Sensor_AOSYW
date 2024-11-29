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
    status_t status=SensorInit(name,interface,id);
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
        status=SensorInit(name[i-1],ADC,1); 
        TEST_ASSERT_EQUAL(OK,status);
    }

    char name1 []={(char)-1};
    status=SensorInit(name1,ADC,1); // Out of range
    TEST_ASSERT_EQUAL(ERROR,status);

    char name2 []={(char)0};
    status=SensorInit(name2,ADC,1); // ASCII '\0'
    TEST_ASSERT_EQUAL(ERROR,status);

    char name3 []={(char)128};
    status=SensorInit(name3,ADC,1); // Out of range
    TEST_ASSERT_EQUAL(ERROR,status);
}

void test_BadInterface(void)
{
    status_t status=SensorInit("Level Sensor", -1, 1);
    TEST_ASSERT_EQUAL(ERROR,status);

    status=SensorInit("Level Sensor", ADC, 1);
    TEST_ASSERT_EQUAL(OK,status);
    
    status=SensorInit("Level Sensor", UART, 1);
    TEST_ASSERT_EQUAL(OK,status);

    status=SensorInit("Level Sensor", I2C, 1);
    TEST_ASSERT_EQUAL(OK,status);

    status=SensorInit("Level Sensor", INTERFACES_COUNT, 1);
    TEST_ASSERT_EQUAL(ERROR,status);
}

void test_IDs_and_Number_of_sensors(void)
{
    status_t status;
 
    for(uint8_t i=SENSORS;i>=1;i--)
    {
        status=SensorInit("Level Sensor", ADC, i);
        TEST_ASSERT_EQUAL(OK,status);
    }    
    status=SensorInit("Level Sensor", ADC, SENSORS+1);
    TEST_ASSERT_EQUAL(ERROR,status);
    status=SensorInit("Level Sensor", ADC, 0);
    TEST_ASSERT_EQUAL(ERROR,status);
}

void test_proper_sensor_initialization(void)
{
    uint8_t id=1;
    char name[]="Water level sensor";
    char name_buff[MAX_NAME_LEN];
    interface_t interface = ADC;
    interface_t interface2;
    status_t status=SensorInit(name, interface, id);
    TEST_ASSERT_EQUAL(OK,status);
    status=sensorGetInterface(id, &interface2);
    TEST_ASSERT_EQUAL(OK,status);
    TEST_ASSERT_EQUAL(ADC,interface2);

    status=sensorGetName(id, name_buff);
    TEST_ASSERT_EQUAL(OK,status);
    TEST_ASSERT_EQUAL(0,strcmp(name_buff,name));
}

void test_getReadingsFromSensor(void)
{
    status_t status = SensorInit("Water Level Sensor",ADC,1);
    float reading = GetFloatValue(1);
    TEST_ASSERT_EQUAL_FLOAT(123.123,reading);
}