#include "Arduino.h"

Switch::Switch(int _pin){
	pin = _pin;
}
bool Switch::getState(){
	return digitalRead(pin);
}
