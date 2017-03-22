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
		int setJointPosition(float pos);
		void setJointPositionStepper(float pos);
		void initPID(int Kp, int Kd, int Ki, int degMax, int degMin);
		void updateJoint();
	private:
		float outPut, setPoint, currentPos;
		Motor jointMotor;
		Potentiometer jointPot;
		PID jointPID;
};
#endif
