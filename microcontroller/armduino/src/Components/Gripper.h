#ifndef Gripper_h
#define Gripper_h
#include "Arduino.h"
#include "Motor.h"

class Gripper{
	public:
		Gripper(Motor _rotationMotor, Motor _gripperMotor);
		void spin(float _vel);
		void open(float _dist);
	private:
		Motor rotationMotor
		Motor gripperMotor;
		int postion;
};
#endif
