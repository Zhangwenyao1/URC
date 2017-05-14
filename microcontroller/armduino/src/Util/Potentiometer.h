#ifndef Potentiometer_h
#define Potentiometer_h
#include <Arduino.h>
#include "mathFunc.h"

class Potentiometer{
  public:
    Potentiometer(){};
    Potentiometer(int pin){
    	this->pin = pin;
    };
    int getValue(){
    	return analogRead(pin);
    };
  private:
    int pin;
};
#endif
