#ifndef Motor_h
#define Motor_h
#include "Arduino.h"
#include <Servo.h>
#include <Stepper.h>

class Motor{
  public:
    Motor(int _pin);
    Motor(Stepper _Stepper);
    Motor();
    void doMotor(int _drive);
    void doStepper(int _input);
    void doPWM(float _input);
  private:
    int pin;
    Servo servo;
    Stepper stepper = Stepper(0,0,0);

};
#endif
