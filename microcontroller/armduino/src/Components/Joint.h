#ifndef Joint_h
#define Joint_h
#include "Arduino.h"
#include "Motor.h"
#include "Potentiometer.h"
#include <PID_v1.h>

class Joint{
	public:
		Joint(Motor _motor, Potentiometer _jointPot);
		float getJointPosition();
		bool setJointPosition(float _pos);
		void setJointPositionStepper(float _pos);
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
