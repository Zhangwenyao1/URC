#include "Arduino.h"
#include "Switch.h"
Switch::Switch(){}

Switch::Switch(int _pin){
	pin = _pin;
  pinMode(pin, INPUT);
}
bool Switch::getState(){
	return digitalRead(pin);
}
