#ifndef Constants_h
#define Constants_h
class Constants{
	public:
		Constants();
		//Left Motor pins
		const int leftFront = 0;
		const int leftMid = 1;
		const int leftRear = 2;
		//Right Motor pins
		const int rightFront = 3;
		const int rightMid = 4;
		const int rightRear = 5;
		//Encoder pins
		//left pins
		const int LFEncA = 6;
		const int LFEncB = 7;
		const int LMEncA = 8;
		const int LMEncB = 9;
		const int LREncA = 10;
		const int LREncB = 11;
		//right pins
		const int RFEncA = 12;
		const int RFEncB = 13;
		const int RMEncA = 14;
		const int RMEncB = 15;
		const int RREncA = 16;
		const int RREncB = 17;
		//PID constants
		const int Kp = 1;
		const int Ki = 0;
		const int Kd = 0;
};
#endif
