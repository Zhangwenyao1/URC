#ifndef Winch_h
#define Winch_h
#include "Arduino.h"
#include "Motor.h"
class Winch{
  public:
    Winch(Motor _motor);
    void doMotor(bool _drive);
  private:
    Motor motor;
};
#endif
