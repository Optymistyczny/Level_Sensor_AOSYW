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

    uint8_t id=1;

    char name[50];

    interface_t interface=ADC;

    sensor_t* sensor;

    SensorInit(sensor, name, interface,id);

}



void test_ReturnStatusWhenGoodArguments(void)

{

    uint8_t id=1;

    char name[50];

    interface_t interface=ADC;

    sensor_t* sensor;



    status_t status;

    status=SensorInit(sensor, name, interface,id);

    UnityAssertEqualNumber((UNITY_INT)(UNITY_UINT8 )((OK)), (UNITY_INT)(UNITY_UINT8 )((status)), (

   ((void *)0)

   ), (UNITY_UINT)(30), UNITY_DISPLAY_STYLE_UINT8);

}



void test_nullSensor(void)

{

    uint8_t id=1;

    char name[50];

    interface_t interface=ADC;

    status_t status=SensorInit(

                              ((void *)0)

                                  , name, interface, id);

    UnityAssertEqualNumber((UNITY_INT)((ERROR)), (UNITY_INT)((status)), (

   ((void *)0)

   ), (UNITY_UINT)(39), UNITY_DISPLAY_STYLE_INT);

}



void test_nullName(void)

{

    uint8_t id=1;

    interface_t interface=ADC;

    sensor_t* sensor;

    status_t status=SensorInit(sensor, 

                                      ((void *)0)

                                          , interface, id);

    UnityAssertEqualNumber((UNITY_INT)((ERROR)), (UNITY_INT)((status)), (

   ((void *)0)

   ), (UNITY_UINT)(48), UNITY_DISPLAY_STYLE_INT);

}











void test_BadInterface(void)

{

    uint8_t id=1;

    char name[50];

    sensor_t* sensor;



    status_t status=SensorInit(sensor, name, 100, id);

    UnityAssertEqualNumber((UNITY_INT)((ERROR)), (UNITY_INT)((status)), (

   ((void *)0)

   ), (UNITY_UINT)(62), UNITY_DISPLAY_STYLE_INT);



    status=SensorInit(sensor, name, ADC, id);

    UnityAssertEqualNumber((UNITY_INT)((OK)), (UNITY_INT)((status)), (

   ((void *)0)

   ), (UNITY_UINT)(65), UNITY_DISPLAY_STYLE_INT);



    status=SensorInit(sensor, name, UART, id);

    UnityAssertEqualNumber((UNITY_INT)((OK)), (UNITY_INT)((status)), (

   ((void *)0)

   ), (UNITY_UINT)(68), UNITY_DISPLAY_STYLE_INT);



    status=SensorInit(sensor, name, I2C, id);

    UnityAssertEqualNumber((UNITY_INT)((OK)), (UNITY_INT)((status)), (

   ((void *)0)

   ), (UNITY_UINT)(71), UNITY_DISPLAY_STYLE_INT);



    status=SensorInit(sensor, name, -1, id);

    UnityAssertEqualNumber((UNITY_INT)((ERROR)), (UNITY_INT)((status)), (

   ((void *)0)

   ), (UNITY_UINT)(74), UNITY_DISPLAY_STYLE_INT);

}



void test_ID_only_positive(void)

{

    char name[50];

    sensor_t* sensor;

    interface_t interface=ADC;

    status_t status=SensorInit(sensor, name, interface, 0);

    UnityAssertEqualNumber((UNITY_INT)((ERROR)), (UNITY_INT)((status)), (

   ((void *)0)

   ), (UNITY_UINT)(83), UNITY_DISPLAY_STYLE_INT);

}
