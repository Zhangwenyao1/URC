#ifndef Constants_h
#define Constants_h
#include <Arduino.h>

class Constants{
	public:
		Constants() {};

		//MISC.
		static constexpr double Pi = 3.14159;
		static constexpr int totalTicks = 1024;

		//Motor Controllers
		static constexpr bool victor = true;
		static constexpr bool spark = false;
		//Arm Motors
		static constexpr int jointMotor1 = 0;
		static constexpr int jointMotor2 = 1;
		static constexpr int jointMotor3 = 2;
		static constexpr int jointMotor4 = 3;
		static constexpr int gripperRotateMotor = 10;
		static constexpr int gripperOpenMotor= 12;
		//Arm Sensors
		static constexpr int joint1Pot = A0;
		static constexpr int joint2Pot = A1;
		static constexpr int joint3pot = A2;
		static constexpr int joint4Pot = A3;
		//Gripper Sensors
		static constexpr int openSwitch = 10;
		static constexpr int closeSwitch = 11;
		//whinch Motors
		static constexpr int winchMotor = 9;
		//Arm constraints //Upper and Lower limits
		/*static constexpr double joint1Upper = math.Pi*2;
		static constexpr double joint1Lower = 0;
		static constexpr double joint2Upper = math.Pi*1/2;
		static constexpr double joint2Lower = 0;
		static constexpr double joint3Upper = math.Pi*13/18;
		static constexpr double joint3Lower = 0;
		static constexpr double joint4Upper = math.Pi*3/2;
		static constexpr double joint4Lower = 0;*/
		//Arm Gear Ratios //For pot calculations //Defines how many full rotations of the pot
		//accounts for one full rotation of the given joint
		static constexpr double joint1Gear = 45/16;
		static constexpr double joint2Gear = 20;
		static constexpr double joint3Gear = 18;
		static constexpr double joint4Gear = 1;
		//Serial baud
		static constexpr int serialBaud = 9600;
		//PID tuning Values & constants
		//Dc motors
		static constexpr double joint1Gains[3] = {
				0,
				0,
				0
		};
		static constexpr double joint2Gains[3] = {
				0,
				0,
				0
		};
		static constexpr double joint3Gains[3] = {
				0,
				0,
				0
		};
		static constexpr int joint4Gains[3] = {
				0,
				0,
				0
		};
		static constexpr double maxOut = 1;
		static constexpr double minOut = -1;
};
#endif
