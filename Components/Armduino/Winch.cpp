#include "Arduino.h"
#include "Winch.h"
#include "Motor.h"

Motor _motor;

Winch::Winch(Motor _winchM){
	_motor = _winchM;
}
void Winch::doMotor(bool _drive){
	_motor.doMotor(_drive);
}
