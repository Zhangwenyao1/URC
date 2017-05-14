#ifndef Motor_h
#define Motor_h
#include "Arduino.h"
#include "./MotorController.h"

class Motor{
  public:
	Motor(){};
	Motor(int pin, bool type){
    	driver =  MotorController(type,pin);
    };
    void doPWM(int input){
    	driver.setDutyCycle(input);
    }
  private:
    MotorController driver;
};
#endif
