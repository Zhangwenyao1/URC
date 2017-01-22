#include "Arduino.h"
#include "Motor.h"

Motor::Motor(int _pin, int _dirPin){
  pin = _pin;
  dirPin = _dirPin;
  pinMode(pin, OUTPUT);
  pinMode(dirPin, OUTPUT);
}
void Motor::doMotorsPWM(double input){
  bool _direction;
  _direction = ((input<0) ? false : true);

  digitalWrite(dirPin,_direction);
  analogWrite(pin, map(0,1,0,255,abs(input)));
}
void Motor::doMotor(int _drive){
	  bool _direction;
	  _direction = ((input<0) ? false : true);

	  digitalWrite(dirPin,_direction);
	  digitalWrite(pin, _drive);
}
