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
		//whinch sensors
		static const int winchMotor = 9;

		//Serial baud
		static const int serialBaud = 9600;

		//PID tuning Values & constants
		//Dc motors
		static const int Kp = 0;
		static const int Ki = 0;
		static const int Kd = 0;
		static const double maxOut = 1;
		static const double minOut = -1;

};
#endif
