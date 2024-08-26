#include <Arduino.h>
#define IN1         12                        //  enable to OUT1 
#define IN2         13                        //  enable to OUT2
#define FAULT       38                        //  fault indication pin, this pin is pulled low to indicate a fault has occured
#define PWM_CHANNEL 0                         //  selected channel 0
const int frequency   = 5000;                 //  pwm frequency
const int PWM_channel = 0;                    //  pwm channel, channel 0 
const int resoultion  = 12;                   //  12 bit resolution
const int slowSpeed   = 1365;                 //  25% duty cycle
const int mediumSpeed = 2730;                 //  50% duty cycle
const int fastSpeed   = 4096;                 //  100% duty cycle

void setup(){
  // Serial communication begin
  Serial.begin(115200);
  pinMode(IN1,OUTPUT);                         //  to enable forward direction 
  pinMode(IN2,OUTPUT);                         //  to enable reverse direction
  pinMode(FAULT,OPEN_DRAIN);                  //  to check for fault, if this pin is low then fault is there
  // PWM enable 

  ledcSetup(PWM_CHANNEL, frequency, resoultion);
  ledcAttachPin(IN1, PWM_CHANNEL);
  ledcWrite(IN1, 0);                          // initially motor is off 
  ledcAttachPin(IN2, PWM_CHANNEL);
  ledcWrite(IN2, 0);  

}
void loop(){
   
  if (Serial.available() > 0)
  {
    
   if(digitalRead(FAULT)!= 0){                                     // to check whether the fault pin is high or low is low means fault is there
    String input_from_user = Serial.readString();
    if (input_from_user.equals("slow"))
    {
      ledcWrite(IN1, slowSpeed);               // to the speed to LOW 
      ledcWrite(IN2,0);
      Serial.println("Running at slow speed");
      delay(1000);
    }
    else if (input_from_user.equals("medium"))
    {
      ledcWrite(IN1, mediumSpeed);            // to set the speed to MEDIUM
      ledcWrite(IN2, 0);
      Serial.println("Running at medium speed");
      delay(1000);
    }
    else if (input_from_user.equals("fast"))
    {
      ledcWrite(IN1, fastSpeed);              // to set the speed to HIGH
      ledcWrite(IN2,0);
      Serial.println("Running at fast speed");
      delay(1000);

    }
    // else if (input_from_user.equals("stop"))
    // {
    //   ledcWrite(PWM_CHANNEL, 0);
    //   Serial.println("STOP");
    //   delay(1000);
    // }
    else if (input_from_user.equals("pause"))         // to pause the motor operation 
    {
      ledcWrite(IN1,0);
      Serial.println("PAUSE");
      delay(1000);
    }

    else 
    {
      Serial.println("Enter valid input");
    }
  }


}
}