//Dependencies
#include <Arduino.h>
//Utilities
#include "Util/Motor.h"
#include "Util/Potentiometer.h"
#include "Util/Switch.h"
#include "Util/mathFunc.h"
//Components
#include "Components/Joint.h"
#include "Components/Winch.h"
#include "Components/Gripper.h"
#include "Constants.h"


Constants constant = Constants();
mathFunc math = mathFunc();

//Motor declaration
Motor j1M = Motor(constant.jointMotor1, constant.victor);//dc motor
Motor j2M = Motor(constant.jointMotor2, constant.victor);//dc motor
Motor j3M = Motor(constant.jointMotor3, constant.victor);//dc motor
Motor j4M = Motor(constant.jointMotor4, constant.victor);//stepper motor
Motor grM = Motor(constant.gripperRotateMotor, constant.victor);//dc motor
Motor goM = Motor(constant.gripperOpenMotor, constant.victor);//dc motor
Motor winchMotor = Motor(constant.winchMotor, constant.victor);//dc motor

//Potentiometer declaration
Potentiometer j1Pos = Potentiometer(constant.joint1Pot);
Potentiometer j2Pos = Potentiometer(constant.joint2Pot);
Potentiometer j3Pos = Potentiometer(constant.joint3pot);
Potentiometer j4Pos = Potentiometer(constant.joint4Pot);

//Joint Declaration
Joint joint1 = Joint(j1M,j1Pos,constant.joint1Gains[0], constant.joint1Gains[1], constant.joint1Gains[2], constant.minOut, constant.maxOut);
Joint joint2 = Joint(j2M,j2Pos,constant.joint2Gains[0], constant.joint2Gains[1], constant.joint2Gains[2], constant.minOut, constant.maxOut);
Joint joint3 = Joint(j3M,j3Pos,constant.joint3Gains[0], constant.joint3Gains[1], constant.joint3Gains[2], constant.minOut, constant.maxOut);
Joint joint4 = Joint(j4M,j4Pos,constant.joint4Gains[0], constant.joint4Gains[1], constant.joint4Gains[2], constant.minOut, constant.maxOut);

//Switch declaration
Switch close = Switch(constant.closeSwitch);
Switch open = Switch(constant.openSwitch);

//Gripper declaration
Gripper gripper = Gripper(grM,goM,open, close);

//Winch declaration
//Winch winch = Winch(winchMotor);

struct RECIEVEJOINT{
	float joint1;
	float joint2;
	float joint3;
	float joint4;
}jointData;

struct RECIEVEGRIPPER{
	float gripperRotate;
	float gripperOpen;
}gripperData;

bool moveJoints(){
	int temp = 0;
	temp += joint1.setJointPosition(math.jointConversions(constant.joint1Gear, jointData.joint1, 10));
	temp += joint2.setJointPosition(math.jointConversions(constant.joint2Gear, jointData.joint2, 10));
	temp += joint3.setJointPosition(math.jointConversions(constant.joint3Gear, jointData.joint3, 10));
	temp += joint4.setJointPosition(math.jointConversions(constant.joint4Gear, jointData.joint4, 1));
	return temp == 4;
}
bool moveGripper(){
	bool temp;
	if(gripperData.gripperOpen == 1)
		temp = gripper.open();
	else if(gripperData.gripperOpen == 2)
		temp = gripper.close();
	else
		temp = false;
	gripper.spin(gripperData.gripperRotate);
	return temp;
}
void sendData(){
	Serial.write(1);
}
void recieveData(){
	String input;
	int commandByte;
	float data[4];
	if(Serial.available()){
		Serial.readBytes((char*)&commandByte,sizeof(int));
	}
	switch(commandByte){
		default:
			break;
		case 1:
			if(Serial.available()>=sizeof(float)){
				Serial.readBytes((char*)&jointData.joint1,sizeof(float));
				Serial.readBytes((char*)&jointData.joint2,sizeof(float));
				Serial.readBytes((char*)&jointData.joint3,sizeof(float));
				Serial.readBytes((char*)&jointData.joint4,sizeof(float));
			}
			break;
		case 2:
			joint1.jointMotor.doPWM(0);
			joint2.jointMotor.doPWM(0);
			joint3.jointMotor.doPWM(0);
			joint4.jointMotor.doPWM(0);
			break;
		case 3:
			if(Serial.available()>=sizeof(float)){
				Serial.readBytes((char*)&gripperData.gripperRotate,sizeof(float));
				Serial.readBytes((char*)&gripperData.gripperOpen,sizeof(float));
			}
			break;
		case 4:
            joint1.jointMotor.doPWM(0);
            joint2.jointMotor.doPWM(0);
            joint3.jointMotor.doPWM(0);
            joint4.jointMotor.doPWM(0);
		}
}
void setup(){
	Serial.begin(constant.serialBaud);
}

void send_status_update() {
    Serial.write(6);
    float f1 = joint1.getJointPosition();
    float f2 = joint2.getJointPosition();
    float f3 = joint3.getJointPosition();
    float f4 = joint4.getJointPosition();

    Serial.write((char*)&f1, sizeof(float));
    Serial.write((char*)&f2, sizeof(float));
    Serial.write((char*)&f3, sizeof(float));
    Serial.write((char*)&f4, sizeof(float));
}

void loop(){
    recieveData();
	if(moveJoints()){
		sendData();
	}
    send_status_update();
	else if(moveGripper())
		recieveData();
}
