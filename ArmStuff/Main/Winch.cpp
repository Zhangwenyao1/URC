#include "Arduino.h"
#include "Winch.h"
#include "Motor.h"

Winch::Winch(Motor _motor){
	motor=_motor;
}
void Winch::doMotor(bool _drive){
	motor.doMotors(_drive);
}
