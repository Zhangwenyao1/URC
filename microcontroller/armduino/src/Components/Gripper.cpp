#include <Arduino.h>
#include "Gripper.h"
#include "Motor.h"
#include "Constans.h"
#include "mathFunc.h"

Constants constant = Constants();
mathFunc math = mathFunc();
Motor gripperMotor, rotationMotor;
Switch limitSwitch;

Gripper::Gripper(Motor rotationMotor, Motor gripperMotor, Switch limitSwitch){
	this->gripperMotor = gripperMotor;
	this->rotationMotor = rotationMotor;
	this->limitSwitch = limitSwitch;
}
void Gripper::spin(float vel){
	rotationMotor.doPWM(map((vel*10),-10,10,0,180));
}
void Gripper::open(float dist){
	gripperMotor.doStepper((int)math.calcGripperDistance(dist,constant.stepsPerCm));
}
bool zeroGripper(){
	if(limitSwitch.getState()!=true){
		gripperMotor.doStepper(5000);
		return false;
	}
	else{
		position = 0;
		return true;
	}
}
