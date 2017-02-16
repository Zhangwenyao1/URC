#ifndef Gripper_h
#define Gripper_h
#include "Arduino.h"
#include "Motor.h"

class Gripper{
	public:
		Gripper(Motor _rotationMotor, Motor _gripperMotor);
		void spin(int _vel);
		void open(int _vel);
	private:
		Motor rotationMotor
		Motor gripperMotor;
		int postion;
};
#endif
