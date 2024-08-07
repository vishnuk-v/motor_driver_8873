#include "main.h"

void test_motor()
{
    pwm_ctrl();

}

void setup(){
    Serial.begin(115200);
    UNITY_BEGIN();
    RUN_TEST(test_motor);
    UNITY_END();

}

void loop(){

}