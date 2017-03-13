#include "Arduino.h"
#include "Switch.h"
Switch::Switch(){}

Switch::Switch(int pin){
	this->pin = pin;
  pinMode(pin, INPUT);
}
bool Switch::getState(){
	return digitalRead(pin);
}
