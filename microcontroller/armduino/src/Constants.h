#ifndef Constants_h
#define Constants_h
#include "Arduino.h"

class Constants{
	public:
		Constants() {};
		//Arm Motors
		static const int jointMotor1 = 0;
		static const int jointMotor2 = 1;
		static const int jointMotor3 = 2;
		static const int jointMotor4A = 3;
		static const int jointMotor4B = 4;
		static const int gripperRotateA = 10;
		static const int gripperRotateB = 11;
		static const int gripperOpenA = 12;
		static const int gripperOpenB = 13;
		//Arm Sensors
		static const int joint1Pot = A0;
		static const int joint2Pot = A1;
		static const int joint3pot = A2;
		static const int joint4Pot = A3;
		//Carousel Motors
		static const int carouselRotateA = 5;
		static const int carouselRotateB = 6;
		static const int carouselCrankA = 7;
		static const int carouselCrankB = 8;
		//Carousel Sensors
		static const int closeSwitch = 25;
		static const int openSwitch = 26;
		static const int indexSwitch = 27;
		//whinch sensors
		static const int winchMotor = 9;
		//Step anlges & steps
		static const int nema17Steps = 200;
		static const float nema17Angle = 1.8;
		static const float nema17GearAngle51 = .0353;
		//Serial baud
		static const int serialBaud = 9600;
		//Joint & Gripper Misc
		static const int stepsPerCm = 100;
		//PID tuning Values & constants
		//Dc motors
		static const int Kp = 0;
		static const int Ki = 0;
		static const int Kd = 0;
		static const int maxOut = 360;
		static const int minOut = 360;

};
#endif
