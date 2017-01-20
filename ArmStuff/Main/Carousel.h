#ifndef Carousel_h
#define Carousel_h
#include "Arduino.h"
#include "Motor.h"
class Winch{
  public:
    Carousel(Motor[] _motor,);
    void open();
    void close();
  private:
    Motor[] motors;
};
#endif
