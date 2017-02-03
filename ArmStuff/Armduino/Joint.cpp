#include "Arduino.h"
#include "Joint.h"
#include "Motor.h"
#include "Potentiometer.h"
#include "ros.h"
#include <std_msgs/Float32.h>

Motor jointMotor = Motor();
Potentiometer jointPot = Potentiometer();

Joint::Joint(Motor _motor, Potentiometer _jointPot){
	jointMotor = _motor;
	jointPot = _jointPot;
}
uint16_t Joint::getJointPosition(){
	return jointPot.getValue();
}
void Joint::setJointPosition(std_msgs::Float32 _pos){
	jointMotor.doPWM(_pos.data);
}
