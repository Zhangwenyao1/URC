#ifndef Arm_h
#define Arm_h
#include <Arduino.h>

class Switch{
	public:
    Switch();
	  Switch(int pin);
	  bool getState();
	private:
	  int pin;
};
#endif
