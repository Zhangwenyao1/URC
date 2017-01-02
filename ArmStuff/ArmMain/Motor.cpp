#include "Arduino.h"
#include "Motor.h"

Motor::Motor(int _pin, int _dirPin){
  pin = _pin;
  dirPin = _dirPin;
  pinMode(pin, OUTPUT);
  pinMode(dirPin, OUTPUT);
}
void Motor::doMotors(double input){
  bool direction;
  int speed;
  if(input < 0)
    direction = false;
  else 
    direction = true;
  
  digitalWrite(dirPin,direction);
  analogWrite(pin, map(0,1,0,255,abs(input)));
}
