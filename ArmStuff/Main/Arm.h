#ifndef Arm_h
#define Arm_h
#include "Arduino.h"
#include "Motor.h"
#include "Potentieometer.h"
#include "Encoder.h"

class Arm{
  public:
    Arm();
    int[] getPosition(Potentiometer[] _pots; Encoder[] _encoder);
    void setMotorSpeed(Motor _motor, int _speed);    
};
#endif
