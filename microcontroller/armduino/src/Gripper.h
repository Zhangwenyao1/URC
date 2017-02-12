#ifndef Gripper_h
#define Gripper_h
#include "Arduino.h"
#include "Motor.h"
#include "ros.h"
#include <std_msgs/Float32.h>
#include <std_msgs/UInt16.h>
class Gripper{
	public:
		Gripper(Motor _motor);
		void move(std_msgs::UInt16 _point);
	private:
		Motor gripperMotor;
		uint16_t postion;
};
#endif
