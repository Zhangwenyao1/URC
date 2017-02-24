#include <Arduino.h>
#include <Servo.h>
#include <Stepper.h>
#include "Motor.h"
#include "Servo.h"

Servo servo;
Stepper stepper = Stepper(0,0,0);

Motor::Motor(){ }
Motor::Motor(int _pin){
	pin =_pin;
	servo.attach(pin);
}
Motor::Motor(Stepper _Stepper){
	stepper = _Stepper;
	stepper.setSpeed(200);
}
void Motor::doPWM(float _input){
	servo.write(_input);
}
void Motor::doStepper(int _input){
	stepper.step(_input);
}
