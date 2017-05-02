#ifndef Motor_h
#define Motor_h
#include "Arduino.h"
#include <Servo.h>
#include "MotorController.h"
class Motor{
  public:
    Motor(int pin, bool type);
    Motor();
    void doPWM(int input);
  private:
    MotorController driver;
};
#endif
