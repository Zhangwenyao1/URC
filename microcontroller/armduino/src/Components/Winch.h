#ifndef Winch_h
#define Winch_h
#include <Arduino.h>
#include "../Util/Motor.h"
class Winch{
  public:
    Winch(Motor winchMotor){
    	this->winchMotor = winchMotor;
    };
    void doMotor(int direction){
    	winchMotor.doPWM(direction);
    }
  private:
    Motor winchMotor;
};
#endif
