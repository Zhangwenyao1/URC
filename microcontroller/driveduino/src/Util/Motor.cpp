#include <Arduino.h>
#include <Servo.h>
#include "Util/Motor.h"
#include "Util/MotorController.h"

Motor::Motor(){ }
Motor::Motor(int pin, bool type){
	MotorController driver = MotorController(type, pin);
}
void Motor::doPWM(int input){
	driver.setDutyCycle(input);
}
