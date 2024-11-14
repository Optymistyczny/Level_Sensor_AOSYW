#ifndef TEST
#define TEST
#endif


#ifdef TEST

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

void test_isThereSensorInit(void)
{
    SensorInit();
}

/**
 * Jakie mogą być funkcjonalności?
 * np.:
 * - rejestracja czujnika
 * - nakaz identyfikacji czujnika
 * - odebranie danych z czujnika
*/


/**
 * Najpierw jednak sprawdzę jak działa funkcja SensorInit()
 * Zakładam, że będzie zwracała wskaźnik do jakiegoś sensora.
 * Początkowo test nie przejdzie, bo funkcja jest voidem.
*/

/**
 * Test napisany, ale nie przechodzi, więc jesteśmy w fazie RED...
 */
void test_doesSensorInitReturnSensor(void)
{
    char name[] =  "Level measurement ultrasonic sensor";
    enum sensor_interface interface = UART;
    uint8_t id = 1;

    struct sensor *result = SensorInit(name, interface, id);

    TEST_ASSERT_EQUAL_STRING(name, result->name);

    TEST_ASSERT_EQUAL_UINT8((uint8_t)interface, (uint8_t)result->interface);

    TEST_ASSERT_EQUAL_UINT8(id, result->id);
}

#endif // TEST
