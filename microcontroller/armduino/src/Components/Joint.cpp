#include "Arduino.h"
#include "Joint.h"
#include "Motor.h"
#include "Potentiometer.h"
#include "ros.h"
#include "mathFunc.h"
#include "Constants.h"

Motor jointMotor = Motor();
Potentiometer jointPot = Potentiometer();
mathFunc math = mathFunc();
Constants constant = Constants();
double currentPos;
double pos;
double setPoint;

Joint::Joint(Motor _motor, Potentiometer _jointPot){
	jointMotor = _motor;
	jointPot = _jointPot;
}
float Joint::getJointPosition(){
	currentPos = jointPot.getRad();
	return currentPos;
}
void initPID(int Kp, int Kd, int Ki,int degMax, int degMin){
	PID jointPID(&currentPos,&pos,&setPoint,Kp,Ki,Kd,DIRECT);
	jointPID.SetOutputLimits(math.degToRad(degMin),math.degToRad(degMax));
}
bool Joint::setJointPosition(float _setPoint){
	setPoint = _setPoint;
	if(!jointPID.Compute()){
		jointMotor.doPWM(map(((int)math.radToDegrees(setPoint)),-360,360,0,180));
		return false;
	}
	else
		return true;
}
void Joint::setJointPositionStepper(float _rads){
	int steps = math.toSteps(math.radToDegrees(_rads),constant.nema17GearAngle51);
	jointMotor.doStepper(steps);
}
