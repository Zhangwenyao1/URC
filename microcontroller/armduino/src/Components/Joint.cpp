#include "Arduino.h"
#include "Joint.h"
#include "Motor.h"
#include "Potentiometer.h"
#include "ros.h"
Motor jointMotor = Motor();
Potentiometer jointPot = Potentiometer();

Joint::Joint(Motor _motor, Potentiometer _jointPot){
	jointMotor = _motor;
	jointPot = _jointPot;
}
int Joint::getJointPosition(){
	return jointPot.getValue();
}
void Joint::setJointPosition(int _pos){
	jointMotor.doPWM(_pos);
}
void Joint::setJointPositionStepper(int _pos){
	jointMotor.doStepper(_pos);
}
