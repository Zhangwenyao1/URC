#ifndef Constants_h
#define Constants_h
#include "Arduino.h"

class Constants{
	public:
		Constants();
		//Arm Motors
		const int jointMotor1 = 0;
		const int jointMotor2 = 1;
		const int jointMotor3 = 2;
		const int jointMotor4A = 3;
		const int jointMotor4B = 4;
		const int gripperRotateA = 10;
		const int gripperRotateB = 11;
		const int gripperOpenA = 12;
		const int gripperOpenB = 13;
		//Arm Sensors
		const int joint1Pot = A0;
		const int joint2Pot = A1;
		const int joint3pot = A2;
		const int joint4Pot = A3;
		//Carousel Motors
		const int carouselRotateA = 5;
		const int carouselRotateB = 6;
		const int carouselCrankA = 7;
		const int carouselCrankB = 8;
		//Carousel Sensors
		const int closeSwitch = 25;
		const int openSwitch = 26;
		const int indexSwitch = 27;
		//whinch sensors
		const int winchMotor = 9;
};
#endif
