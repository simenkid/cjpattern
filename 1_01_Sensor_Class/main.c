#include "Sensor.h"
#include <stdlib.h>
#include <stdio.h>

int main(int argc, char* argv[])
{

    Sensor * p_Sensor0, * p_Sensor1;

    p_Sensor0 = Sensor_Create();
    p_Sensor1 = Sensor_Create();

    p_Sensor0->value = 99;
    p_Sensor1->value = -1;

    printf("The current value of Sensor 0 is %d\n", Sensor_getValue(p_Sensor0));
    printf("The current value of Sensor 1 is %d\n", Sensor_getValue(p_Sensor1));

    Sensor_Destroy(p_Sensor1);
    Sensor_Destroy(p_Sensor1);

    return 0;
}
