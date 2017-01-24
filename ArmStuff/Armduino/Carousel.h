#ifndef Carousel_h
#define Carousel_h
#include "Arduino.h"
#include "Motor.h"
#include "Switch.h"
class Carousel{
  public:
    Carousel(int m1, int m2, int dir1, int dir2, int _pin1, int _pin2, int _pin3);
    void Open();
    void Close();
    void rotate(int _index);
    void fillIndex(int _index);
    void emptyIndex(int _index);
    bool checkIndex(int _index);
  private:
    Motor rotationMotor;
    Motor crankMotor;
    Switch closedSwitch, openSwitch, indexSwitch;
    bool fullIndexes[6];
    int index;

};
#endif
