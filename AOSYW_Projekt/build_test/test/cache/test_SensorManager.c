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

    UnityIgnore( (("Need to Implement SensorManager")), (UNITY_UINT)(20));

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

   ), (UNITY_UINT)(50));



    UnityAssertEqualNumber((UNITY_INT)(UNITY_UINT8 )(((uint8_t)interface)), (UNITY_INT)(UNITY_UINT8 )(((uint8_t)result->interface)), (

   ((void *)0)

   ), (UNITY_UINT)(52), UNITY_DISPLAY_STYLE_UINT8);



    UnityAssertEqualNumber((UNITY_INT)(UNITY_UINT8 )((id)), (UNITY_INT)(UNITY_UINT8 )((result->id)), (

   ((void *)0)

   ), (UNITY_UINT)(54), UNITY_DISPLAY_STYLE_UINT8);

}
