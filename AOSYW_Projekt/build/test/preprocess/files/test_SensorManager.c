#include "src/SensorManager.h"
#include "C:/Users/kubas/scoop/persist/ruby30/gems/gems/ceedling-0.31.1/vendor/unity/src/unity.h"










void setUp(void)

{

}



void tearDown(void)

{

}



void test_SensorManager_NeedToImplement(void)

{

    UnityIgnore( (("Need to Implement SensorManager")), (UNITY_UINT)(18));

}



void test_isThereSensorInit(void)

{

    SensorInit();

}

void test_doesSensorInitReturnSensor(void)

{

    char name[] = "Level measurement ultrasonic sensor";

    enum sensor_interface interface = UART;

    uint8_t id = 1;



    struct sensor *result = SensorInit(name, interface, id);



    UnityAssertEqualString((const char*)((name)), (const char*)((result->name)), (

   ((void *)0)

   ), (UNITY_UINT)(48));

    TEST_ASSERT_EQUAL_UINT8_T((uint8_t)interface, (uint8_t)result->interface);

    TEST_ASSERT_EQUAL_UINT8_T(id, result->id);

}
