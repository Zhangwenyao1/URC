//driveduino
#include "Arduino.h"
#include <Encoder.h>
#include <PID_v1.h>

#include "Util/Motor.h"
#include "Constants.h"

#define vel 0
#define enc 1

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

struct MOTORDATA{
	float leftFront[2];
	float leftMid[2];
	float leftRear[2];
	float rightFront[2];
	float rightMid[2];
	float rightRear[2];
}motorData;
void setup() {
	//Zeroing the Encoders
	leftFrontEncoder.write(0);
	leftMidEncoder.write(0);
	leftRearEncoder.write(0);
	rightFrontEncoder.write(0);
	rightMidEncoder.write(0);
	rightRearEncoder.write(0);

	Serial.begin(constant.serialBaud);
}

void recieveData(){

}
void setWheelVel(){
	leftFrontMotor.doPWM(motorData.leftFront[vel]);
	leftMidMotor.doPWM(motorData.leftMid[vel]);
	leftRearMotor.doPWM(motorData.leftRear[vel]);
	rightFrontMotor.doPWM(motorData.rightFront[vel]);
	rightMidMotor.doPWM(motorData.rightMid[vel]);
	rightRearMotor.doPWM(motorData.rightRear[vel]);
}
void getWheelPosition(){
	motorData.leftFront[enc] = leftFrontEncoder.read();
	motorData.leftMid[enc] = leftMidEncoder.read();
	motorData.leftRear[enc] = leftRearEncoder.read();
	motorData.rightFront[enc] = rightFrontEncoder.read();
	motorData.rightMid[enc] = rightMidEncoder.read();
	motorData.rightRear[enc] = rightRearEncoder.read();
}
void loop() {
	setWheelVel();
	getWheelPosition();
}
