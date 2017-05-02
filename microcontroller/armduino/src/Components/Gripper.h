#ifndef Gripper_h
#define Gripper_h
#include <Arduino.h>
#include "Motor.h"
#include "Util/Switch.h"

class Gripper{
	public:
		Gripper(Motor rotationMotor, Motor gripperMotor, Switch openSwitch, Switch closeSwitch);
		void spin(float vel);
		bool open();
		bool close();
		bool zeroGripper();
	private:
		Motor rotationMotor, gripperMotor;
		Switch openSwitch, closeSwitch;
		bool Open;

};
#endif
