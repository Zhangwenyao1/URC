//Main Arm Code, Ryerson Rams Robotics, URC2017
#include <Arduino.h>
#include <Servo.h>
#include <Stepper.h>
#include "ros.h"
#include <std_msgs/UInt16.h>
#include <std_msgs/Int16.h>
#include <std_msgs/Float32.h>
#include <std_msgs/Bool.h>
#include <control_msgs/Joint_Trajectories.h>
#include <sensor_msgs/JointState.h>
#include "Motor.h"
#include "Potentiometer.h"

#include "Joint.h"
#include "Winch.h"
#include "Carousel.h"
#include "Gripper.h"

#define nema17Steps 200

//motor pins
#define _j1M 0
#define _j2M 1
#define _j3M 2
#define _j4MA 3
#define _j4MB 4
#define carouselRotateA 4
#define carouselRotateB 5
#define carouselCrankA 6
#define carouselCrankB 7
#define winchM 6
#define gripperRotateA 8
#define gripperRotateB 9
#define gripperOpenA 10
#define gripperOpenB 11

//direction pins
/*#define _j1D 7
#define _j2D 9
#define _j3D 11
#define _gD 13
#define winchDir 21*/

//Stepper declaration
Stepper joint4Stepper= Stepper(nema17Steps, _j4MA, _j4MB);
Stepper carouselCrankStepper = Stepper(nema17Steps, carouselRotateA,carouselRotateB);
Stepper carouselRotateStepper = Stepper(nema17Steps, carouselCrankA,carouselCrankB);
Stepper gripperRotateStepper = Stepper(nema17Steps,gripperRotateA,gripperRotateB);
Stepper gripperOpenStepper = Steper(nema17Steps,gripperOpenA,gripperRotateB);

//Motor declaration
Motor j1M = Motor(_j1M);//dc motor
Motor j2M = Motor(_j2M);//dc motor
Motor j3M = Motor(_j3M);//dc motor
Motor j4M = Motor(joint4Stepper);//stepper motor
Motor grM = Motor(gripperRotateStepper);
Motor goM = Motor(gripperOpenStepper);
Motor carouselRotate = Motor(carouselRotateStepper);//Carousel rotate stepper
Motor carouselCrank =  Motor(carouselCrankStepper);//carousel crank stepper
Motor _winchMotor = Motor(winchM);//dc motor

//pot pins
#define _j1Pos A0	
#define _j2Pos A1
#define _j3Pos A2
#define _j4Pos A3
//Potentiometer declaration
Potentiometer j1Pos = Potentiometer(_j1Pos);
Potentiometer j2Pos = Potentiometer(_j2Pos);
Potentiometer j3Pos = Potentiometer(_j3Pos);
Potentiometer j4Pos = Potentiometer(_j4Pos);

//Joint Declaration
Joint joint1 = Joint(j1M,j1Pos);
Joint joint2 = Joint(j2M,j2Pos);
Joint joint3 = Joint(j3M,j3Pos);
Joint joint4 = Joint(j4M,j4Pos);

Gripper gripper = Gripper(grM,goM);

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
Winch winch = Winch(_winchMotor);

//ros node handle
ros::NodeHandle nh;

//Ros Subscribers
void JointPosition1(const std_msgs::Int32& cmd_msg){
	joint1.setJointPosition(cmd_msg.data());
}
ros::Subscriber<std_msgs::Int32> _JointPosition1("JointPosition1",JointPosition1);

void JointPosition2(const std_msgs::Int32& cmd_msg){
	joint2.setJointPosition(cmd_msg.data());
}
ros::Subscriber<std_msgs::Int32> _JointPosition2("JointPosition2",JointPosition2);

void JointPosition3(const std_msgs::Int32& cmd_msg){
	joint3.setJointPosition(cmd_msg.data());
}
ros::Subscriber<std_msgs::Int32> _JointPosition3("JointPosition3",JointPosition3);

void JointPosition4(const std_msgs::Int32& cmd_msg){
	joint4.setJointPositionStepper(cmd_msg.data());
}
ros::Subscriber<std_msgs::Int32> _JointPosition4("JointPosition4",JointPosition4);

void GripperOpen(const std_msgs::Int32& cmd_msg){
	gripper.open(cmd_msg.data());
}
ros::Subscriber<std_msgs::Int32> _GripperOpen("GripperNode",GripperOpen);

void GripperRotate(const std_msgs::Int32& cmd_msg){
	gripper.spin(cmd_msg.data());
}
ros::Subscriber<std_msgs::Int32> _GripperRotate("GripperSpinNode",GripperRotate);

/*void spinCarouselTo(const std_msgs::UInt16& cmd_msg){
	carousel.rotate(cmd_msg);
}
ros::Subscriber<std_msgs::UInt16> _spinCarouselTo("spinCarouselTo",spinCarouselTo);

void carouselDoor(const std_msgs::Bool& cmd_msg){
	((cmd_msg.data==true)?carousel.Open():carousel.Close());
}
ros::Subscriber<std_msgs::Bool> _carouselDoor("carouselDoor", carouselDoor);

void winchMotor(const std_msgs::Int16& cmg_msg){
	winch.doMotor(cmg_msg);
}
ros::Subscriber<std_msgs::Int16> _winchMotor_("winchMotor", winchMotor);*/
//Ros Publishers
/*std_msgs::UInt16 getJoint1Position;
ros::Publisher _getJoint1Position("getJoint1Position", &getJoint1Position);

std_msgs::UInt16 getJoint2Position;
ros::Publisher _getJoint2Position("getJoint2Position", &getJoint2Position);

std_msgs::UInt16 getJoint3Position;
ros::Publisher _getJoint3Position("getJoint3Position", &getJoint3Position);

std_msgs::UInt16 getJoint4Position;
ros::Publisher _getJoint4Position("getJoint4Position", &getJoint4Position);

std_msgs::UInt16 getCarouselPosition;
ros::Publisher _getCarouselPosition("getCarouselPosition", &getCarouselPosition);*/

/*void initializePublishers(){
	//publisher initialization
	/*nh.advertise(_getJoint1Position);
	nh.advertise(_getJoint2Position);
	nh.advertise(_getJoint3Position);
	nh.advertise(_getJoint4Position);
	nh.advertise(_getCarouselPosition);
}*/
void initializeSubscribers(){
	//subscriber initialization
	nh.subscribe(_JointPosition1);
	nh.subscribe(_JointPosition2);
	nh.subscribe(_JointPosition3);
	nh.subscribe(_JointPosition4);
	nh.subscribe(_GripperRotate);
	nh.subscribe(_GripperOpen);
	/*nh.subscribe(_spinCarouselTo);
	nh.subscribe(_carouselDoor);
	nh.subscribe(_winchMotor_);*/

}
/*void updatePublishers(){
	//set data
	getJoint1Position.data = joint1.getJointPosition();
	getJoint2Position.data = joint2.getJointPosition();
	getJoint3Position.data = joint3.getJointPosition();
	getJoint4Position.data = joint4.getJointPosition();
	//publish data
	_getJoint1Position.publish(&getJoint1Position);
	_getJoint2Position.publish(&getJoint2Position);
	_getJoint3Position.publish(&getJoint3Position);
	_getJoint4Position.publish(&getJoint4Position);
	_getCarouselPosition.publish(&getCarouselPosition);
}*/

void setup(){
	nh.initNode();//initialize the node handle
	initializeSubscribers();
}
void loop(){

	nh.spinOnce();//required
}
