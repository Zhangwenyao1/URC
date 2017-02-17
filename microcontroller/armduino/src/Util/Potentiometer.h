#ifndef Potentiometer_h
#define Potentiometer_h
#include "Arduino.h"
class Potentiometer{
  public:
    Potentiometer();
    Potentiometer(int _pin);
    int getValue();
    int getDegrees();
    float getRad();
  private:
    int pin;
};
#endif
