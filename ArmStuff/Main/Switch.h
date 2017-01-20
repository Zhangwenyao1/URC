#ifndef Arm_h
#define Arm_h
#include "Arduino.h"

class Switch{
	public:
	  Switch(int _pin);
	  bool getState();
	private:
	  int pin;
};
#endif
