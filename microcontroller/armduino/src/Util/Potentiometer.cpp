#include <Arduino.h>
#include "Potentiometer.h"
#include "mathFunc.h"

mathFunc math = mathFunc();
Potentiometer::Potentiometer(){}
Potentiometer::Potentiometer(int _pin){
  pin = _pin;
}
int Potentiometer::getValue(){
	return analogRead(pin);
}
int Potentiometer::getDegrees(){
	return map(getValue(),0,1024,0,360);
}
float Potentiometer::getRad(){
	return math.degToRad(getDegrees());
}

