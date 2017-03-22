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
double currentPos;
double pos;
double setPoint;

Joint::Joint(Motor motor, Potentiometer jointPot){
	this->jointMotor = motor;
	this->jointPot = jointPot;
}
float Joint::getJointPosition(){
	currentPos = jointPot.getRad();
	return currentPos;
}
void initPID(int Kp, int Kd, int Ki,int degMax, int degMin){
	PID jointPID(&currentPos, &outPut, &setPoint, Kp, Ki, Kd, DIRECT);
	jointPID.SetOutputLimits(math.degToRad(degMin), math.degToRad(degMax));
}
int Joint::setJointPosition(float setPoint){
	this->setPoint = setPoint;
	if(!jointPID.Compute()){
		jointMotor.doPWM(map(((int)math.radToDegrees(outPut)),-360,360,0,180));
		return 0;
	}
	else
		return 1;
}
void Joint::setJointPositionStepper(float rads){
	int steps = math.toSteps(math.radToDegrees(rads),constant.nema17GearAngle51);
	jointMotor.doStepper(steps);
}
