#ifndef Motor_h
#define Motor_h
#include "Arduino.h"
class Motor{
  public:
    Motor(int _pin, int _dirPin);
    void doMotors(int _drive);
    void doMotorsPWM(double input);
  private:
    int pin;
    int dirPin;
};
#endif
