//Dependencies
#include <Arduino.h>
#include <Servo.h>
#include <Stepper.h>
#include <PID_v1.h>
//Utilities
#include "Util/Motor.h"
#include "Util/Potentiometer.h"
#include "Util/Switch.h"
//Components
#include "Components/Joint.h"
#include "Components/Winch.h"
#include "Components/Carousel.h"
#include "Components/Gripper.h"
#include "Constants.h"

#define nema17Steps 200
Constants constant = Constants();

//Stepper declaration
Stepper joint4Stepper= Stepper(nema17Steps, constant.jointMotor4A, constant.jointMotor4B);
Stepper carouselCrankStepper = Stepper(nema17Steps, constant.carouselCrankA, constant.carouselCrankB);
Stepper carouselRotateStepper = Stepper(nema17Steps, constant.carouselRotateA, constant.carouselRotateB);
Stepper gripperRotateStepper = Stepper(nema17Steps,constant.gripperRotateA,constant.gripperRotateB);
Stepper gripperOpenStepper = Stepper(nema17Steps,constant.gripperOpenA,constant.gripperOpenB);

//Motor declaration
Motor j1M = Motor(constant.jointMotor1);//dc motor
Motor j2M = Motor(constant.jointMotor2);//dc motor
Motor j3M = Motor(constant.jointMotor3);//dc motor
Motor j4M = Motor(joint4Stepper);//stepper motor
Motor grM = Motor(gripperRotateStepper);
Motor goM = Motor(gripperOpenStepper);
Motor carouselRotate = Motor(carouselRotateStepper);//Carousel rotate stepper
Motor carouselCrank =  Motor(carouselCrankStepper);//carousel crank stepper
Motor winchMotor = Motor(constant.winchMotor);//dc motor

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
Gripper gripper = Gripper(grM,goM);

//Switch declaration
Switch close = Switch(constant.closeSwitch);
Switch open = Switch(constant.openSwitch);
Switch index = Switch(constant.indexSwitch);

//Carousel declaration
Carousel carousel = Carousel(carouselRotate, carouselCrank, close, open, index);

//Winch declaration
Winch winch = Winch(winchMotor);

void setup(){
}
void loop(){
	moveArm();
}
void moveArm(){
}
void recieveData(){
	char message[] = Serial.read();
}
void sendData(){

}
