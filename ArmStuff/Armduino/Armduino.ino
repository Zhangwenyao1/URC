//Main Arm Code, Ryerson Rams Robotics, URC2017
#include <Arduino.h>
#include "ros.h";
#include <std_msgs/UInt16.h>
#include <std_msgs/Float32.h>

#include "Motor.h";
#include "Encoder.h";
#include "Potentiometer.h";

#include "Winch.h"
#include "Carousel.h";

//motor pins
#define _j1M 0
#define _j2M 1
#define _j3M 2
#define _gM 3
#define carouselRotateM 4
#define carouselCrankM 5
#define winchM 6
//direction pins
#define _j1D 7
#define _j2D 9
#define _j3D 11
#define _gD 13
#define carouselRotateDir 17
#define carouselCrankDir 19
#define winchDir 21

//Motor declaration
Motor j1M = Motor(_j1M, _j1D);
Motor j2M = Motor(_j2M, _j2D);
Motor j3M = Motor(_j3M, _j3D);
Motor j4M = Motor(_gM, _gD);
Motor carouselRotate = Motor(carouselRotateM, carouselRotateDir);
Motor carouselCrank =  Motor(carouselCrankM, carouselCrankDir);
Motor winchMotor = Motor(winchM, winchDir);

//pot pins
#define _j1Pos A0
#define _j2Pos A1
#define _j3Pos A2
#define pot3 A3
//Potentiometer declaration
Potentiometer j1Pos = Potentiometer(_j1Pos);
Potentiometer j2Pos = Potentiometer(_j2Pos);
Potentiometer j3Pos = Potentiometer(_j3Pos);

//encoder pins
#define encA 23
#define encB 24
//encoder declaration
Encoder encoder = Encoder(encA, encB);

//Limit Switches
#define _closeSwitch 25
#define _openSwitch 26
#define _indexSwitch 27
//Switch declaration
Switch _close = Switch(_closeSwitch);
Switch _open = Switch(_openSwitch);
Switch _index = Switch(_indexSwitch);

//Carousel declaration
Carousel carousel = Carousel(carouselRotate, carouselCrank, _close, _open, _index);
//Winch declaration
Winch winch = Winch(winchMotor);

//ros declarations and methods
ros::NodeHandle nh;

//Subscribers
void setJoint1Position(const std_msgs::Float32& cmd_msg){
  
  j1M.doMotorsPWM(cmd_msg);
}
ros::Subscriber<std_msgs::Float32> _setJoint1Position("setjoint1Position",setJoint1Position);

void setJoint2Position(const std_msgs::Float32& cmd_msg){
  
  j2M.doMotorsPWM(cmd_msg);
}
ros::Subscriber<std_msgs::Float32> _setJoint2Position("setjoint2Position",setJoint2Position);

void setJoint3Position(const std_msgs::Float32& cmd_msg){
  
  j3M.doMotorsPWM(cmd_msg);
}
ros::Subscriber<std_msgs::Float32> _setJoint3Position("setjoint3Position",setJoint3Position);


//Publishers
std_msgs::UInt16 getJoint1Position;
ros::Publisher _getJoint1Position("getJoint1Position", &getJoint1Position);

void setup(){
	nh.initNode();//initialize the node handle
  initializePublishers();
  initializeSubscribers();
	//interrupt pins for encoders
	attachInterrupt(digitalPinToInterrupt(encA), _doEncoderA, RISING);
	attachInterrupt(digitalPinToInterrupt(encB), _doEncoderB, RISING);
}
void loop(){
	updatePublishers();
	nh.spinOnce();
}
void initializePublishers(){
	//publisher initialization
	nh.advertise(_getJoint1Position);
}
void initializeSubscribers(){
	//subscriber initialization
	nh.subscribe(_setJoint1Position);
	nh.subscribe(_setJoint2Position);
	nh.subscribe(_setJoint3Position);
}
void updatePublishers(){
	//set data
	getJoint1Position.data = j1Pos.getValue();
	//publish data
	_getJoint1Position.publish(&getJoint1Position);
}
void _doEncoderA(){
  encoder.doEncoderA();
}
void _doEncoderB(){
  encoder.doEncoderB();
}
