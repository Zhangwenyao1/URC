#ifndef Joint_h
#define Joint_h
#include "Arduino.h"
#include "Motor.h"
#include "Potentiometer.h"
#include "Encoder.h"
#include "ros.h"
#include <std_msgs/Float32.h>

class Joint{
	public:
		Joint(Motor _motor, Potentiometer _jointPot);
		Joint(Motor _motor, Encoder _jointEncoder);
		uint16_t getJointPosition();
		void setJointPosition(std_msgs::Float32 _pos);
	private:
		Motor jointMotor;
		Potentiometer jointPot;
		Encoder	jointEncoder;
};
#endif
