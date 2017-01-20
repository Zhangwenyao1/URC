#ifndef Arm_h
#define Arm_h
#include "Arduino.h"
#include "Motor.h"
#include "Potentieometer.h"
#include "Encoder.h"

class Arm{
  public:
    Arm(Motor[] _joints,Potentiometer[] _pots; Encoder[] _encoder);
  private:
    Motor[] joints;
    Potentiometer[] pots;
    Encoder[] encoders;

};
#endif
