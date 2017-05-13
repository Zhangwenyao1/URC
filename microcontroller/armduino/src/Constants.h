#ifndef Constants_h
#define Constants_h
#include "Arduino.h"

class Constants{
	public:
		Constants() {};
		//Motor Controllers
		const bool victor = true;
		const bool spark = false;
		//Arm Motors
		const int jointMotor1 = 0;
		const int jointMotor2 = 1;
		const int jointMotor3 = 2;
		const int jointMotor4 = 3;
		const int gripperRotateMotor = 10;
		const int gripperOpenMotor= 12;
		//Arm Sensors
		const int joint1Pot = A0;
		const int joint2Pot = A1;
		const int joint3pot = A2;
		const int joint4Pot = A3;
		//Gripper Sensors
		const int openSwitch = 10;
		const int closeSwitch = 11;
		//whinch Motors
		const int winchMotor = 9;
		//Arm constraints //Upper and Lower limits
		const int joint1Upper = 360;
		const int joint1Lower = 0;
		const int joint2Upper = 90;
		const int joint2Lower = 0;
		const int joint3Upper = 130;
		const int joint3Lower = 0;
		const int joint4Upper = 270;
		const int joint4Lower = 0;
		//Arm Gear Ratios //For pot calculations //Defines how many full rotations of the pot
		//accounts for one full rotation of the given joint
		const int joint1Gear = 45/16;
		const int joint2Gear = 20;
		const int joint3Gear = 18;
		//Serial baud
		const int serialBaud = 9600;

		//PID tuning Values & constants
		//Dc motors
		const int joint1Gains[3] = {
				0,
				0,
				0
		};
		const int joint2Gains[3] = {
				0,
				0,
				0
		};
		const int joint3Gains[3] = {
				0,
				0,
				0
		};
		const int joint4Gains[3] = {
				0,
				0,
				0
		};
		const double maxOut = 1;
		const double minOut = -1;

};
#endif
