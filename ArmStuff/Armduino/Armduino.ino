//Main Arm Code, Ryerson Rams Robotics, URC2017
#include <Arduino.h>
#include "ros.h";
#include "Motor.h";
#include "Encoder.h";
#include "Potentiometer.h";

#include "Winch.h"
#include "Carousel.h";

//motor pins
#define baseM 0
#define elbowM 1
#define wristM 2
#define gripperM 3
#define carouselRotateM 4
#define carouselCrankM 5
#define winchM 6

//direction pins
#define baseDir 7
#define elbowDir 9
#define wristDir 11
#define gripperDir 13
#define carouselRotateDir 17
#define carouselCrankDir 19
#define winchDir 21

Motor base = Motor(baseM, baseDir);
Motor elbow = Motor(elbowM, elbowDir);
Motor wrist = Motor(wristM, wristDir);
Motor gripper = Motor(gripperM, gripperDir);


//pot pins
#define pot0 A0
#define pot1 A1
#define pot2 A2
#define pot3 A3

Potentiometer elbowPot = Potentiometer(pot0);
Potentiometer wristPot = Potentiometer(pot1);

//encoder pins
#define encA 23
#define encB 24

Encoder encoder = Encoder(encA, encB);

//Limit Switches
#define _closeSwitch 25
#define _openSwitch 26
#define _indexSwitch 27
//Arm

//Carousel
Carousel carousel = Carousel(carouselRotateM, carouselCrankM, carouselRotateDir, carouselCrankDir, _closeSwitch, _openSwitch, _indexSwitch);
//Winch
Winch winch = Winch(winchM, winchDir);

void setup() {
  attachInterrupt(digitalPinToInterrupt(encA), doEncoderA, RISING);
  attachInterrupt(digitalPinToInterrupt(encB), doEncoderB, RISING);
}

void loop() {
}
void doEncoderA(){
  encoder.doEncoderA();
}
void doEncoderB(){
  encoder.doEncoderB();
}

