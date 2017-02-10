//
// Created by matthew on 26/01/17.
//

#include <Arduino.h>
#include "Servo.h"
#include "ros.h"
#include "geometry_msgs/Twist.h"


ros::NodeHandle nh;
Servo leftServo;
Servo rightServo;


const int deadZoneThreshold = 93;

int rawSpeedFromX(float x) {
    if (x < 0) {
        return (int) (deadZoneThreshold - (-x * deadZoneThreshold));
    }
    else {
        return ((int) (93 + (x * deadZoneThreshold)));
    }
}

int rawSpeedFromY(float y) {
    if (y < 0) {
        return (int) (deadZoneThreshold - (-y * deadZoneThreshold));
    }
    else {
        return ((int) (93 + (y * deadZoneThreshold)));
    }
}

void setPower(double leftPower, double rightPower) { //Writes speed values to motors
    leftServo.write(leftPower);
    rightServo.write(rightPower);
}

void callback(const geometry_msgs::Twist& msg) {
    //int speed = rawSpeedFromX(msg.linear.x);
    double forwardPower = rawSpeedFromX(msg.linear.x); //x position of joystick
    double turnMod = rawSpeedFromY(msg.linear.y); //y position of joystick
   
    //Values being sent to drive
    double leftPower = forwardPower;
    double rightPower = forwardPower;

   /* 
    if (forwardPower > -0.15 && forwardPower < 0.15)  // Added deadzone, if forwardPower is less than 0.5,robot does not move forward
        forwardPower = 0;
    
    if (leftPower > -0.15 && leftPower < 0.15) 
      leftPower = 0;
        
    if (rightPower > -0.15 && rightPower < 0.15) 
      rightPower = 0;
   */
        
    if (forwardPower < 0) {// switches directions when moving backwards
      turnMod *= -1;
    
    if (turnMod > 0) // reduce power of opposite side by the turnMod
      rightPower *= 1 - Math.abs(turnMod); // ********** 1 OR 100???? ********** // 
 
    if (turnMod < 0) 
      leftPower *= 1 - Math.abs(turnMod); // ********** 1 OR 100???? ********** //
    
    if (forwardPower == 0) { // if forward = 0, then zero point turn
      leftPower = turnMod;
      rightPower = -turnMod;
    }
    
    setPower(leftpower, rightPower);
}

ros::Subscriber<geometry_msgs::Twist> sub("cmd_vel", callback);

void setup() {
    rightServo.attach(9);
    leftServo.attach(10);
   
    nh.initNode();
    nh.subscribe(sub);
   
    rightServo.write(93);
    leftServo.write(93);
}

void loop() {
    nh.spinOnce();
}
