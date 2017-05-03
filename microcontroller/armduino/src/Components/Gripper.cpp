#include <Arduino.h>
#include "Gripper.h"
#include "Motor.h"
#include "Constans.h"
#include "mathFunc.h"

Constants constant = Constants();
mathFunc math = mathFunc();
Motor gripperMotor, rotationMotor;
Switch limitSwitch;

Gripper::Gripper(Motor rotationMotor, Motor gripperMotor, Switch openSwitch, Switch closeSwitch){
	this->gripperMotor = gripperMotor;
	this->rotationMotor = rotationMotor;
	this->openSwitch = openSwitch;
	this->closeSwitch = closeSwitch;
}
void Gripper::spin(float vel){
	rotationMotor.doPWM(vel);
}
bool Gripper::open(){
	while(!openSwitch.getState())
		gripperMotor.doPWM(1);
	open = !open;
	return open;
}
bool Gripper::close(){
	while(!closeSwitch.getState())
		gripperMotor.doPWM(-1);
	open = !open;
	return open;
}
bool Gripper::zeroGripper(){
	while(!openSwitch.getState()&& open!=true)
		gripperMotor.doPWM(1);
	open = true;
	return open;
}
