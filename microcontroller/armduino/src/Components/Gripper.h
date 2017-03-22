#ifndef Gripper_h
#define Gripper_h
#include <Arduino.h>
#include "Motor.h"
#include "Util/Switch.h"

class Gripper{
	public:
		Gripper(Motor rotationMotor, Motor gripperMotor, Switch limitSwitch);
		void spin(float vel);
		void open(float dist);
		bool zeroGripper();
	private:
		Motor rotationMotor, gripperMotor;
		Switch limitSwitch;
		int postion;

};
#endif
