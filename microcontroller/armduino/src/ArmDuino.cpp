//Main Arm Code, Ryerson Rams Robotics, URC2017
#include <Arduino.h>
#include <Servo.h>
#include <Stepper.h>
#include <PID.h>
#include "Motor.h"
#include "Potentiometer.h"
#include "Switch.h"

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


//Stepper declaration
Stepper joint4Stepper= Stepper(nema17Steps, _j4MA, _j4MB);
Stepper carouselCrankStepper = Stepper(nema17Steps, carouselRotateA,carouselRotateB);
Stepper carouselRotateStepper = Stepper(nema17Steps, carouselCrankA,carouselCrankB);
Stepper gripperRotateStepper = Stepper(nema17Steps,gripperRotateA,gripperRotateB);
Stepper gripperOpenStepper = Stepper(nema17Steps,gripperOpenA,gripperRotateB);

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

void setup(){
}
void loop(){
	moveArm();
}
void moveArm(){
}
