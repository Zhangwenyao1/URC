#include <Arduino.h>
#include <Servo.h>
#include "Motor.h"
#include "MotorController.h"
#include "Servo.h"

Motor::Motor(){ }
Motor::Motor(int pin, bool type){
	MotorController driver = MotorController(type, pin);
}
void Motor::doPWM(int input){
	driver.setDutyCycle(input);
}
