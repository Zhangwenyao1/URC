#ifndef Joint_h
#define Joint_h

//If PID_v1.h is throwing an error saying no constructor PID::PID(), go into the class and add it.
#include "Arduino.h"
#include "../Util/Motor.h"
#include "../Util/Potentiometer.h"
#include <PID_v1.h>
class Joint{
	public:
		Joint(Motor jointMotor, Potentiometer jointPot, double Kp, double Kd, double Ki, double maxOut, double minOut){
			this->jointMotor = jointMotor;
			this->jointPot = jointPot;
			this->Kp = Kp;
			this->Kd = Kd;
			this->Ki = Ki;
			this->maxOut = maxOut;
			this->minOut = minOut;
			jointPID = PID(&currentPos, &output, &setPoint, Kp, Ki, Kd, DIRECT);
			jointPID.SetOutputLimits(minOut, maxOut);
			jointPID.SetMode(MANUAL);
		};
		float getJointPosition(){
			currentPos = jointPot.getValue();
			return currentPos;
		};
		bool setJointPosition(double setPoint){
			this->setPoint = setPoint;
			if(!jointPID.Compute()){
				jointPID.SetMode(AUTOMATIC);
				jointMotor.doPWM(output);
				return false;
			}
			else{
				jointPID.SetMode(MANUAL);
				return true;
			}
		};
		Motor jointMotor;
	private:
		double output, setPoint, currentPos,Kp,Kd,Ki,maxOut,minOut;
		Potentiometer jointPot;
		PID jointPID;
};
#endif
