#ifndef Winch_h
#define Winch_h
#include <Arduino.h>
#include "Motor.h"
class Winch{
  public:
    Winch(Motor winchMotor);
    void doMotor(int direction);
  private:
    Motor winchMotor;
    int drive;
};
#endif
