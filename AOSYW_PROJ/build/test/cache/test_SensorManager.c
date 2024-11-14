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

    UnityIgnore( (("Need to Implement SensorManager")), (UNITY_UINT)(14));

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

    UnityAssertEqualNumber((UNITY_INT)(UNITY_UINT8 )(((uint8_t)status)), (UNITY_INT)(UNITY_UINT8 )(((uint8_t)status2)), (

   ((void *)0)

   ), (UNITY_UINT)(37), UNITY_DISPLAY_STYLE_UINT8);

}
