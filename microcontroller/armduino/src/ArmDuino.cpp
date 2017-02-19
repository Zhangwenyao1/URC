//Dependancies
#include <Arduino.h>
#include <Servo.h>
#include <Stepper.h>
#include <PID_v1.h>

//Utilities
#include "Util/Motor.h"
#include "Util/Potentiometer.h"
#include "Util/Switch.h"
//Componentsw
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



//Switch declaration
Switch _close = Switch(constant.closeSwitch);
Switch _open = Switch(constant.openSwitch);
Switch _index = Switch(constant.indexSwitch);

//Carousel declaration
Carousel carousel = Carousel(carouselRotate, carouselCrank, _close, _open, _index);
//Winch declaration
Winch winch = Winch(winchMotor);

void setup(){
}
void loop(){
	moveArm();
}
void moveArm(){
}
