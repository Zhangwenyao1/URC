#ifndef Carousel_h
#define Carousel_h
#include "Arduino.h"
#include "Motor.h"
#include "Switch.h"
class Carousel{
  public:
    Carousel(Motor _rotate, Motor _crank, Switch _open, Switch _close, Switch _index);
    void Open();
    void Close();
    void rotate(uint16_t _index);
    void fillIndex(uint16_t _index);
    void emptyIndex(uint16_t _index);
    bool checkIndex(uint16_t _index);
  private:
    Motor rotationMotor;
    Motor crankMotor;
    Switch closedSwitch, openSwitch, indexSwitch;
    bool fullIndexes[6];
    uint16_t index;

};
#endif
