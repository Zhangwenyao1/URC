#include "Arduino.h"
#include "Motor.h"
#include "ros.h";
#include <std_msgs/UInt16.h>
#include <std_msgs/Float32.h>

Motor::Motor(){ }
Motor::Motor(int _pin, int _dirPin){
  pin = _pin;
  dirPin = _dirPin;
  pinMode(pin, OUTPUT);
  pinMode(dirPin, OUTPUT);
}
void Motor::doMotorsPWM(std_msgs::Float32 _input){
  bool _direction;
  float input = _input.data;
  _direction = ((input<0) ? false : true);
  digitalWrite(dirPin,_direction);
  analogWrite(pin, map((abs(input)*10),0,10,0,255));
}
void Motor::doMotor(int _drive){
	  bool _direction;
	  _direction = ((_drive<0) ? false : true);

	  digitalWrite(dirPin,_direction);
	  digitalWrite(pin, _drive);
}
