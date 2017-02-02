#include "Arduino.h"
#include "Winch.h"
#include "Motor.h"

Motor motor;

Winch::Winch(Motor _winchM){
	motor = _winchM;
}
void Winch::doMotor(bool _drive){
	motor.doMotor(_drive);
}
