#ifndef Joint_h
#define Joint_h
#include "Arduino.h"
#include "Motor.h"
#include "Potentiometer.h"
#include "ros.h"
#include <std_msgs/Float32.h>

class Joint{
	public:
		Joint(Motor _motor, Potentiometer _jointPot);
		uint16_t getJointPosition();
		void setJointPosition(std_msgs::Float32 _pos);
	private:
		Motor jointMotor;
		Potentiometer jointPot;
};
#endif
