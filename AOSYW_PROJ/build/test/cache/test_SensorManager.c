#include "src/SensorManager.h"
#include "C:/Users/kubas/scoop/persist/ruby30/gems/gems/ceedling-0.31.1/vendor/unity/src/unity.h"


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

    UnityAssertEqualNumber((UNITY_INT)(UNITY_UINT8 )(((uint8_t)status)), (UNITY_INT)(UNITY_UINT8 )(((uint8_t)status2)), (

   ((void *)0)

   ), (UNITY_UINT)(32), UNITY_DISPLAY_STYLE_UINT8);

}



void test_uninitializedArguments(void)

{

    uint8_t id;

    char name[50];

    interface_t interface;

    sensor_t* sensor;

    SensorInit(sensor, name, interface, id);



    UnityAssertEqualNumber((UNITY_INT)((0)), (UNITY_INT)((strcmp(sensor->name,"NULL"))), (

   ((void *)0)

   ), (UNITY_UINT)(43), UNITY_DISPLAY_STYLE_INT);

    UnityAssertEqualNumber((UNITY_INT)(((uint8_t)NA)), (UNITY_INT)((sensor->interface)), (

   ((void *)0)

   ), (UNITY_UINT)(44), UNITY_DISPLAY_STYLE_INT);

    UnityAssertEqualNumber((UNITY_INT)((0)), (UNITY_INT)((sensor->id)), (

   ((void *)0)

   ), (UNITY_UINT)(45), UNITY_DISPLAY_STYLE_INT);

}
