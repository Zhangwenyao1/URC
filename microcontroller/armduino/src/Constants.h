#ifndef Constants_h
#define Constants_h
#include "Arduino.h"

class Constants{
	public:
		Constants() {};
		//Motor Controllers
		static const bool victor = true;
		static const bool spark = false;
		//Arm Motors
		static const int jointMotor1 = 0;
		static const int jointMotor2 = 1;
		static const int jointMotor3 = 2;
		static const int jointMotor4 = 3;
		static const int gripperRotateMotor = 10;
		static const int gripperOpenMotor= 12;
		//Arm Sensors
		static const int joint1Pot = A0;
		static const int joint2Pot = A1;
		static const int joint3pot = A2;
		static const int joint4Pot = A3;
		//Gripper Sensors
		static const int openSwitch = 10;
		static const int closeSwitch = 11;
		//whinch Motors
		static const int winchMotor = 9;
		//Arm constraints //Upper and Lower limits
		static const int joint1Upper = 360;
		static const int joint1Lower = 0;
		static const int joint2Upper = 90;
		static const int joint2Lower = 0;
		static const int joint3Upper = 130;
		static const int joint3Lower = 0
		static const int joint4Upper = 270;
		static const int joint4Lower = 0;
		//Arm Gear Ratios //For pot calculations //Defines how many full rotations of the pot
		//accounts for one full rotation of the given joint
		static const int joint1Gear = 45/16;
		static const int joint2Gear = 20;
		static const int joint3Gear = 18;
		//Serial baud
		static const int serialBaud = 9600;

		//PID tuning Values & constants
		//Dc motors
		static const int joint1Gains[3] = {
				0,
				0,
				0
		};
		static const int joint2Gains[3] = {
				0,
				0,
				0
		};
		static const int joint3Gains[3] = {
				0,
				0,
				0
		};
		static const int joint4Gains[3] = {
				0,
				0,
				0
		};
		static const double maxOut = 1;
		static const double minOut = -1;

};
#endif
