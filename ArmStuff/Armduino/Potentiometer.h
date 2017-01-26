#ifndef Potentiometer_h
#define Potentiometer_h
#include "Arduino.h"
class Potentiometer{
  public:
    Potentiometer(int _pin);
    uint16_t getValue();
  private:
    int pin;
};
#endif
