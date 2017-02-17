#include <Arduino.h>
#include "Potentiometer.h"

Potentiometer::Potentiometer(){}
Potentiometer::Potentiometer(int _pin){
  pin = _pin;
}
int Potentiometer::getValue(){
  return map(analogRead(pin),0,1024,0,100);
}
int Potentiometer::getDegrees(){
	return map(analogRead(pin),0,1024,0,360);
}
float Potentiometer::getRad(){
	int potVal = analogRead(pin);
	return potVal/(2*3.14);
}

