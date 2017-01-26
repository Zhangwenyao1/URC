#ifndef Motor_h
#define Motor_h
#include "Arduino.h"
#include "ros.h";
#include <std_msgs/UInt16.h>
#include <std_msgs/Float32.h>
class Motor{
  public:
    Motor(int _pin, int _dirPin);
    Motor();
    void doMotor(std_msgs::UInt16 _drive);
    void doMotorsPWM(std_msgs::Float32 input);
  private:
    int pin;
    int dirPin;
};
#endif
