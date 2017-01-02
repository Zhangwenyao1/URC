#ifndef Potentiometer_h
#define Potentiometer_h
#include "Arduino.h"
class Potentiometer{
  public:
    Potentiometer(int _pin);
    int getValue();
  private:
    int pin;
};
#endif
