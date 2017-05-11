#include "Arduino.h"
#include "Joint.h"
#include "Motor.h"
#include "Potentiometer.h"
#include "mathFunc.h"
#include "Constants.h"

Motor jointMotor = Motor();
Potentiometer jointPot = Potentiometer();
mathFunc math = mathFunc();
Constants constant = Constants();
double currentPos, pos, output, setPoint;

Joint::Joint(Motor motor, Potentiometer jointPot){
	this->jointMotor = motor;
	this->jointPot = jointPot;
}
float Joint::getJointPosition(){
	currentPos = jointPot.getRad();
	return currentPos;
}
void initPID(double Kp, double Kd, double Ki, double maxOut, double minOut){
	PID jointPID(&currentPos, &output, &setPoint, Kp, Ki, Kd, DIRECT);
	jointPID.SetOutputLimits(minOut, maxOut);
	jointPID.SetMode(MANUAL);
}
bool Joint::setJointPosition(double setPoint){
	this->setPoint = setPoint;
	if(!jointPID.Compute()){
		jointPID.SetMode(AUTOMATIC);
		jointMotor.doPWM(output);
		return false;
	}
	else{
		jointPID.SetMode(MANUAL);
		return true;
	}
}
