#include <Arduino.h>
#include "Gripper.h"
#include "Motor.h"
#include "Constans.h"
#include "mathFunc."h

Constants constant = Constants();
mathFunc math = mathFunc();
Motor gripperMotor;
Motor rotationMotor;
Gripper::Gripper(Motor _rotationMotor, Motor _gripperMotor){
	gripperMotor = _gripperMotor;
	rotationMotor = _rotationMotor;
}
void Gripper::spin(float _vel){
	rotationMotor.doPWM(map((_vel*10),-10,10,0,180));
}
void Gripper::open(float _dist){
	gripperMotor.doStepper((int)math.calcGripperDistance(_dist,constant.stepsPerCm));
}
