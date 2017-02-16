#include "Arduino.h"
#include "Gripper.h"
#include "Motor.h"
#include "ros.h"
#include <std_msgs/Float32.h>
#include <std_msgs/UInt16.h>

Motor gripperMotor;
Motor rotationMotor;
Gripper::Gripper(Motor _rotationMotor, Motor _gripperMotor){
	gripperMotor = _gripperMotor;
	rotationMotor = _rotationMotor;
}
void Gripper::spin(int _vel){
	rotationMotor.doStepper(_vel);
}
void Gripper::open(int _vel){
	gripperMotor.doStepper(_vel);
}
