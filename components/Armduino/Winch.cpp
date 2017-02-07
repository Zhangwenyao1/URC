#include "Arduino.h"
#include "Winch.h"
#include "Motor.h"
#include <std_msgs/Float32.h>
Motor _motor;

Winch::Winch(Motor _winchM){
	_motor = _winchM;
}
void Winch::doMotor(std_msgs::Float32 _drive){
	_motor.doPWM(_drive.data);
}
