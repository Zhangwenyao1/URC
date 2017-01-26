#include "Arduino.h"
#include "Joint.h"
#include "Motor.h"
#include "Potentiometer.h"
#include "Encoder.h"
#include "ros.h"
#include <std_msgs/Float32.h>

Motor jointMotor = Motor();
Potentiometer jointPot = Potentiometer();
Encoder jointEncoder = Encoder();

Joint::Joint(Motor _motor, Potentiometer _jointPot){
	jointMotor = _motor;
	jointPot = _jointPot;
}
Joint::Joint(Motor _motor, Encoder _jointEncoder){
	jointMotor = _motor;
	jointEncoder = _jointEncoder;
}
uint16_t Joint::getJointPosition(){
	return ((jointEncoder.getEncoderValues()<2)?jointPot.getValue():jointEncoder.getEncoderValues());
}
void Joint::setJointPosition(std_msgs::Float32 _pos){
	jointMotor.doMotorsPWM(_pos);
}
