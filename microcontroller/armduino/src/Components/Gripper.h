#ifndef Gripper_h
#define Gripper_h
#include "Arduino.h"
#include "Motor.h"

class Gripper{
	public:
		Gripper(Motor rotationMotor, Motor gripperMotor);
		void spin(float vel);
		void open(float dist);
	private:
		Motor rotationMotor
		Motor gripperMotor;
		int postion;
};
#endif
