#ifndef Winch_h
#define Winch_h
#include "Arduino.h"
#include "Motor.h"
class Winch{
  public:
    Winch(int m1, int dir1);
    void doMotor(bool _drive);
  private:
    Motor motor;
};
#endif
