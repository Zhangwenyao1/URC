//driveduino
#include "Arduino.h"
#include <Encoder.h>
#include <PID_v1.h>

#include "Util/Motor.h"
#include "Constants.h"

#define serialBaud 9600

struct MOTORS{
	static const int leftFront = 1;
	static const int leftMid = 2;
	static const int leftRear = 3;
	static const int rightFront = 4;
	static const int rightMid = 5;
	static const int rightRear = 6;
}motors;

Constants constant = Constants();
//Motor Declarations
Motor leftFrontMotor = Motor(constant.leftFront);
Motor leftMidMotor = Motor(constant.leftMid);
Motor leftRearMotor = Motor(constant.leftRear);
Motor rightFrontMotor = Motor(constant.rightFront);
Motor rightMidMotor = Motor(constant.rightMid);
Motor rightRearMotor = Motor(constant.rightRear);

//Encoder Declarations
Encoder leftFrontEncoder = Encoder(constant.LFEncA,constant.LFEncB);
Encoder leftMidEncoder = Encoder(constant.LMEncA,constant.LMEncB);
Encoder leftRearEncoder = Encoder(constant.LREncA,constant.LREncB);
Encoder rightFrontEncoder = Encoder(constant.RFEncA,constant.RFEncB);
Encoder rightMidEncoder = Encoder(constant.RMEncA,constant.RMEncB);
Encoder rightRearEncoder = Encoder(constant.RREncA,constant.RREncB);

void setup() {
	Serial.begin(serialBaud);
}
void loop() {

}
void recieveData(){

}
void setWheelVel(float _vel,int _motor){
	switch(_motor){
		default:
		case motors.leftFront:
			leftFrontMotor.doPWM(_vel);
			break;
		case motors.leftMid:
			leftMidMotor.doPWM(_vel);
			break;
		case motors.leftRear:
			leftRearMotor.doPWM(_vel);
			break;
		case motors.rightFront:
			rightFrontMotor.doPWM(_vel);
			break;
		case motors.rightMid:
			rightMidMotor.doPWM(_vel);
			break;
		case motors.rightRear:
			rightRearMotor.doPWM(_vel);
			break;
	}
}
int getWheelPosition(int _motor){
	switch(_motor){
		default:
		case motors.leftFront:
			return leftFrontEncoder.read();
		case motors.leftMid:
			return leftMidEncoder.read();
		case motors.leftRear:
			return leftRearEncoder.read();
		case motors.rightFront:
			return rightFrontEncoder.read();
		case motors.rightMid:
			return rightMidEncoder.read();
		case motors.rightRear:
			return rightRearEncoder.read();
	}
}
