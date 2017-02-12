#include "Arduino.h"
#include "Winch.h"
#include "Motor.h"
#include <std_msgs/Int16.h>
Motor _motor;

Winch::Winch(Motor _winchM){
	_motor = _winchM;
}
void Winch::doMotor(std_msgs::Int16 _drive){
	_motor.doPWM(_drive.data);
}
