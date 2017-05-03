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
		bool setJointPosition(double pos);
		void initPID(double Kp, double Kd, double Ki, double maxOut, double minOut);
		void updateJoint();
	private:
		double outPut, setPoint, currentPos;
		Motor jointMotor;
		Potentiometer jointPot;
		PID jointPID;
};
#endif
