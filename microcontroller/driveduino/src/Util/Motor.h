#ifndef Motor_h
#define Motor_h
#include "Arduino.h"
#include <Servo.h>
class Motor{
  public:
    Motor(int pin);
    Motor();
    void doPWM(float vel);
  private:
    int pin;
    Servo motor;
};
#endif
