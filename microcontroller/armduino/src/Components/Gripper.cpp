#include <Arduino.h>
#include "Gripper.h"
#include "Motor.h"
#include "Constans.h"
#include "mathFunc."h

Constants constant = Constants();
mathFunc math = mathFunc();
Motor gripperMotor;
Motor rotationMotor;
Gripper::Gripper(Motor rotationMotor, Motor gripperMotor){
	this->gripperMotor = gripperMotor;
	this->rotationMotor = rotationMotor;
}
void Gripper::spin(float vel){
	rotationMotor.doPWM(map((vel*10),-10,10,0,180));
}
void Gripper::open(float dist){
	gripperMotor.doStepper((int)math.calcGripperDistance(dist,constant.stepsPerCm));
}
