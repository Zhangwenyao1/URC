//Main Arm Code, Ryerson Rams Robotics, URC2017
#include <Arduino.h>
#include "ros.h";

#include "Motor.h";
#include "Encoder.h";
#include "Potentiometer.h";

#include "Arm.h"
#include "Winch.h"
#include "Carousel.h";

//motor pins
#define baseM 0
#define elbowM 1
#define wristM 2
#define gripperM 3
#define carouselSpinM 4
#define carouselCrankM 5
#define winchM 6

//direction pins
#define baseDir 7
#define elbowDir 9
#define wristDir 11
#define gripperDir 13
#define carouselSpinDir1 17
#define carouselSpinDir2 18
#define carouselCrankDir1 19
#define carouselCrankDir2 20
#define winchDir1 21

Motor base = Motor(baseM, baseDir);
Motor elbow = Motor(elbowM, elbowDir);
Motor wrist = Motor(wristM, wirstDir);
Motor gripper = Motor(gripperM, gripperDir);


//pot pins 
#define pot0 A0
#define pot1 A1
#define pot2 A2
#define pot3 A3

Potentiometer elbown = Potentiometer(pot0);
Potentiometer wrist = Potentiometer(pot1);

//encoder pins
#define encA 23
#define encB 24
Encoder encoder = Encoder(encA,encB);

//Limit Switches
#define _closeSwitch 25
#define _openSwitch 26
#define _indexSwitch 27

Swtich closeSwitch = Switch(_closeSwitch);
Switch openSwitch = Switch(_openSwitch);
Switch indexSwitch = Switch(_indexSwitch);

//Arm

//Carousel
Carousel carousel = Carousel();
//Winch


void setup(){
	attachInterrupt(digitalPinToInterrupt(encA), enc.doEncoderA, RISING);
	attachInterrupt(digitalPinToInterrupt(encA), enc.doEncoderB, RISING);
}

void loop(){
}
