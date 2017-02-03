#include "Arduino.h"
#include <Servo.h>
#include "Motor.h"
#include "Servo.h"
#include "ros.h";
#include <std_msgs/UInt16.h>
#include <std_msgs/Float32.h>

Servo motor;
Motor::Motor(){ }
Motor::Motor(int _pin, int _dirPin){
  pin = _pin;
  dirPin = _dirPin;
  pinMode(pin, OUTPUT);
  pinMode(dirPin, OUTPUT);
}
Motor::Motor(int _pin){
	pin = _pin;
	motor.attach(pin);
}
void Motor::doMotorsPWM(std_msgs::Float32 _input){
	
	if(dirPin > 0){
		float input = _input.data;
		motor.write(map((input*10),-10,10,0,180));
	}
	else{
		bool _direction;
		float input = _input.data;
		_direction = ((input<0) ? false : true);
		digitalWrite(dirPin,_direction);
		analogWrite(pin, map(abs(input*10),0,10,0,255));
	}
}
void Motor::doMotor(int _drive){
	  bool _direction;
	  _direction = ((_drive<0) ? false : true);
	  digitalWrite(dirPin,_direction);
	  digitalWrite(pin, _drive);
}
