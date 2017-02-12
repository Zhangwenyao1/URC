#include "Arduino.h"
#include "Gripper.h"
#include "Motor.h"
#include "ros.h"
#include <std_msgs/Float32.h>
#include <std_msgs/UInt16.h>

Motor gripperMotor;
Gripper::Gripper(Motor _motor){
	gripperMotor = _motor;
}
void Gripper::move(std_msgs::UInt16 _point){

}
