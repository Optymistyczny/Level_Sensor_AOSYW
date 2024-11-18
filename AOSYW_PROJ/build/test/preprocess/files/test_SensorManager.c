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

    char name[]="Water level sensor";

    interface_t interface=ADC;

    sensor_t sensor;

    status_t status=SensorInit(&sensor, name, strlen(name), interface,id);

    UnityAssertEqualNumber((UNITY_INT)((OK)), (UNITY_INT)((status)), (

   ((void *)0)

   ), (UNITY_UINT)(19), UNITY_DISPLAY_STYLE_INT);

}



void test_ReturnStatusWhenGoodArguments(void)

{

    uint8_t id=1;

    char name[50];

    interface_t interface=ADC;

    sensor_t sensor;



    status_t status;

    status=SensorInit(&sensor, name, strlen(name), interface,id);

    UnityAssertEqualNumber((UNITY_INT)((OK)), (UNITY_INT)((status)), (

   ((void *)0)

   ), (UNITY_UINT)(31), UNITY_DISPLAY_STYLE_INT);

}



void test_nullSensor(void)

{

    uint8_t id=1;

    char name[50];

    interface_t interface=ADC;

    status_t status=SensorInit(

                              ((void *)0)

                                  , name, strlen(name), interface, id);

    UnityAssertEqualNumber((UNITY_INT)((ERROR)), (UNITY_INT)((status)), (

   ((void *)0)

   ), (UNITY_UINT)(40), UNITY_DISPLAY_STYLE_INT);

}



void test_nullName(void)

{

    uint8_t id=1;

    interface_t interface=ADC;

    sensor_t sensor;

    status_t status=SensorInit(&sensor, 

                                       ((void *)0)

                                           , 0 , interface, id);

    UnityAssertEqualNumber((UNITY_INT)((ERROR)), (UNITY_INT)((status)), (

   ((void *)0)

   ), (UNITY_UINT)(49), UNITY_DISPLAY_STYLE_INT);

}











void test_BadInterface(void)

{

    uint8_t id=1;

    char name[50];

    sensor_t sensor;



    status_t status=SensorInit(&sensor, name, strlen(name), 100, id);

    UnityAssertEqualNumber((UNITY_INT)((ERROR)), (UNITY_INT)((status)), (

   ((void *)0)

   ), (UNITY_UINT)(63), UNITY_DISPLAY_STYLE_INT);



    sensor_t sensor1;

    status=SensorInit(&sensor1, name, strlen(name), ADC, id);

    UnityAssertEqualNumber((UNITY_INT)((OK)), (UNITY_INT)((status)), (

   ((void *)0)

   ), (UNITY_UINT)(67), UNITY_DISPLAY_STYLE_INT);



    sensor_t sensor2;

    status=SensorInit(&sensor2, name, strlen(name), UART, id);

    UnityAssertEqualNumber((UNITY_INT)((OK)), (UNITY_INT)((status)), (

   ((void *)0)

   ), (UNITY_UINT)(71), UNITY_DISPLAY_STYLE_INT);



    sensor_t sensor3;

    status=SensorInit(&sensor3, name, strlen(name), I2C, id);

    UnityAssertEqualNumber((UNITY_INT)((OK)), (UNITY_INT)((status)), (

   ((void *)0)

   ), (UNITY_UINT)(75), UNITY_DISPLAY_STYLE_INT);



    sensor_t sensor4;

    status=SensorInit(&sensor4, name, strlen(name), -1, id);

    UnityAssertEqualNumber((UNITY_INT)((ERROR)), (UNITY_INT)((status)), (

   ((void *)0)

   ), (UNITY_UINT)(79), UNITY_DISPLAY_STYLE_INT);

}



void test_ID_only_positive(void)

{

    char name[50];

    sensor_t sensor;

    interface_t interface=ADC;

    status_t status=SensorInit(&sensor, name, strlen(name), interface, 0);

    UnityAssertEqualNumber((UNITY_INT)((ERROR)), (UNITY_INT)((status)), (

   ((void *)0)

   ), (UNITY_UINT)(88), UNITY_DISPLAY_STYLE_INT);

}



void test_proper_sensor_initialization(void)

{

    uint8_t id=1;

    char name[]="Water level sensor";

    interface_t interface=ADC;

    sensor_t sensor;

    status_t status=SensorInit(&sensor,name, strlen(name), interface, id);

    UnityAssertEqualNumber((UNITY_INT)((OK)), (UNITY_INT)((status)), (

   ((void *)0)

   ), (UNITY_UINT)(98), UNITY_DISPLAY_STYLE_INT);

    UnityAssertEqualNumber((UNITY_INT)((ADC)), (UNITY_INT)((sensor.interface)), (

   ((void *)0)

   ), (UNITY_UINT)(99), UNITY_DISPLAY_STYLE_INT);

    UnityAssertEqualNumber((UNITY_INT)((0)), (UNITY_INT)((strncmp(sensor.name,name,strlen(name)))), (

   ((void *)0)

   ), (UNITY_UINT)(100), UNITY_DISPLAY_STYLE_INT);

    UnityAssertEqualNumber((UNITY_INT)((1)), (UNITY_INT)((sensor.id)), (

   ((void *)0)

   ), (UNITY_UINT)(101), UNITY_DISPLAY_STYLE_INT);

}



void test_multiple_initialization(void)

