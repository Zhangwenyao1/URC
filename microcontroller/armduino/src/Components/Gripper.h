#ifndef Gripper_h
#define Gripper_h
#include <Arduino.h>
#include "../Util/Motor.h"
#include "../Util/Switch.h"

class Gripper{
	public:
		Gripper(Motor rotationMotor, Motor gripperMotor, Switch openSwitch, Switch closeSwitch){
			this->gripperMotor = gripperMotor;
			this->rotationMotor = rotationMotor;
			this->openSwitch = openSwitch;
			this->closeSwitch = closeSwitch;
			Open = false;
		};
		void spin(float vel){
			rotationMotor.doPWM(vel);
		};
		bool open(){
			while(!openSwitch.getState())
				gripperMotor.doPWM(1);
			Open = !Open;
			return Open;
		};
		bool close(){
			while(!closeSwitch.getState())
				gripperMotor.doPWM(-1);
			Open = !Open;
			return Open;

		};
		bool zeroGripper(){
			while(!openSwitch.getState()&& Open!=true)
				gripperMotor.doPWM(1);
			Open = true;
			return Open;
		};
	private:
		Motor rotationMotor, gripperMotor;
		Switch openSwitch, closeSwitch;
		bool Open;

};
#endif
