#include <Arduino.h>
#include "Winch.h"
#include "Motor.h"
Motor _motor;

Winch::Winch(Motor winchMotor){
	this->winchMotor = winchMotor;
}
void Winch::doMotor(int direction){
	if(direction==1)
		drive == 180;
	else if(direction == -1)
		drive == 0;
	else
		drive = 90;
	winchMotor.doPWM(drive);
}
