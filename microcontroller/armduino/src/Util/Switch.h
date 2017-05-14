#ifndef Arm_h
#define Arm_h
#include <Arduino.h>

class Switch{
	public:
    	Switch(){};
    	Switch(int pin){
    		this->pin = pin;
    		pinMode(pin, INPUT);
    	};
    	bool getState(){
    		return digitalRead(pin);
    	};
	private:
    	int pin;
};
#endif
