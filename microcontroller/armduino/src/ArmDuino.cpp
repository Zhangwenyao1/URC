//Dependencies
#include <Arduino.h>
#include <Servo.h>
#include <Stepper.h>
#include <PID_v1.h>
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
Joint joint1 = Joint(j1M,j1Pos);
Joint joint2 = Joint(j2M,j2Pos);
Joint joint3 = Joint(j3M,j3Pos);
Joint joint4 = Joint(j4M,j4Pos);

//Switch declaration
Switch close = Switch(constant.closeSwitch);
Switch open = Switch(constant.openSwitch);

//Gripper declaration
Gripper gripper = Gripper(grM,goM,open, close);

//Winch declaration
Winch winch = Winch(winchMotor);

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

void setup(){
	initPID();
	Serial.begin(constant.serialBaud);
	recieveData();
}
void loop(){
	if(moveJoints())
		recieveData();
	else if(moveGripper())
		recieveData();
}
void initPID(){
	joint1.initPID(constant.Kp,constant.Ki,constant.Kd,constant.minOut,constant.maxOut);
	joint2.initPID(constant.Kp,constant.Ki,constant.Kd,constant.minOut,constant.maxOut);
	joint3.initPID(constant.Kp,constant.Ki,constant.Kd,constant.minOut,constant.maxOut);
}
bool moveJoints(){
	int temp;
	temp += joint1.setJointPosition(jointData.joint1);
	temp += joint2.setJointPosition(jointData.joint2);
	temp += joint3.setJointPosition(jointData.joint3);
	temp += joint4.setJointPosition(jointData.joint4);
	return ((temp==4)?true:false);
}
bool moveGripper(){
	bool temp
	if(gripperData.gripperOpen == 1)
		temp = gripper.open();
	else if(gripperData.gripperOpen == 2)
		temp = gripper.close();
	else
		temp = false;
	gripper.spin(gripperData.gripperRotate);
	return temp;
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
			if(Serial.avalable()>=sizeof(float)){
				Serial.readBytes((char*)&jointData.joint1,sizeof(float));
				Serial.readBytes((char*)&jointData.joint2,sizeof(float));
				Serial.readBytes((char*)&jointData.joint3,sizeof(float));
				Serial.readBytes((char*)&jointData.joint4,sizeof(float));
			}
			if(moveJoints()){
				data[0] = joint1.getJointPosition();
				data[1] = joint2.getJointPosition();
				data[2] = joint3.getJointPosition();
				data[3] = joint4.getJointPosition();
				sendData(data, 4);
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
			if(moveGripper()){
				data[0] = 0;
				sendData(data, 1);
			}
			break;
		case 4:
			break;
		}
}
void sendData(float data[],int length){
	for(int i = 0; i<length;i++)
		Serial.print(data[i]+" ");
}
