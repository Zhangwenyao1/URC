#ifndef Joint_h
#define Joint_h
#include "Arduino.h"
#include "Motor.h"
#include "Potentiometer.h"
#include <PID_v1.h>

class Joint{
	public:
		Joint(Motor motor, Potentiometer jointPot);
		float getJointPosition();
		bool setJointPosition(float pos);
		void setJointPositionStepper(float pos);
		void initPID(int Kp, int Kd, int Ki, int degMax, int degMin);
		void updateJoint();
	private:
		double pos;
		double setPoint;
		double currentPos;
		Motor jointMotor;
		Potentiometer jointPot;
		PID jointPID;
};
#endif
