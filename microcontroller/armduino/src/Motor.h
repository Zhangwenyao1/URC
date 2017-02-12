#ifndef Motor_h
#define Motor_h
#include "Arduino.h"
#include <Servo.h>
#include <Stepper.h>
#include "ros.h";
#include <std_msgs/Int16.h>
#include <std_msgs/UInt16.h>
#include <std_msgs/Float32.h>
class Motor{
  public:
    Motor(int _pin, int _dirPin);
    Motor(int _pin);
    Motor(Stepper _Stepper);
    Motor();
    void doMotor(int _drive);
    void doStepper(int16_t _input);
    void doPWM(float _input);
  private:
    int pin;
    int dirPin;
    Servo servo;
    Stepper stepper = Stepper(0,0,0);
};
#endif
