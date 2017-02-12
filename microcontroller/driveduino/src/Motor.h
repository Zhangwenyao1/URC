#ifndef Motor_h
#define Motor_h
#include "Arduino.h"
#include <Servo.h>
#include "ros.h";
#include <std_msgs/UInt16.h>
#include <std_msgs/Float32.h>
class Motor{
  public:
    Motor(int _pin, int _dirPin);
    Motor(int _pin);
    Motor();
    void doMotor(int _drive);
    void doMotorsPWM(std_msgs::Float32 _input);
  private:
    int pin;
    int dirPin;
    Servo motor;
};
#endif
