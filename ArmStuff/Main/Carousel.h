#ifndef Carousel_h
#define Carousel_h
#include "Arduino.h"
#include "Motor.h"
class Winch{
  public:
    Carousel(Motor _rotationMotor, Motor _crankMotor, Switch _closedSwitch, Switch _openSwitch, Switch _indexSwtich);
    void open();
    void close();
    void rotate(int _index);
    void fillIndex(int _index);
    bool checkIndex(int _index);
  private:
    Motor rotationMotor, crankMotor;
    Switch closeSwitch, openSwitch, indexSwitch;
    bool fullIndexes[6];
    int index;

};
#endif
