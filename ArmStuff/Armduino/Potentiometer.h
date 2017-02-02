#ifndef Potentiometer_h
#define Potentiometer_h
#include "Arduino.h"
class Potentiometer{
  public:
    Potentiometer();
    Potentiometer(int _pin);
    uint16_t getValue();
  private:
    int pin;
};
#endif
