#ifndef Motor_h
#define Motor_h
#include "Arduino.h"
#include <Servo.h>
#include "MotorController.h"

class Motor{
  public:
	Motor();
    Motor(int pin, bool type);
    void doPWM(int input);
  private:
    MotorController driver;
};
#endif
