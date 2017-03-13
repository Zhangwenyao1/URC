#ifndef Constants_h
#define Constants_h
class Constants{
	public:
		Constants(){};
		//Left Motor pins
		static const int leftFront = 0;
		static const int leftMid = 1;
		static const int leftRear = 2;
		//Right Motor pins
		static const int rightFront = 3;
		static const int rightMid = 4;
		static const int rightRear = 5;
		//Encoder pins
		//left pins
		static const int LFEncA = 6;
		static const int LFEncB = 7;
		static const int LMEncA = 8;
		static const int LMEncB = 9;
		static const int LREncA = 10;
		static const int LREncB = 11;
		//right pins
		static const int RFEncA = 12;
		static const int RFEncB = 13;
		static const int RMEncA = 14;
		static const int RMEncB = 15;
		static const int RREncA = 16;
		static const int RREncB = 17;
		//PID constants
		static const int Kp = 1;
		static const int Ki = 0;
		static const int Kd = 0;
		//Misc.
		static const int serialBaud = 9600;
};
#endif