{

    uint8_t id=1;

    char name[]="Water level sensor";

    interface_t interface=ADC;

    sensor_t sensor;

    status_t status=SensorInit(&sensor,name, strlen(name), interface, id);

    UnityAssertEqualNumber((UNITY_INT)((OK)), (UNITY_INT)((status)), (

   ((void *)0)

   ), (UNITY_UINT)(111), UNITY_DISPLAY_STYLE_INT);



    status=SensorInit(&sensor,name, strlen(name), interface, id);

    UnityAssertEqualNumber((UNITY_INT)((ERROR)), (UNITY_INT)((status)), (

   ((void *)0)

   ), (UNITY_UINT)(114), UNITY_DISPLAY_STYLE_INT);

}



void test_multiple_various_initialization(void)

{

    uint8_t id1=1;

    char name1[]="Water level sensor";

    interface_t interface1=ADC;

    sensor_t Level_sensor;

    status_t status1=SensorInit(&Level_sensor,name1, strlen(name1), interface1, id1);

    UnityAssertEqualNumber((UNITY_INT)((OK)), (UNITY_INT)((status1)), (

   ((void *)0)

   ), (UNITY_UINT)(124), UNITY_DISPLAY_STYLE_INT);

    UnityAssertEqualNumber((UNITY_INT)((0)), (UNITY_INT)((strncmp(Level_sensor.name,name1,strlen(name1)))), (

   ((void *)0)

   ), (UNITY_UINT)(125), UNITY_DISPLAY_STYLE_INT);



    uint8_t id2=2;

    char name2[]="Temperature sensor";

    interface_t interface2=UART;

    sensor_t Temp_sensor;

    status_t status2=SensorInit(&Temp_sensor,name2, strlen(name2), interface2, id2);

    UnityAssertEqualNumber((UNITY_INT)((OK)), (UNITY_INT)((status2)), (

   ((void *)0)

   ), (UNITY_UINT)(132), UNITY_DISPLAY_STYLE_INT);

    UnityAssertEqualNumber((UNITY_INT)((0)), (UNITY_INT)((strncmp(Temp_sensor.name,name2,strlen(name2)))), (

   ((void *)0)

   ), (UNITY_UINT)(133), UNITY_DISPLAY_STYLE_INT);



    uint8_t id3=3;

    char name3[]="Moisture level sensor";

    interface_t interface3=I2C;

    sensor_t Moist_sensor;

    status_t status3=SensorInit(&Moist_sensor,name3, strlen(name3), interface3, id3);

    UnityAssertEqualNumber((UNITY_INT)((OK)), (UNITY_INT)((status3)), (

   ((void *)0)

   ), (UNITY_UINT)(140), UNITY_DISPLAY_STYLE_INT);

    UnityAssertEqualNumber((UNITY_INT)((0)), (UNITY_INT)((strncmp(Moist_sensor.name,name3,strlen(name3)))), (

   ((void *)0)

   ), (UNITY_UINT)(141), UNITY_DISPLAY_STYLE_INT);

}

void test_too_long_name_initialization(void)

{

    uint8_t id=1;

    char name[]="Water level sensorrrrrrrrrrrrrrrrrrrrrrrrrrrrr48";

    interface_t interface=ADC;

    sensor_t sensor;

    status_t status=SensorInit(&sensor,name,strlen(name), interface, id);

    UnityAssertEqualNumber((UNITY_INT)((OK)), (UNITY_INT)((status)), (

   ((void *)0)

   ), (UNITY_UINT)(150), UNITY_DISPLAY_STYLE_INT);

    UnityAssertEqualNumber((UNITY_INT)((0)), (UNITY_INT)((strncmp(sensor.name,name,strlen(name)))), (

   ((void *)0)

   ), (UNITY_UINT)(151), UNITY_DISPLAY_STYLE_INT);



    char name1[]="Water level sensorrrrrrrrrrrrrrrrrrrrrrrrrrrrrr49";

    sensor_t sensor1;

    status=SensorInit(&sensor1,name1,strlen(name1), interface, id);

    UnityAssertEqualNumber((UNITY_INT)((OK)), (UNITY_INT)((status)), (

   ((void *)0)

   ), (UNITY_UINT)(156), UNITY_DISPLAY_STYLE_INT);

    UnityAssertEqualNumber((UNITY_INT)((0)), (UNITY_INT)((strncmp(sensor1.name,name1,strlen(name1)))), (

   ((void *)0)

   ), (UNITY_UINT)(157), UNITY_DISPLAY_STYLE_INT);



    char name2[]="Water level sensorrrrrrrrrrrrrrrrrrrrrrrrrrrrrrr50";

    sensor_t sensor2;

    status=SensorInit(&sensor2,name2,strlen(name2), interface, id);

    UnityAssertEqualNumber((UNITY_INT)((ERROR)), (UNITY_INT)((status)), (

   ((void *)0)

   ), (UNITY_UINT)(162), UNITY_DISPLAY_STYLE_INT);

}



void test_isManager(void)

{

    sensorManager_t manager;

    sensor_t sensor_arr [10];

    status_t status = SensorManagerInit(&manager, sensor_arr, 10);

    UnityAssertEqualNumber((UNITY_INT)((OK)), (UNITY_INT)((status)), (

   ((void *)0)

   ), (UNITY_UINT)(170), UNITY_DISPLAY_STYLE_INT);

}
