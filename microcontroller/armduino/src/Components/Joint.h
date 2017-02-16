#ifndef Joint_h
#define Joint_h
#include "Arduino.h"
#include "Motor.h"
#include "Potentiometer.h"
#include "ros.h"

class Joint{
	public:
		Joint(Motor _motor, Potentiometer _jointPot);
		int getJointPosition();
		void setJointPosition(int _pos);
		void setJointPositionStepper(int _pos);
	private:
		Motor jointMotor;
		Potentiometer jointPot;
};
#endif
