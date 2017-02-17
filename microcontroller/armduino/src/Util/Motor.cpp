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
}
void Motor::doPWM(float _input){
	float input = _input;
	servo.write(map((input*10),-10,10,0,180));
}
void Motor::doStepper(int _input){
	stepper.step(_input);
}
